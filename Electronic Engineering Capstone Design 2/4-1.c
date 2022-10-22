#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void cmd(int command) {
    PORTB = command;
    PORTA = 0x04;
    _delay_ms(1);
    PORTA = 0x00;
}

void data(char str) {
    PORTB = str;
    PORTA = 0x05;
    _delay_ms(1);
    PORTA = 0x01;
}

void display1(char *str) {
    cmd(0x80);
    int i = 0;
    while (str[i] != '\0') {
        data(str[i++];)
    }
}

volatile char str[1][16] = {{"Your Name"}};     // Initial LCD display

int main()
{
    DDRA=0xff;
    DDRB=0xff;

    cmd(0x38);              // Set 8bit 2Line 5x7 dots
    cmd(0x01);              // Display clear
    cmd(0x80);              // Set DDRAM address or cursor position on display
    cmd(0x0c);              // Display on Cursor Off
    cmd(0x06);              // Entry Mode
    
    display1(str[0]);
    while(1);
}

