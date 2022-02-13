/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2022 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "spi.h"
#include "usart.h"
#include "dac.h"
#include "math.h"
#include "tim.h"
#include "minmea.h"
#include "mytypes.h"
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
extern double getDistance(double lat1, double lon1, double lat2, double lon2, double *yards, double *miles);
int no_waypoints;
static struct minmea_sentence_rmc rmc;
static struct minmea_sentence_gga gga;
static struct minmea_sentence_gll gll;
//static struct minmea_sentence_gst gst;
static struct minmea_sentence_gsv gsv;
static struct minmea_sentence_vtg vtg;
static struct minmea_sentence_gsa gsa;
//static struct minmea_sentence_zda zda;

char directions[16][7] = {"North\0","NNE\0","NE\0","ENE\0","East\0","ESE\0","SE\0","SSE\0","South\0","SSW\0","SW\0","WSW\0","West\0","WNW\0","NW\0","NNW\0"};

static char gps_strings[20][80];

/*
uint32_t sine_val[100];
#define PI 3.1415926
void get_sineval()
{
	for(int i= 0;i < 100;i++)
	{
		sine_val[i] = ((sin(i*2*PI/100) + 1)*(4096/2));
	}
}
*/
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
static 	uint8_t data[DATA_SIZE];
static 	uint8_t rdata[DATA_SIZE];
float value = 0.2;
uint32_t var;

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
//  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
//  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
//  osThreadDef(myTask02, StartTask02, osPriorityIdle, 0, 128);
//  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, StartTask03, osPriorityIdle, 0, 128);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
/*
	MOSI	PA7
	SS		PC4
	SCLK	PB3
	TRIG	PB7
*/

//	uint8_t *pData = data;
	uint16_t Size = DATA_SIZE;
//	int ctr = 0;
	int i;
	uint8_t xbyte = 0x21;
//	int menu_ptr = 0;
	uint32_t error = 0;

	HAL_StatusTypeDef ret;

	for(i = 0;i < DATA_SIZE/2;i++)
	{
		data[i] = xbyte;
		if(++xbyte > 0x7f)
			xbyte = 0x1f;
	}
	xbyte = 0x7f;
	for(i = DATA_SIZE/2;i < DATA_SIZE;i++)
	{
		data[i] = xbyte;
		if(--xbyte < 0x1f)
			xbyte = 0x7f;
	}
	/* Infinite loop */

	for(;;)
	{
		ret = HAL_SPI_TransmitReceive(&hspi2, &data[0], &rdata[0], Size, 2000);
		vTaskDelay(1);
		ret = HAL_UART_Transmit(&huart2, &rdata[0], Size, 100);
		vTaskDelay(1);
/*
		xbyte = '\r';
		HAL_UART_Transmit(&huart2, &xbyte, 1, 100);
		xbyte = '\n';
		HAL_UART_Transmit(&huart2, &xbyte, 1, 100);

		vTaskDelay(1);
		if(menu_ptr == 0)
		{
			HAL_GPIO_WritePin(GPIOD, LED1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, LED2_Pin, GPIO_PIN_SET);
			menu_ptr = 1;
		}else if(menu_ptr == 1)
		{
			HAL_GPIO_WritePin(GPIOD, LED2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, LED3_Pin, GPIO_PIN_SET);
			menu_ptr = 2;
		}else if(menu_ptr == 2)
		{
			HAL_GPIO_WritePin(GPIOD, LED3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, LED4_Pin, GPIO_PIN_SET);
			menu_ptr = 3;
		}else if(menu_ptr == 3)
		{
			HAL_GPIO_WritePin(GPIOD, LED4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, LED1_Pin, GPIO_PIN_SET);
			menu_ptr = 0;
		}
*/
	}
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */

	HAL_StatusTypeDef ret;
	int i;
	uint8_t *pData;
	uint16_t Size;
	uint8_t xbyte = 0x22;

	int menu_ptr = 0;

	HAL_GPIO_WritePin(GPIOD, LED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, LED2_Pin, GPIO_PIN_SET);

	vTaskDelay(100);

//	HAL_DAC_Start(&hdac, DAC_CHANNEL_2);
/*
	HAL_TIM_Base_Start(&htim2);

	get_sineval();

	HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_2, sine_val, 100, DAC_ALIGN_12B_R);
*/
	vTaskDelay(100);
			

	for(i = 0;i < DATA_SIZE;i++)
	{
		data[i] = xbyte;
		if(++xbyte > 0x7f)
			xbyte = 0x1f;
	}
	
	pData = &data[0];
