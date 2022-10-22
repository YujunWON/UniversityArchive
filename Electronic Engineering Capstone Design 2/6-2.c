#define F_CPU 16000000
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

unsigned int count = 0;
unsigned int sec = 0;               // second
unsigned int min = 0;               // minute
unsigned int h = 0;                 // hour
char time[16];                      // h min sec 변수 받아서 출력
char stop = 0;                      // 스톱워치의 on/off 여부를 정하는 변수

void cmd(int command){
	PORTB = command;            // receive data pin
	PORTA = 0x04;               // 화면 shift off
	_delay_ms(1);
	PORTA = 0x00;               // 동작 x
}

void data(char str){
	PORTB = str;                // data 전송
	PORTA = 0x05;               // 화면 shift on
	_delay_ms(1); 
	PORTA = 0x01;               // display clear
}

void display1(char *str){           // 1번째 줄 출력 함수
	cmd(0x80);
	int i = 0;
	while(str[i] != '\0') {
		data(str[i++]);     // LCD에 str upload 
	}
}

void display2(char*str){            // 2번째 줄 출력 함수
	cmd(0x80 | 0x40);
	int i = 0;
	while(str[i] != '\0') {
		data(str[i++]);     // LCD에 str upload 
	}
}

ISR(TIMER2_OVF_vect){
	if(stop == 1){              // stop == 1이면 스톱워치가 실행
	    count++;
        if(count == 60) {
            sec++;
            count = 0;
        }
        if(sec == 60) {             // 60sec를 넘어가면 +1min
            min += 1;
        }
        if(min == 60) {             // 60min을 넘어가면 +1hour
            h += 1;
        }
	}
}
		
ISR(INT0_vect) {                    // 0번 스위치
	stop = 1;                   // stop = 1: 스톱워치 실행
}

ISR(INT1_vect) {                    // 1번 스위치
	stop = 0;                   // stop = 0: 스톱워치 정지
}

ISR(INT2_vect) {                    // 2번 스위치: 스톱워치 초기화
	count = 0;
	sec = 0;
	min = 0;
	h = 0;
}

volatile char str[1][16]={{"stop watch"}};

int main(void)
{
	DDRD = 0b00000111;
	PORTD =0b11111000;
	DDRA = 0xff;                // PORTA 출력 설정
	DDRB = 0xff;                // PORTB 출력 설정 
	cmd(0x38);                  // 기능셋(데이터베이스 8bit, 라인수 2줄)
	cmd(0x01);                  // 화면 지우기 
	cmd(0x80);                  // Set DDRAM address
	cmd(0x0c);                  // Display on 
	cmd(0x06);                  // entry mode set

	EIMSK = 0x07;               // INT 0~2 사용허가
	EICRA = 0b00101010;         // INTERRUPT 0~2 down edge에서 interrupt 
	SREG |= 0x80;               // interrupt 허가

	TCCR2 = 0x05;               // normal mode
	TIMSK = 0x40;               // overflow interrupt 허용
	TCNT2 = 0;                  // Timer Coutner 0 초기화 

    while (1) {
	sprintf(time,"%02d:%02d:%02d", h, min, sec); //sprintf 함수 이용하여 LCD 출력 
	display1(str[0]);           // 1번째 줄에는 stop watch 출력 
	display2(time);             // 2번째 줄에는 시간 출력 
    }
}
