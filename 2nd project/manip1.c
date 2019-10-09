#include "stm32f4xx.h"
#include "cmsis_os2.h"
#include "Board_LED.h"
#include "systemClock_Config.h"
#include "RTE_Components.h"
#include "stm32f4xx_hal.h"
#include "EventRecorder.h"


void thread_A(void * argument){
	int j=0;
	for(;;){
		LED_On(0);
		for(j=0;j<1000000;j++);
		LED_Off(0);
		for(j=0;j<1000000;j++);
	}
	
}
void thread_B(void * argument){
	int j=0;
	for(;;){
		LED_On(1);
		for(j=0;j<1000000;j++);
		LED_Off(1);
		for(j=0;j<1000000;j++);
	}
	
}
void app_main(void *argument){
osThreadNew(thread_A,NULL,NULL);
	osThreadNew(thread_B,NULL,NULL);
	osThreadTerminate(osThreadGetId());

}

int main (void){
	LED_Initialize();
	HAL_Init();
	SystemClock_Config();
	SystemCoreClockUpdate();
	EventRecorderInitialize(0U, 1U);
	EventRecorderEnable(EventRecordError,0xF0U,0xF8U);
	EventRecorderEnable(EventRecordAll,0xF2U,0xF2U);
	SystemCoreClockUpdate();
	
	osKernelInitialize();
	osThreadNew(app_main,NULL,NULL);
	osKernelStart();
	for(;;) {}
	}

	//II-4) OS_TICK_FREQ: 10000
	//   5)OS_ROBIN_TIMEOUT: 8
	//   12) A ->B
	

