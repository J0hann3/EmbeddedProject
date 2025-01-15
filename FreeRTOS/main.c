#include "FreeRTOS.h"
#include "task.h"
#include <avr/io.h>

#define mainLED_TASK_PRIORITY   (tskIDLE_PRIORITY)

static void LedRed(void* pvParameters);

int main(void)
{
	// Create task.
	xTaskCreate
	(
		LedRed,						//function task
		(const char * const)"led red",	//name of task for debugging
		configMINIMAL_STACK_SIZE,		//stack size
		NULL,							//parameter of task function
		mainLED_TASK_PRIORITY,			//priority task
		NULL							//task handle pointer
	);
 
	// Start scheduler.
	vTaskStartScheduler();
 
	return 0;
}
 
void vApplicationIdleHook(void) {}
 
static void LedRed(void* pvParameters)
{
	DDRB |= _BV(PB5);
 
	for ( ;; )
	{
		PORTB ^= _BV(PB5);
		vTaskDelay(1000 / portTICK_PERIOD_MS); // time to wait in ticks
	}
}