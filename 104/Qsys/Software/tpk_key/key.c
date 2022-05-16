/*
 * key.c
 *
 *  Created on: 2021��5��9��
 *      Author: hlK
 */

#include "key.h"
#include <stdint.h>
#include <system.h>
#include <io.h>
#include <altera_avalon_uart_regs.h>
#include <priv/alt_legacy_irq.h>

//static bool key_status[103];
key_flow_t key_flow;

void key_isr(void* isr_context) {
	unsigned payload = IORD(KEY_STREAM_BASE, 0);
	key_flow.valid = true;
	key_flow.down = payload & KEY_DOWN_MASK;
	key_flow.code = payload & KEY_ID_MASK;
}

void key_init(void) {
	int err = alt_irq_register(KEY_STREAM_IRQ, NULL, key_isr);  //ע���ж�
	printf("kirq:%d\n", err);
}

key_flow_t key_get(void) {
	return key_flow;
}

void key_set(void) {
	key_flow.valid = false;
}

