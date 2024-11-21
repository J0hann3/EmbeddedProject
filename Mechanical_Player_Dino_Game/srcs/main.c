#include "tool.h"
#include "uart.h"

void timer_init()
{
	// set waveform generation to mode 4 CTC
	RESET(TCCR1A, WGM10);
	SET(TCCR1A, WGM11);
	SET(TCCR1B, WGM12);
	SET(TCCR1B, WGM13);

	// set pin OC1A=0 on Compare Match with OCR1A and 1 on BOTTOM
	RESET(TCCR1A, COM1A0);
	SET(TCCR1A, COM1A1);

	// set prescaler to 64
	RESET(TCCR1B, CS10);
	RESET(TCCR1B, CS11);
	SET(TCCR1B, CS12);

	// set interrupt for OCR1A
	SET(TIMSK1, OCIE1A);

	OCR1A = 150;
	ICR1 = 1250;
	// 16 000 000 / (N * (TOP + 1)) = 500
}
// pwm period 20ms or 50Hz
// cycle 0.5ms 21
// cycle 2.5ms 160

void analog_init()
{
	//reference voltage AVCC
	SET(ADMUX, REFS0);
	RESET(ADMUX, REFS1);

	// write left to right, good for 8 bits resolution
	SET(ADMUX, ADLAR);

	// connection ADC0 pin
	RESET(ADMUX, MUX0);
	RESET(ADMUX, MUX1);
	RESET(ADMUX, MUX2);
	RESET(ADMUX, MUX3);

	// set prescale to 128 to have frequence < 200kHz
	SET(ADCSRA, ADPS0);
	SET(ADCSRA, ADPS1);
	SET(ADCSRA, ADPS2);

	SET(ADCSRA, ADEN); //enable ADC
}

int main()
{
	// set motor to output to press enter
	// digital pin 9
	SET(DDRB, PB1);
	SET(PORTB, PB1);

	// analogue pin input to get value from the photosensitive resistor
	// analogue pin 0
	RESET(DDRC, PC0);
	RESET(PORTC, PC0);
	
	uart_init();
	analog_init();
	timer_init();

	while(1)
	{
		SET(ADCSRA, ADSC); //start a conversion
		while((ADCSRA & (1 << ADSC)) != 0) //wait for the end of the conversion
		{}
		int value = ADCH;
		if (value >= 150)
		{
			OCR1A = 45;
			_delay_ms(100);
		}
		else
			OCR1A = 70;

		uart_print_dec(value);
		uart_printstr("\r\n");
		_delay_ms(20);
	}
}
