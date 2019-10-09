#include "stm32f4xx.h"

#include "RTE_Components.h"
#include "EventRecorder.h"
#include "systemClock_Config.h"
#include "cmsis_os2.h"
#include "Board_LED.h"

osThreadId_t TA,TB;
void thread_A(void* argument){
	int j=0;

	while(1) {
		
		LED_On (0);
		for(j=0; j<10000000;j++);
		osThreadFlagsSet(TB,0x0001);
		
		LED_Off(0);
		for(j=0;j<100000000;j++);
		
	}}
void thread_B(void*argument){
	int j=0;
	while (1) {
		osThreadFlagsWait(0x0001,osFlagsWaitAny, osWaitForever);
		LED_On(1);
		for(j=0;j<10000000;j++);
	  LED_Off(1);
		for(j=0;j<100000000;j++);
			
		
		
	}}
void app_main(void*argument){
	osThreadSetPriority(osThreadGetId(), osPriorityHigh);
	TA=osThreadNew(thread_A,NULL,NULL);
	TB= osThreadNew(thread_B,NULL,NULL);
	
	osThreadTerminate(osThreadGetId());
}
int main(void){
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
for(;;);
}