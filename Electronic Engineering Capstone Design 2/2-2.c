#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main()
{
    unsigned char on_off, read;
    int speed = 10;
    int i, x;

    DDRA = 0b11111111;
    DDRE = 0b00011111;
    PORTE = 0b11100000;

    on_off = 1;

    while(1) {
        read = PINE & 0b11100000;

        switch(read) {
            case 0b10000000:
                if (on_off) {
                    while(1) {
                        i = 0b00000001;
                        for (x=0; x<8; x++) { PORTA = i; i = i << 1; if (PINE != 0b10000000) goto Finished; _delay_ms(speed); }
                        for (x=0; x<8; x++) { PORTA = i; i = i >> 1; if (PINE != 0b10000000) goto Finished; _delay_ms(speed); }
                    }
                }
                Finished:
                    break;
            case 0b01000000:
                speed -= 2;
                break;
            case 0b00100000:
                speed += 2;
                break;
            default:
                PORTA = 0b00000000;
                break;
        }
    }
}