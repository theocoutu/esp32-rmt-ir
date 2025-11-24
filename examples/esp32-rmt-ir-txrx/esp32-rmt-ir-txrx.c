/*
https://github.com/junkfix/esp32-rmt-ir
*/
#include "esp32-rmt-ir.h"

void app_main() {
	ir_init_rmt(4, -1);
	for (;;)
	{
		send_ir_rmt(NEC, 0xC1AAFC03, 32, 1, 1); //protocol, code, bits, bursts, repeats
		vTaskDelay(pdMS_TO_TICKS(1000));
		send_ir_rmt(SONY, 0x3e108, 20, 1, 1); //protocol, code, bits, bursts, repeats
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
