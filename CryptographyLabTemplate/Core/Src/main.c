#include "main.h"
#include "aes.h"
#include "gcm.h"
#include "md.h"
#include "pkcs5.h"
#include "ecdh.h"

UART_HandleTypeDef   huart6;
RNG_HandleTypeDef    hrng;
mbedtls_aes_context  ctx;
mbedtls_gcm_context  ctx_gcm;

mbedtls_ecdh_context_mbed ctx_ecdh;
mbedtls_ecdh_context ctx_cli, ctx_srv;
mbedtls_ecp_group    grp;
mbedtls_mpi			 private_key;
mbedtls_ecp_point    public_key;


// Private function prototypes
static void MX_RNG_Init(void);
void flush_screen();
void task1();
void task2();
void task3();
int f_rng(void * a, unsigned char * buff, size_t buff_size);

// Global Variable
unsigned char ERROROCCURED = 0;

int main(void){
	Sys_Init();

	MX_RNG_Init();
	MX_MBEDTLS_Init();

	HAL_Delay(1000);
	flush_screen();
	printf("Press '1' to choose the task 1\r\nPress '2' to choose the task 2\r\nPress '3' to choose the task 3\r\n");
	char choice = getchar();
	if (choice == 49){
		task1();
	}else if(choice == 50){
		task2();
	}else{
		task3();
	}

	if (ERROROCCURED) return 1;
}

/**
  * @brief RNG Initialization Function
  * @param None
  * @retval None
  */
static void MX_RNG_Init(void)
{
	hrng.Instance = RNG;
	if (HAL_RNG_Init(&hrng) != HAL_OK)
	{
		printf("Failed to initialize RNG\r\n");
		while (1);
	}
}

void flush_screen(){
	printf("\033[2J\033[;H"); // Erase screen & move cursor to home position
	printf("\033c"); // Reset device
	fflush(stdout);
}

void task1(){
	mbedtls_aes_init(&ctx);
	// Init parameter
	unsigned char secret_key[256]    = {0};
	unsigned char nounce_counter[16] = {0};
	unsigned char stream_block[16]   = {0};

	char input[100]  = {0};
	char output[100] = {0};

	size_t nc_off = 0;

	uint32_t RandomBit = 0;

	int key_length = 256;

	// Main Process
	while (1){
		// Flush the creen
		flush_screen();
		// Generate the New key
		memset(secret_key, 0, sizeof(secret_key));
		uint32_t index = 0;
		for (int i = 0; i < 64; i ++){
			HAL_RNG_GenerateRandomNumber(&hrng, &RandomBit);
			for(int j = 8; j <= 32; j+=8){
				uint32_t num = (RandomBit - ((RandomBit >> j) << j)) >> (j-8);
				secret_key[index] = num;
				index++;
			}
		}
		index = 0;
		// Receive the message
		uart_getline(&USB_UART, input, 10);

		// Encrypt the plaintext
		if (mbedtls_aes_setkey_enc(&ctx, secret_key, 256) != 0){
			printf("Generate Key Failure!\r\n");
			ERROROCCURED = 1;
			return;
		}
		if (mbedtls_aes_crypt_ctr(&ctx, key_length, &nc_off, nounce_counter, stream_block, &input, &output) != 0){
			printf("Encrypt the Plaintext Failure\r\n");
			ERROROCCURED = 1;
			return;
		}
		printf("\r\nThe encrypted message is: %s\r\n", output);

		// Decrypt the ciphertext
		memset(input, 		   0, sizeof(input));
		memset(nounce_counter, 0, sizeof(nounce_counter));
		memset(stream_block,   0, sizeof(stream_block));
		nc_off = 0;
		if (mbedtls_aes_crypt_ctr(&ctx, key_length, &nc_off, nounce_counter, stream_block, &output, &input) != 0){
			printf("Decrypt the Plaintext Failure\r\n");
			ERROROCCURED = 1;
			return;
		}
		printf("The decrypted message is: %s\r\n", input);

		// Waiting for another encryption command
		printf("Press any key to encrypt and decrypt the message\r\n");
		getchar();

		// Reset the parameters for the next round
		memset(input, 		   0, sizeof(input));
		memset(output, 		   0, sizeof(output));
		memset(nounce_counter, 0, sizeof(nounce_counter));
		memset(stream_block,   0, sizeof(stream_block));
		nc_off = 0;
	}
}

