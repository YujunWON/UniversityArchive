#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

unsigned char led_on;

void PB_LEDOnOff(void) {
    if (led_on) {               // LED Off
        PORTA = 0b10000000;
        led_on = 0;
    } else {                    // LED On
        PORTA = 0b00000000;
        led_on = 1;
    }
}

int main()
{
    unsigned char key;
    DDRA = 0b10000000;          // 입출력 방향 설정
    DDRE = 0b00000000;          // 입출력 방향 설정
    PORTE = 0b10000000;
    PORTA = 0b00000000;

    led_on = 1;

    while(1) {
        key = (PINE & 0b10000000);  // 버튼 스위치 값 읽기
        switch(key) {
            case 0b10000000:        // 스위치가 눌렸음을 확인
                PB_LEDOnOff();
                _delay_ms(500);     // 0.5s 시간 지연 발생
                break;
            default:
                break;
        }
    }

}