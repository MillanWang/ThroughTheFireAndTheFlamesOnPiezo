//Millan Wang - 101114457
//SYSC 3310 - Going Through the Fire and the Flames
//May 26th 2020

#include <stdint.h>
#include "../inc/BSP.h"
#include "../inc/msp432p401r.h"

/*
Helper function for changing the frequency of the buzzer
The frequency is set just like it is in BSP_Buzzer_Init()
This is used to change the note played by the buzzer
*/
void set_buzzer_frequency(uint16_t freq){
		uint16_t PWMCycles = 3000000/freq;				//Frequency corresponds to note parameter
		TA0CCR4 = (512*PWMCycles)>>10;  // defines when output signal is cleared
		TA0CCR0 = PWMCycles - 1;         // defines when output signals are set
		TA0EX0 &= ~0x0007;               // configure for input clock divider /1
		TA0CTL |= 0x0014;                // reset and start Timer A0 in up mode
}


int main(){
	uint16_t x_pos, y_pos; //Pointers for storing the joystick's x and y positions
	uint8_t select = 1; //Pointer to joystick select (pushing down on thumbstick, NOT USED but needed to call function)
	uint8_t last_quadrant = 0;//Local variable to store the most recently visited quadrant.
															//Prevents the frequency from being set more than once. 
	
	//Arrays of pointers to be sent to be printed on the LCD. 
	char C[] = {'C',' '};//Has the additional space at the end so that the flats (b) will be overwritten. 
	char D[] = {'D',' '};
	char Eb[] = {'E','b'};
	char F[] = {'F',' '};
	char G[] = {'G',' '};
	char Ab[] = {'A','b'};
	char Bb[] = {'B','b'};
	char Chi[] = {'C',' '};
	char X[] = {'X',' '};
	char performed[] = {'P','e','r','f','o','r','m','e','d',' ','u','s','i','n','g',' ','a','n'};
	char mspname[] = {'T','I',' ','M','S','P','4','3','2','P','4','0','1','R','+','B','S','P'};
	char millan[] = {'B','y',' ','M','i','l','l','a','n',' ','W','a','n','g'};
	
	//Disabling the watchdog timer
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
	
	//Initializing joystick
	BSP_Joystick_Init();
	//Initializing buzzer to off
	BSP_Buzzer_Init((uint16_t) 0);
	
	//Initializing the LCD
	BSP_LCD_Init();
	//Printing Constant message to LCD
	BSP_LCD_DrawString((uint16_t) 0, (uint16_t) 0, performed, (int16_t) 0xFFFF);
	BSP_LCD_DrawString((uint16_t) 0, (uint16_t) 1, mspname, (int16_t) 0xFFFF);
	BSP_LCD_DrawString((uint16_t) 0, (uint16_t) 2, millan, (int16_t) 0xFFFF);
	
	while(1){//Polling loop

		BSP_Joystick_Input(&x_pos, &y_pos, &select);//Reading current joystick position
		
		//Now check where the joystick is. Behavior is defined by the position
		//Changing the frequency of the buzzer calls the above helper function set_buzzer_frequency(#)
		
		if(x_pos<=340){
			//Left column. Quadrants 1,4,6
			
			if (y_pos>=683){
				//Top row
				//Quadrant 1, note:C
				if (last_quadrant != 1){
					//Frequency corresponds to note: C
					set_buzzer_frequency(1046);
					BSP_LCD_DrawString((uint16_t) 10, (uint16_t) 6, C, (int16_t) 0xFFFF);
				}
				BSP_Buzzer_Set((uint16_t) 412);
				last_quadrant = 1;
				
				
			}else if(y_pos>=341){
				//Middle row
				//Quadrant 4, note:Chi
				if (last_quadrant != 4){
					//Frequency corresponds to note: Chi
					set_buzzer_frequency(2093);
					BSP_LCD_DrawString((uint16_t) 10, (uint16_t) 6, Chi, (int16_t) 0xFFFF);
				}
				BSP_Buzzer_Set((uint16_t) 412);
				last_quadrant = 4;
				
			}else{
				//Bottom row
				//Quadrant 6, note:Bb
				if (last_quadrant != 6){
					//Frequency corresponds to note: Bb
					set_buzzer_frequency(1865);
					BSP_LCD_DrawString((uint16_t) 10, (uint16_t) 6, Bb, (int16_t) 0xFFFF);
				}
				BSP_Buzzer_Set((uint16_t) 512);
				last_quadrant = 6;
			}
			
			
		}else if (x_pos<=682){
			//Centered column. Quadrants 2,0,7

			if (y_pos>=643){
				//Top row
				//Quadrant 2, note:D
				if (last_quadrant != 2){
					//Frequency corresponds to note: D
					set_buzzer_frequency(1175);
					BSP_LCD_DrawString((uint16_t) 10, (uint16_t) 6, D, (int16_t) 0xFFFF);
				}
				BSP_Buzzer_Set((uint16_t) 512);
				last_quadrant = 2;
				
			}else if(y_pos>=341){
				//Middle row
				//Quadrant 0, note:Silent
				if (last_quadrant != 0){
					//Frequency corresponds to note: A, but is not played with the 0% duty cycle
					set_buzzer_frequency(880);
					BSP_LCD_DrawString((uint16_t) 10, (uint16_t) 6, X, (int16_t) 0xFFFF);
				}
				BSP_Buzzer_Set((uint16_t) 0);
				last_quadrant = 0;
				
			}else{
				//Bottom row
				//Quadrant 7, note:Ab
				if (last_quadrant != 7){
					//Frequency corresponds to note: Ab
					set_buzzer_frequency(1661);
					BSP_LCD_DrawString((uint16_t) 10, (uint16_t) 6, Ab, (int16_t) 0xFFFF);
				}
				BSP_Buzzer_Set((uint16_t) 512);
				last_quadrant = 7;
			}



		} else {
			//Right column, Quadrants 3,5,8
			if (y_pos>=683){
				//Top row
				//Quadrant 3, note:Eb
				if (last_quadrant != 3){
					//Frequency corresponds to note: Eb
					set_buzzer_frequency(1245);
					BSP_LCD_DrawString((uint16_t) 10, (uint16_t) 6, Eb, (int16_t) 0xFFFF);
				}
				BSP_Buzzer_Set((uint16_t) 512);
				last_quadrant = 3;
				
			}else if(y_pos>=341){
				//Middle row
				//Quadrant 5, note:F
				if (last_quadrant != 5){
					//Frequency corresponds to note: F
					set_buzzer_frequency(1397);
					BSP_LCD_DrawString((uint16_t) 10, (uint16_t) 6, F, (int16_t) 0xFFFF);
				}
				BSP_Buzzer_Set((uint16_t) 512);
				last_quadrant = 5;
			}else{
				//Bottom row
				//Quadrant 8, note:G
				if (last_quadrant != 8){
					//Frequency corresponds to note: G
					set_buzzer_frequency(1568);
					BSP_LCD_DrawString((uint16_t) 10, (uint16_t) 6, G, (int16_t) 0xFFFF);
				}
				BSP_Buzzer_Set((uint16_t) 512);
				last_quadrant = 8;
			}
		}	
	}
	
	//return 0;
}