void task2(){
	// Set the basic parameters
	unsigned char secret_key[128] = {0};

	char input[100]  = {0};
	char output[100] = {0};

	unsigned char iv[512]     = "abcdefghijklmn";

	uint32_t RandomBit = 0;

	// Main process
	while(1){
		// Flush the creen
		flush_screen();

		// Generate the New key and set it
		memset(secret_key, 0, sizeof(secret_key));
		uint32_t index = 0;
		for (int i = 0; i < 32; i ++){
			HAL_RNG_GenerateRandomNumber(&hrng, &RandomBit);
			for(int j = 8; j <= 32; j+=8){
				uint32_t num = (RandomBit - ((RandomBit >> j) << j)) >> (j-8);
				secret_key[index] = num;
				index++;
			}
		}
		index = 0;
		// Receive the message
		uart_getline(&USB_UART, input, 10);

		// Encrypt the message
		mbedtls_gcm_init(&ctx_gcm);
		if(mbedtls_gcm_setkey(&ctx_gcm, MBEDTLS_CIPHER_ID_AES, secret_key, 128) != 0){
			printf("Generate Key Failure!\r\n");
			ERROROCCURED = 1;
			return;
		}
		if (mbedtls_gcm_starts(&ctx_gcm, MBEDTLS_GCM_ENCRYPT, &iv, (size_t *) strlen(iv)) != 0){
			printf("GCM Start Error!\r\n");
			ERROROCCURED = 1;
			return;
		}
		if (mbedtls_gcm_update(&ctx_gcm, &input, sizeof(input), &output, sizeof(output), (size_t *) strlen(output)) != 0){
			printf("GCM Update Error!\r\n");
			ERROROCCURED = 1;
			return;
		}
		mbedtls_gcm_free(&ctx_gcm);
		printf("\r\nThe encrypted message is: %s\r\n", output);

		// Decrypt the message
		mbedtls_gcm_init(&ctx_gcm);
		if(mbedtls_gcm_setkey(&ctx_gcm, MBEDTLS_CIPHER_ID_AES, secret_key, 128) != 0){
					printf("Generate Key Failure!\r\n");
					ERROROCCURED = 1;
					return;
		}
		if (mbedtls_gcm_starts(&ctx_gcm, MBEDTLS_GCM_DECRYPT, &iv, (size_t *) strlen(iv)) != 0){
			printf("GCM Start Error!\r\n");
			ERROROCCURED = 1;
			return;
		}

		if (mbedtls_gcm_update(&ctx_gcm, &output, sizeof(output), &input, sizeof(input), (size_t *) strlen(input)) != 0){
			printf("GCM Update Error!\r\n");
			ERROROCCURED = 1;
			return;
		}
		mbedtls_gcm_free(&ctx_gcm);
		printf("The decrypted message is: %s\r\n", input);

		// Waiting for another encryption command
		printf("Press any key to encrypt and decrypt the message\r\n");
		getchar();
	}
}

void task3(){
	initUart(&huart6, 115200, USART6);
	// unsigned char buf[64] = {0};
	unsigned char buff[32] = {0};
	size_t olen = 0;

	// Main Process
	while(1){
		// Flush the screen
		flush_screen();
		printf("Begin from here\r\n");
		// Init the context
		mbedtls_ecdh_init(&ctx_cli);
		if (mbedtls_ecdh_setup(&ctx_cli, MBEDTLS_ECP_DP_CURVE25519) != 0){
			printf("Set up Failure\r\n");
			ERROROCCURED= 1;
			return;
		}

		if (mbedtls_ecdh_make_public(&ctx_cli, &olen, buff, sizeof(buff), &f_rng, NULL) != 0){
			printf("Make Public Key Failure\r\n");
			ERROROCCURED = 1;
			return;
		}
		printf("Right now it is correct\r\n");
		getchar();
	}
}

int f_rng(void *a, unsigned char * buff, size_t buff_size){
	uint32_t index = 0;
	uint32_t RandomBit = 0;
	for (int i = 0; i < 8; i ++){
		HAL_RNG_GenerateRandomNumber(&hrng, &RandomBit);
		for(int j = 8; j <= 32; j+=8){
			uint32_t num = (RandomBit - ((RandomBit >> j) << j)) >> (j-8);
			buff[index] = num;
			index++;
		}
	}
	return 0;
}
