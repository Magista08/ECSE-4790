int main(){


    /* Task 3 */
    /* Load an image into the JPEG, print out it's size, use provided function to display in Putty */

    // Decode the file with DMA

    // Print out the image size

    // Print the image in PuTTy
    raw_output = colorConversion((uint8_t *)JPEG_OUTPUT_DATA_BUFFER, num_bytes_decoded);
    if (input != 0x1B)
    	printPutty(raw_output, &jpeg_info);

    printf("Task 3 completed! Press any key to continue \r\n");
    getchar();
    printf("\033[2J\033[;H"); // Erase screen & move cursor to home position
    printf("\033c"); // Reset device
    fflush(stdout);

    /* Task 4 (Depth) */
    /* Setup DMA2D to copy image to LCD buffer */
    /* Implement the below function */
    /* If using DISCO without LCD, use second provided function to print to Putty to verify functionality*/

	uint32_t xPos = (BSP_LCD_GetXSize() - jpeg_info.ImageWidth)/2;
	uint32_t yPos = (BSP_LCD_GetYSize() - jpeg_info.ImageHeight)/2;


	DMA2D_CopyBuffer((uint32_t *)raw_output, (uint32_t *)LCD_FRAME_BUFFER, xPos , yPos, &jpeg_info);
	printPutty2D((uint8_t *)LCD_FRAME_BUFFER, xPos, yPos, &jpeg_info);
}