//	Size = DATA_SIZE;
	vTaskDelay(100);
	for(;;)
	{
		Size = 1;
		ret = HAL_UART_Receive(&huart2, &xbyte, Size, 5000);
		vTaskDelay(2);
		if(ret != HAL_TIMEOUT)
		{
			switch(xbyte)
			{
				case 0xFD:
					xbyte = 0x21;
					for(i = 0;i < DATA_SIZE;i++)
					{
						data[i] = xbyte;
						if(++xbyte > 0x7f)
							xbyte = 0x1f;
					}
				break;
				case 0xFE:
					xbyte = 0x7F;
					for(i = 0;i < DATA_SIZE;i++)
					{
						data[i] = xbyte;
						if(--xbyte < 0x21)
							xbyte = 0x7f;
					}
				break;
				case 0xFC:
					xbyte = 0x30;
					for(i = 0;i < DATA_SIZE/2;i++)
					{
						data[i] = xbyte;
						if(++xbyte > 0x7f)
							xbyte = 0x30;
					}
				break;
				default:
				break;
			}
			Size = DATA_SIZE;
			ret = HAL_UART_Transmit(&huart2, pData, Size, 100);
		}
		vTaskDelay(1);

		if(menu_ptr == 0)
		{
			HAL_GPIO_WritePin(GPIOD, LED1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, LED2_Pin, GPIO_PIN_SET);
			menu_ptr = 1;
		}else if(menu_ptr == 1)
		{
			HAL_GPIO_WritePin(GPIOD, LED2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, LED3_Pin, GPIO_PIN_SET);
			menu_ptr = 2;
		}else if(menu_ptr == 2)
		{
			HAL_GPIO_WritePin(GPIOD, LED3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, LED4_Pin, GPIO_PIN_SET);
			menu_ptr = 3;
		}else if(menu_ptr == 3)
		{
			HAL_GPIO_WritePin(GPIOD, LED4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, LED1_Pin, GPIO_PIN_SET);
			menu_ptr = 0;
		}
	}


  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
	int menu_ptr = 0;
	uint32_t error = 0;
	uint16_t Size = DATA_SIZE;

	HAL_StatusTypeDef ret;

	/* Infinite loop */
		
	UCHAR ch;
	int i,k;
	FARRAY fa[45];		// this should be big enough to store all the waypoints in wp[]
	double curr_lat, curr_long;
	double mdistance1, mdistance2;
	int closest_wp, next_closest_wp;
	int error_count = 0;
	int br_try = 0;
	char tempx[200];
	char tempy[30];
	char errmsg[30];
	UCHAR ucbuff[20];
	int no_recs;
	double tfloat;
	closest_wp = next_closest_wp = 0;
	int start_wp = 0;
	int end_wp;
	int wp_range = 6;
	
	struct minmea_sentence_rmc *prmc = &rmc;
	struct minmea_sentence_gga *pgga = &gga;
	struct minmea_sentence_gll *pgll = &gll;
//	struct minmea_sentence_gst *pgst = &gst;
	struct minmea_sentence_gsv *pgsv = &gsv;
	struct minmea_sentence_vtg *pvtg = &vtg;
	struct minmea_sentence_gsa *pgsa = &gsa;
