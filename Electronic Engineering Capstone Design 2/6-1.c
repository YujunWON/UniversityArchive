#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>

// Normal Mode
unsigned char led = 0x00;
unsigned int count = 0;

// 타이머2의 오버플로우를 이용
ISR(TIMER2_OVF_vect) {
    count++;
    if (count == 60) {
        if(led==0b10000000) {
            led=0b00000001; // LED가 다 켜졌다면 1번 LED만 켜지도록 하는 조건문
        } else {
            led = led << 1; // 1bit씩 순차적으로 이동
        }
        count = 0;          // count 변수를 다시 0으로 설정
    }
}

int main()
{
    DDRA = 0xff;        // A 포트를 출력포트로 사용
    TCCR2 = 0b00000101; // CTC를 사용하지 않으면서 프리스케일러 분주비를 1024로 설정
    TIMSK = 0b01000000; // 타이머2의 오버플로우 인터럽트 허용
    TCNT2 = 0;          // 타이머 카운터를 0으로 초기화
    SREG = 0x80;        // 전체 인터럽트 허용
    led = 0b00000001;   // 초기 LED를 1개만 켜짐으로 허용

    while(1) {
        PORTA = led;    // A 포트에 LED 값 출력
    } 
}

