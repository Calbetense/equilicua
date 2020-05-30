#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/mcpwm.h"

#define PWM_1	22	//GPIO 0, pin 23
#define PWM_2	23	//GPIO 2, pin 22

TaskHandle_t taskHandle = NULL;

void task1()		// Unnecesary, but to practice
{
	mcpwm_start(MCPWM_UNIT_0, MCPWM_TIMER_0);
	mcpwm_set_signal_high(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM0A);	// PWM 1 full of power
	while(1){
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM0B, 80);	// PWM 2 kind of blink 
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM0B, 30);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
void pwm_init()
{
	mcpwm_config_t timer_config = {
		.frequency = 1000,
		.cmpr_a = 0,
		.cmpr_b = 0,
		.duty_mode = MCPWM_DUTY_MODE_0,
		.counter_mode = MCPWM_UP_COUNTER
	};

	mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, PWM_1);
	mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, PWM_2);

	mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &timer_config);

}
void app_main(void)
{
	pwm_init();

	xTaskCreate(task1, "task 1", 4096, NULL/*Variables here*/, 6 /*Piority*/, &taskHandle);
}
