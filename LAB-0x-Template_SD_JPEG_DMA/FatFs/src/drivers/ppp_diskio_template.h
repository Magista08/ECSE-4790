/**
  ******************************************************************************
  * @file    ppp_diskio.h
  * @author  MCD Application Team
  * @brief   Header for ppp_diskio.c module. the PPP diskio driver is not
             functional and is intended to show how to implement
	     a FatFS diskio driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PPP_DISKIO_H
#define __PPP_DISKIO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32xxxxx_{eval}{discovery}_ppp.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern const Diskio_drvTypeDef  PPP_Driver;

#endif /* __SD_DISKIO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

