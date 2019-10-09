#include "stm32f4xx.h"

#include "RTE_Components.h"
#include "EventRecorder.h"
#include "systemClock_Config.h"
#include "cmsis_os2.h"
#include "Board_LED.h"

osEventFlagsId_t evt_id1;
void thread_A(void* argument){
	int j=0;

	while(1) {
		
		LED_On (0);
		for(j=0; j<500000;j++);
		osEventFlagsSet(evt_id1,0x0001);
		for(j=0; j<500000;j++);
		LED_Off(0);
		for(j=0;j<100000;j++);
		osEventFlagsWait(evt_id1,0x0004,osFlagsWaitAny, osWaitForever);
	}}

	
	void thread_B(void* argument){
	int j=0;

	while(1) {
			osEventFlagsWait(evt_id1,0x0001,osFlagsWaitAny, osWaitForever);
		LED_On (1);
		for(j=0; j<500000;j++);
		osEventFlagsSet(evt_id1,0x0002);
		for(j=0; j<500000;j++);
		LED_Off(1);
		for(j=0;j<100000;j++);
		
	}}

void thread_C(void* argument){
	int j=0;

	while(1) {
		osEventFlagsWait(evt_id1,0x0002,osFlagsWaitAny, osWaitForever);
		LED_On (2);
		for(j=0; j<500000;j++);
		osEventFlagsSet(evt_id1,0x0003);
		for(j=0; j<500000;j++);
		LED_Off(2);
		for(j=0;j<100000;j++);
		
	}}
void thread_D(void* argument){
	int j=0;

	while(1) {
		osEventFlagsWait(evt_id1,0x0003,osFlagsWaitAny, osWaitForever);
		LED_On (3);
		for(j=0; j<500000;j++);
		osEventFlagsSet(evt_id1,0x0004);
		for(j=0; j<500000;j++);
		LED_Off(3);
		for(j=0;j<100000;j++);
		
	}}
void app_main(void*argument){
	osThreadSetPriority(osThreadGetId(), osPriorityHigh);
	osThreadNew(thread_A,NULL,NULL);
	osThreadNew(thread_B,NULL,NULL);
	osThreadNew(thread_C,NULL,NULL);
	osThreadNew(thread_D,NULL,NULL);
	evt_id1=osEventFlagsNew(NULL);
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