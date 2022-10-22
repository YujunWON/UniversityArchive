#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char led_on;
unsigned char speed = '5';
short out = 1;                  // 출력 LED 패턴을 결정하는 변수

ISR(INT0_vect) {                // LED on/off
    if (led_on) {
        led_on = 0;
    } else {
        led_on = 1;
    }
}

ISR(INT1_vect) {                // speed up
    if (speed < '9') {
        speed++;
    }
}

ISR(INT2_vect) {                // speed down
    if (speed > '1') {
        speed--;
    }
}

void delay_ms(int speed) {
    while(speed--) {
        _delay_ms(50);
    }
}

int main(void)
{
    DDRA = 0b11111111;          // 입출력 방향 설정
    DDRD = 0b00000000;          // 입출력 방향 설정
    PORTD= 0b00000111;          // 풀업저항 설정

    EIMSK = 0b00000111;         // 인터럽트 트리거 방식 설정
    EICRA = 0b00101010;         // 인터럽트 허용 설정
    SREG |= 0b11111111;         // 전체 인터럽트 허가

    led_on = 1;                 // 초기상태: LED on
    while (1) {
        if (led_on) {
            PORTA = out;
            delay_ms(speed - '0');
            PORTA = 0x00;
            out *= 2;
            if (out == 256) {
                out = 1;
            }
            delay_ms(speed - '0');
        }
    }   
}

