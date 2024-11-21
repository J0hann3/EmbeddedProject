#include "uart.h"

void uart_init()
{
	//UBRRn = F_CPU/(16 * BAUD) -1
	// 7.6805 = 16 000 000 / / (16 * 115 200) -1
	uint16_t ubrr = F_CPU / (16. * UART_BAUDRATE) - 1 + 0.5; //add 0.5 to round the value to the nearest int
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)(ubrr & 0xFF);

	// Asynchronous USART
	RESET(UCSR0C, UMSEL00);
	RESET(UCSR0C, UMSEL01);

	// 8 data bits, no parity bits, and 1 stop 
	// => UCSZn2:0 (data bit),  UPMn1:0(parity bit), USBSn(stop bit) in UCSRnB and UCSRnC
	// Parity mode disabled
	RESET(UCSR0C, UPM00);
	RESET(UCSR0C, UPM01);

	// Stop bit => 1-bit
	RESET(UCSR0C, USBS0);

	//set number data bit to 8 bit
	SET(UCSR0C, UCSZ00);
	SET(UCSR0C, UCSZ01);
	RESET(UCSR0B, UCSZ02);

	// Activated transmitter
	SET(UCSR0B, TXEN0);
	// Activated receive
	SET(UCSR0B, RXEN0);
	// //Activated interrupt on receive
	SET(UCSR0B, RXCIE0);
}

// received
unsigned char uart_rx(void)
{
	// exit the loop if ready to read now data
	while ((UCSR0A & (1 << RXC0)) == 0)
	{}
	return UDR0;
}

// transmitted
void uart_tx(char c)
{
	// exit the loop if ready to write data (data register empty)
	while((UCSR0A & (1 << UDRE0)) == 0)
	{}
	// transmit data c
	UDR0 = c;
}

void uart_printstr(const char* str)
{
	if (str == 0)
		return;
	for (int i = 0; str[i] != '\0'; i++)
		uart_tx(str[i]);
}

void uart_printhex(uint8_t nb)
{
	uint8_t tmp1 = nb >> 4;
	uint8_t tmp2 = nb & 0x0F;

	tmp1 += tmp1 > 9 ? 'A' - 10 : '0';
    tmp2 += tmp2 > 9 ? 'A' - 10 : '0';

	uart_tx(tmp1);
	uart_tx(tmp2);
}

void uart_print_dec(uint32_t nb)
{
	if (nb < 10)
	{
		uart_tx(nb + '0');
		return;
	}
	uart_print_dec(nb / 10);
	uart_print_dec(nb % 10);
}