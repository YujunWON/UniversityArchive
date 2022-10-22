#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

volatile char ch;

ISR(USART0_RX_vect) {
    ch = UDR0;
    if ((ch >= 'a') && (ch <= 'z')) {
        ch += ('A' - 'a');
        UDR0 = ch;
    } else {
        UDR0 = '\0'
    }
}

int main(void)
{
    UCSR0A = 0b00000000;
    UCSR0B = 0b10011000;
    UCSR0C = 0b10000110;

    UBRR0H = 0;
    UBRR0L = 103;
    SREG = 0x80;

    while(1)
}