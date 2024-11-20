#ifndef UART_H
# define UART_H
# include "tool.h"

void uart_init();

unsigned char uart_rx(void);

void uart_tx(char c);

void uart_printstr(const char* str);

void uart_printhex(uint8_t nb);

void uart_print_dec(uint32_t nb);

// ISR(USART_RX_vect) => get_interrupt

#endif