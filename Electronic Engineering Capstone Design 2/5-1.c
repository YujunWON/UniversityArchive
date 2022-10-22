#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char led_on;

ISR(INT3_vect) {
    if (led_on) {
        PORTA = 0b10000000;     // (led_on = 0) LED OFF
        led_on = 0;
    } else {
        PORTA = 0b00000000;     // (led_on = 1) LED ON
        led_on = 1;
    }
}

int main(void)
{
    DDRA = 0b10001111;          // 입출력 방향 설정
    DDRD = 0b00000000;          // 입출력 방향 설정
    PORTD= 0b00001000;          // 풀업저항 설정
    
    EICRA = 0b10000000;         // 인터럽트 허용 설정
    EIMSK = 0b00001000;         // 인터럽트 트리거 방식 설정
    SREG |= 0b10000000;         // 전체 인터럽트 허가

    led_on = 1;
    while (1) {
        PORTA = 0b00000111;     // LED ON
        _delay_ms(500);
        PORTA = 0b00000000;     // LED OFF
        _delay_ms(500);
    }
    
}
