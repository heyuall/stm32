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
		osDelay(50);
		
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
void thread_C(void * argument){
	int j=0;
	for(;;){
		LED_On(2);
		for(j=0;j<1000000;j++);
		LED_Off(2);
		for(j=0;j<1000000;j++);
	}
	
}
void thread_D(void * argument){
	int j=0;
	for(;;){
		LED_On(3);
		for(j=0;j<1000000;j++);
		LED_Off(3);
		for(j=0;j<1000000;j++);
	}
	
}
void app_main(void *argument){
osThreadNew(thread_A,NULL,NULL);
	osThreadNew(thread_B,NULL,NULL);
	osThreadNew(thread_C,NULL,NULL);
	osThreadNew(thread_D,NULL,NULL);
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

	//III-3)chercher le fichier RTX_Config.h et mettre OS_ROBIN_ENABLE à 1 
	//   7)main -> app-main-> A-> B -> C -> D
	//   8) 9.1 ms
	//   10) la diode 0 ne s'allume qu'une seule fois puis elle s'eteint, les autres diodes continuent à clignoter
 	//   12) 

