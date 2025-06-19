#include <reg51.h>

sbit start_button = P2^0;
sbit switch1 = P2^1;
sbit switch2 = P2^2;
sbit wash = P2^3;
sbit drain = P2^4;

sbit pump1 = P3^3;
sbit pump2 = P3^4;
sbit motor1 = P3^5;
sbit motor2 = P3^6;

sbit buzzer = P3^0;
sbit red_led = P3^1;
sbit green_led = P3^2;

sbit s1 = P1^1;
sbit en1 = P1^2;
sbit en2 = P1^3;

unsigned int overflow_count = 0;
unsigned int minutes_remaining = 0;

unsigned int wash_mode_active = 0;
unsigned int drain_mode_active = 0;

// 7-segment display lookup table (common anode)
unsigned char seg_code[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 125; j++);
    }
}

void display_minutes(unsigned char minutes) {
    
    unsigned char units = minutes % 10;
    s1 = 1;
    P0 = seg_code[units];
    delay_ms(10);
}

void wash_mode() {
    pump1 = 1; pump2 = 0;
    motor1 = 1; motor2 = 0;
    delay_ms(1500); // 1.5 seconds
    motor1 = 0; motor2 = 1;
    delay_ms(1500); // 1.5 seconds
}

void drain_mode() {
    pump1 = 0; pump2 = 0;
    motor1 = 1; motor2 = 0;
    delay_ms(1500); // 1.5 seconds
    motor1 = 0; motor2 = 1;
    delay_ms(1500); // 1.5 seconds
}

void timer0_ISR() interrupt 1 {
		//(65536-19453)*1.085us=50000.055=50ms =>4B FD
	  //(65536-15536)*1us=50000=50ms =>3C B0
    TH0 = 0x3C; 
    TL0 = 0xB0; 
    overflow_count++;
		
    if (overflow_count >= 1200) {
        overflow_count = 0;
        if (minutes_remaining != 0) {
            minutes_remaining--;
            display_minutes(minutes_remaining);
        }
			
		
    if (minutes_remaining == 0) {
            TR0 = 0;
            red_led = 0;
            green_led = 1;
	pump1=0;
	pump2=0;
	motor1=0;
	motor2=0;
	en1=0;
	en2=0;
            buzzer = 1;
        }
			}
}

void timer0_init() {
    TMOD = 0x01;
    TH0 = 0x3C;
    TL0 = 0xB0;
    ET0 = 1;
    EA = 1;
    TR0 = 1;
}

void main() {
    buzzer = 0;
    red_led = 0;
    green_led = 0;
	pump1=0;
	pump2=0;
	motor1=0;
	motor2=0;
	en1=1;
	en2=1;
    while (1) {
        if (start_button == 1) {
            if (wash == 1 && drain==0) {
                wash_mode_active = 1;
							
                minutes_remaining = (switch1 == 1) ? 2 : 1;
                overflow_count = 0;
                red_led = 1;
                green_led = 0;
                buzzer = 0;
                display_minutes(minutes_remaining);
                timer0_init();

                while (wash == 1 && wash_mode_active) {
                    wash_mode();
                }
								
                wash_mode_active = 0;  // Reset when wash switch is turned off
                red_led = 0;           // Turn off red LED when mode ends
            } else if (drain == 1 && wash==0) {
                drain_mode_active = 1;
                minutes_remaining = (switch1 == 1) ? 2 : 1;
                overflow_count = 0;
                red_led = 1;
                green_led = 0;
                buzzer = 0;
                display_minutes(minutes_remaining);
                timer0_init();

                while (drain == 1 && drain_mode_active) {
                    drain_mode();
                }
                drain_mode_active = 0;  // Reset when drain switch is turned off
                red_led = 0;            // Turn off red LED when mode ends
            }
        }
    }
}
