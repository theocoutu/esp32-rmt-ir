/*
https://github.com/junkfix/esp32-rmt-ir
*/

#ifndef ir_rmt_esp32
#define ir_rmt_esp32

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/rmt_rx.h"
#include "driver/rmt_tx.h"
#include "driver/rmt_encoder.h"

extern uint8_t ir_rx_pin_rmt;
extern uint8_t ir_tx_pin_rmt;

#define RMT_IR_TAG "esp32-rmt-ir"

enum irproto { UNK, NEC, SONY, SAM, RC5, PROTO_COUNT };

typedef struct {
	rmt_encoder_t base;
	rmt_encoder_t *copy_encoder;
	uint8_t bit_index;
	int state;
} rmt_ir_encoder_t;

typedef struct {
	irproto irtype;
	uint32_t ircode;
	uint8_t bits;
} sendir_t;

typedef struct {
	uint16_t header_high;
	uint16_t header_low;
	uint16_t one_high;
	uint16_t one_low;
	uint16_t zero_high;
	uint16_t zero_low;
	uint16_t footer_high;
	uint8_t footer_low;
	uint16_t frequency;
	const char* name;
} ir_protocol_t;

extern const ir_protocol_t proto[PROTO_COUNT];

void ir_init_rmt(uint8_t tx_pin, uint8_t rx_pin);

extern void ir_recvd_rmt(irproto brand, uint32_t code, size_t len, rmt_symbol_word_t *item);
void send_ir_rmt(irproto brand, uint32_t code, uint8_t bits = 32, uint8_t burst = 1, uint8_t repeat = 1);

IRAM_ATTR bool ir_rx_done_rmt(rmt_channel_handle_t channel, const rmt_rx_done_event_data_t *edata, void *udata);

void recv_ir_rmt(void* param);
uint32_t nec_check_rmt(rmt_symbol_word_t *item, size_t &len);
uint32_t sam_check_rmt(rmt_symbol_word_t *item, size_t &len);
uint32_t sony_check_rmt(rmt_symbol_word_t *item, size_t &len);
uint32_t rc5_check_rmt(rmt_symbol_word_t *item, size_t &len);
bool rc5_bit_rmt(uint32_t d, uint32_t v);
bool check_bit_rmt(rmt_symbol_word_t &item, uint16_t high, uint16_t low);
void fill_item_rmt(rmt_symbol_word_t &item, uint16_t high, uint16_t low, bool bit);

static esp_err_t rmt_ir_encoder_reset(rmt_encoder_t *encoder);
static esp_err_t rmt_del_ir_encoder(rmt_encoder_t *encoder);
static size_t rmt_encode_ir(rmt_encoder_t *encoder, rmt_channel_handle_t channel, const void *primary_data, size_t data_size, rmt_encode_state_t *ret_state);

#endif
