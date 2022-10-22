#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void cmd(int command){
    PORTB = command;
    PORTA = 0x04;
    _delay_ms(1);
    PORTA = 0x00;
}
void data(char str){
    PORTB = str;
    PORTA = 0x05;
    _delay_ms(1);
    PORTA = 0x01;
}

void display1(char *str){
    cmd(0x80);
    int i= 0;
    while(1) {
        if(i == 20) {
            _delay_ms(1000);
        } else if((i > 20) && (i < 26)) {
            cmd(0x18);
            _delay_ms(1000);
        }
        data(str[i]);
        i++;
        if(i==26) {                 // 초기화
            i = -1;
            cmd(0x18);
            _delay_ms(1000);
            cmd(0x01);
        }
    }
}

volatile char str[1][26]= {{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"}}; //출력문자

int main(){
    DDRA=0xff;
    DDRB=0xff;
    
    cmd(0x34);                      // Set 8bit 1Line 5x7 dots
    cmd(0x01);                      // Display clear
    cmd(0x80);                      // Set DDRAM address or cursor position on display
    cmd(0x0c);                      // Display on Cursor Off
    cmd(0x06);                      // Entry Mode

    display1(str[0]);
    while(1);
}