//	struct minmea_sentence_gsa *pzda = &zda;

	int ret_val = -1;
	static int onoff = 0;
	void *vstruct;

	k = 0;

	while(TRUE)
	{
		do
		{
			i++;
			vTaskDelay(1);
			ret = HAL_UART_Receive(&huart3, &rdata[0], Size, 100);
			vTaskDelay(1);
//			if(tempx[i] < 0)
//				printf("%s\r\n",errmsg);
//			printf("%c",tempx[i]);
 		}while(i < 200 && tempx[i] != 0x0D && tempx[i-1] != 0x0A && tempx[i] < 0x7e);	
		// if CRLF, quit

		ret_val = minmea_sentence_id(tempx, false);
//		sprintf(tempx,"%d %d",ret_val,i);
//		myprintf1(tempx);

		switch(ret_val)
		{
			// recommended minimum specific data
			// time, date, lat/long, speed, direction
			case MINMEA_SENTENCE_RMC:
				if(get_rmc_frame(tempx, prmc) > 0)
				{
					error_count = 0;
					memset(tempx,0,sizeof(tempx));
					sprintf(tempy,"%.4f,\0",(curr_lat = minmea_tocoord(&rmc.latitude)));
					//printf("%s\r\n",tempy);
					memset(ucbuff,0,sizeof(ucbuff));
					memcpy(ucbuff,tempy,strlen(tempy)-1);
//					send_lcd(ucbuff,strlen(tempy)+5);
					vTaskDelay(1);
					strcat(tempx,tempy);

					sprintf(tempy,"%.4f,\0",(curr_long = minmea_tocoord(&rmc.longitude)));
					//printf("%s\r\n",tempy);
					memset(ucbuff,0,sizeof(ucbuff));
					memcpy(ucbuff,tempy,strlen(tempy)-1);
//					send_lcd(ucbuff,strlen(tempy)+5);
					vTaskDelay(1);
					strcat(tempx,tempy);

					sprintf(tempy,"%.1f,\0",minmea_tofloat(&rmc.speed));
					//printf("%s\r\n",tempy);
					memset(ucbuff,0,sizeof(ucbuff));
					memcpy(ucbuff,tempy,strlen(tempy)-1);
//					send_lcd(ucbuff,strlen(tempy)+5);
					vTaskDelay(1);
					strcat(tempx,tempy);

					tfloat = minmea_tofloat(&rmc.course);
					i = (int)tfloat/24.0;
					//printf("%d: %.2f %s\r\n",i,tfloat,directions[i]);
					sprintf(tempy,"%s,\0",directions[i]);
					memset(ucbuff,0,sizeof(ucbuff));
					memcpy(ucbuff,tempy,strlen(tempy)-1);
//					send_lcd(ucbuff,strlen(tempy)+5);
					strcat(tempx,tempy);
				}
				break;

			// system fixed data
			case MINMEA_SENTENCE_GGA:
				if(get_gga_frame(tempx, pgga) > 0)
				{
					error_count = 0;
					memset(tempx,0,sizeof(tempy));
					sprintf(tempx,"%.1f\0",3.2808*minmea_tofloat(&gga.altitude));
					//printf("%s\r\n",tempy);
					memset(ucbuff,0,sizeof(ucbuff));
					memcpy(ucbuff,tempx,strlen(tempx)-2);
//					send_lcd(ucbuff,strlen(tempx)+5);
					sprintf(tempy,",%d,%d,%d\0", gga.time.hours, gga.time.minutes, gga.time.seconds);
					strcat(tempx, tempy);
					//myprintf1(tempx);
					//printf("%s\r\n",tempx);
				}
				break;

			// satellites in view
			case MINMEA_SENTENCE_GSV:
				if(get_gsv_frame(tempx, pgsv) > 0)
				{
					error_count = 0;
					//sprintf(tempx,"GSV total sats: %d",gsv.total_sats);
				}
				break;

			// active satellites
			case MINMEA_SENTENCE_GSA:
				if(get_gsa_frame(tempx, pgsa) > 0)
				{
					error_count = 0;
					//sprintf(tempx,"GSA total sats: %d",gsa.fix_type);
				}
				break;

			// lat/long, time 
			case MINMEA_SENTENCE_GLL:
				if(get_gll_frame(tempx, pgll) > 0)
				{
					error_count = 0;
				}
				break;

			case MINMEA_SENTENCE_VTG:
				if(get_vtg_frame(tempx, pvtg) > 0)
				{
					error_count = 0;
/*
					sprintf(tempx,"VTG true course: %f mag track: %f speed (kph) %f",
							minmea_tofloat(&vtg.true_track_degrees),
							minmea_tofloat(&vtg.magnetic_track_degrees),
							minmea_tofloat(&vtg.speed_kph));
*/
				}
				break;

			case MINMEA_INVALID:
				if(error_count < 2)
				error_count++;
				break;

			default:
				if(error_count < 2)
				error_count++;
				break;
		}	// end of switch

		if(menu_ptr == 0)
		{
			HAL_GPIO_WritePin(GPIOD, LED1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, LED2_Pin, GPIO_PIN_SET);
			menu_ptr = 1;
		}else if(menu_ptr == 1)
		{
			HAL_GPIO_WritePin(GPIOD, LED2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, LED3_Pin, GPIO_PIN_SET);
			menu_ptr = 2;
		}else if(menu_ptr == 2)
		{
			HAL_GPIO_WritePin(GPIOD, LED3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, LED4_Pin, GPIO_PIN_SET);
			menu_ptr = 3;
		}else if(menu_ptr == 3)
		{
			HAL_GPIO_WritePin(GPIOD, LED4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, LED1_Pin, GPIO_PIN_SET);
			menu_ptr = 0;
		}
	}	// end of while(TRUE)
  /* USER CODE END StartTask03 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
