/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    App/p2p_server_app.c
  * @author  MCD Application Team
  * @brief   Peer to peer Server Application
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "app_common.h"
#include "dbg_trace.h"
#include "ble.h"
#include "p2p_server_app.h"
#include "stm32_seq.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MAX5531.h"
#include "lis2dw12_reg.h"
#include "stm32_lpm.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct
{
  uint8_t               Notification_Status; /* used to check if P2P Server is enabled to Notify */
  uint16_t              ConnectionHandle;
	
} P2P_Server_App_Context_t;

static P2P_Server_App_Context_t  P2P_Server_App_Context;
extern stmdev_ctx_t dev_ctx;
/* USER CODE END PTD */

/* Private defines ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macros -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
static void Function_Init(void);

static void P2PS_Send_Notification(void);
/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void P2PS_STM_App_Notification(P2PS_STM_App_Notification_evt_t *pNotification)
{
/* USER CODE BEGIN P2PS_STM_App_Notification_1 */

/* USER CODE END P2PS_STM_App_Notification_1 */
  switch(pNotification->P2P_Evt_Opcode)
  {
/* USER CODE BEGIN P2PS_STM_App_Notification_P2P_Evt_Opcode */

/* USER CODE END P2PS_STM_App_Notification_P2P_Evt_Opcode */

    case P2PS_STM__NOTIFY_ENABLED_EVT:
/* USER CODE BEGIN P2PS_STM__NOTIFY_ENABLED_EVT */

/* USER CODE END P2PS_STM__NOTIFY_ENABLED_EVT */
      break;

    case P2PS_STM_NOTIFY_DISABLED_EVT:
/* USER CODE BEGIN P2PS_STM_NOTIFY_DISABLED_EVT */

/* USER CODE END P2PS_STM_NOTIFY_DISABLED_EVT */
      break;

    case P2PS_STM_WRITE_EVT:
/* USER CODE BEGIN P2PS_STM_WRITE_EVT */

/* USER CODE END P2PS_STM_WRITE_EVT */
      break;

    default:
/* USER CODE BEGIN P2PS_STM_App_Notification_default */

/* USER CODE END P2PS_STM_App_Notification_default */
      break;
  }
/* USER CODE BEGIN P2PS_STM_App_Notification_2 */

/* USER CODE END P2PS_STM_App_Notification_2 */
  return;
}

void P2PS_APP_Notification(P2PS_APP_ConnHandle_Not_evt_t *pNotification)
{
/* USER CODE BEGIN P2PS_APP_Notification_1 */

/* USER CODE END P2PS_APP_Notification_1 */
  switch(pNotification->P2P_Evt_Opcode)
  {
/* USER CODE BEGIN P2PS_APP_Notification_P2P_Evt_Opcode */

/* USER CODE END P2PS_APP_Notification_P2P_Evt_Opcode */
  case PEER_CONN_HANDLE_EVT :
/* USER CODE BEGIN PEER_CONN_HANDLE_EVT */
  P2P_Server_App_Context.Notification_Status=1; 
	UTIL_SEQ_SetTask( 1<< CFG_TASK_FUN_INIT, CFG_SCH_PRIO_0);  
/* USER CODE END PEER_CONN_HANDLE_EVT */
    break;

    case PEER_DISCON_HANDLE_EVT :
/* USER CODE BEGIN PEER_DISCON_HANDLE_EVT */
P2P_Server_App_Context.Notification_Status=0; 
/* USER CODE END PEER_DISCON_HANDLE_EVT */
    break;

    default:
/* USER CODE BEGIN P2PS_APP_Notification_default */

/* USER CODE END P2PS_APP_Notification_default */
      break;
  }
/* USER CODE BEGIN P2PS_APP_Notification_2 */

/* USER CODE END P2PS_APP_Notification_2 */
  return;
}

void P2PS_APP_Init(void)
{
/* USER CODE BEGIN P2PS_APP_Init */
  UTIL_SEQ_RegTask( 1<< CFG_TASK_SEND_DATA_ID, UTIL_SEQ_RFU, P2PS_Send_Notification);  
	UTIL_SEQ_RegTask( 1<< CFG_TASK_FUN_INIT, UTIL_SEQ_RFU, Function_Init);  
	
  P2P_Server_App_Context.Notification_Status=0; 
	
/* USER CODE END P2PS_APP_Init */
  return;
}

/* USER CODE BEGIN FD */

/* USER CODE END FD */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/
/* USER CODE BEGIN FD_LOCAL_FUNCTIONS*/
static void Function_Init(void)
{

//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
//	lis2dw12_read_data_single();
//  MAX5531_Init();

}
static void P2PS_Send_Notification(void)
{

   static uint8_t DataToSend[10] = {0xF1,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0A};
	 int16_t data_raw_acceleration[3];
	 UTIL_LPM_Mode_t LPM_mopde=0;

//   lis2dw12_acceleration_raw_get(&dev_ctx, data_raw_acceleration);
   LPM_mopde = UTIL_LPM_GetMode();
	 
//   memcpy(DataToSend+2,(uint8_t *) data_raw_acceleration,6);
	 
	 
	 DataToSend[8] = LPM_mopde;
	 
   if(P2P_Server_App_Context.Notification_Status){ 

   P2PS_STM_App_Update_Char(P2P_NOTIFY_CHAR_UUID, DataToSend);
   
   } else {

   }

     /* acceleration_mg[0] = lis2dw12_from_fs2_lp1_to_mg(
                             data_raw_acceleration[0]);
      acceleration_mg[1] = lis2dw12_from_fs2_lp1_to_mg(
                             data_raw_acceleration[1]);
      acceleration_mg[2] = lis2dw12_from_fs2_lp1_to_mg(
                             data_raw_acceleration[2]);*/


      /* After data ready signal rise, is not possible to set a
       * new trigger before 175us.
       * I2C read data operation fit this constraint while SPI need
       * a wait loop in order to guarantee it.
       */
//      for (int i = 0; i < 0x3FF; i++);


//      lis2dw12_data_rate_set(&dev_ctx, LIS2DW12_XL_SET_SW_TRIG);
	 
	    UTIL_LPM_SetStopMode(1 << CFG_LPM_APP, UTIL_LPM_ENABLE);
      UTIL_LPM_SetOffMode(1 << CFG_LPM_APP, UTIL_LPM_DISABLE);


  return;
}
/* USER CODE END FD_LOCAL_FUNCTIONS*/
