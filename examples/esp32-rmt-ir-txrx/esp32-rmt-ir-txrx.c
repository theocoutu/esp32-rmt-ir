/*
https://github.com/junkfix/esp32-rmt-ir
*/
#include "esp32-rmt-ir.h"

void irReceived(irproto brand, uint32_t code, size_t len, rmt_symbol_word_t *item){
	if( code ){
		ESP_LOGD("", "IR %s, code: %#x, bits: %d,  proto[brand].name, code, len);
	}
	
	if (true)	// debug
	{
		ESP_LOGD("", "Rx%d:", len);							
		for (uint8_t i=0; i < len ; i++ ) {
			int d0 = item[i].duration0; if(!item[i].level0){d0 *= -1;}
			int d1 = item[i].duration1; if(!item[i].level1){d1 *= -1;}
			ESP_LOGD("", "%d,%d", d0, d1);
		}								
	}
}

void ir_setup() {
	ir_rx_pin = 34;
	ir_tx_pin = 4;
	xTaskCreatePinnedToCore(recv_ir_rmt, "recv_ir_rmt", 2048, NULL, 10, NULL, 1);
}

void app_main() {
	send_ir_rmt(NEC, 0xC1AAFC03, 32, 1, 1); //protocol, code, bits, bursts, repeats
	vTaskDelay(pdMS_TO_TICKS(1000));
	send_ir_rmt(SONY, 0x3e108, 20, 1, 1); //protocol, code, bits, bursts, repeats
	vTaskDelay(pdMS_TO_TICKS(1000));
}
