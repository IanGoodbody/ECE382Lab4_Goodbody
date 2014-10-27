/*
* lab4_bounce.c
*
* 
* Author: C2C Ian Goodbody
* Function: Implements the basic functionality
* For this lab. Creates an etch-a-sketch program
* that writes multiple colors to the screen
*/

#include <msp430g2553.h>

extern void init();
extern void initNokia();
extern void clearDisplay();
extern void drawBlock(unsigned char row, unsigned char col, unsigned char coloredByte);

#define		TRUE			1
#define		FALSE			0
#define 	BLACK			0xFF
#define 	WHITE			0x00
#define		UP_BUTTON		(P2IN & BIT5)
#define		DOWN_BUTTON		(P2IN & BIT4)
#define		AUX_BUTTON		(P2IN & BIT3)
#define		LEFT_BUTTON		(P2IN & BIT2)
#define		RIGHT_BUTTON	(P2IN & BIT1)


void main() {

	unsigned char	x, y, button_press, color;

	// === Initialize system ================================================
	IFG1=0; /* clear interrupt flag1 */
	WDTCTL=WDTPW+WDTHOLD; /* stop WD */
	button_press = FALSE;


	init();
	initNokia();
	clearDisplay();
	x=4;		y=4;
	color = BLACK;
	drawBlock(y,x, color);

	while(1) {

			if (UP_BUTTON == 0) {
				while(UP_BUTTON == 0);
				if (y>=1) y=y-1;
				button_press = TRUE;
			} else if (DOWN_BUTTON == 0) {
				while(DOWN_BUTTON == 0);
				if (y<=6) y=y+1;
				button_press = TRUE;
			} else if (LEFT_BUTTON == 0) {
				while(LEFT_BUTTON == 0);
				if (x>=1) x=x-1;
				button_press = TRUE;
			} else if (RIGHT_BUTTON == 0) {
				while(RIGHT_BUTTON == 0);
				if (x<=10) x=x+1;
				button_press = TRUE;
			}
			else if (AUX_BUTTON == 0)
			{
				while (AUX_BUTTON == 0);
				color = ~color;		// Inverts the color, only works with white/black functionality
			}

			if (button_press) {
				button_press = FALSE;
				drawBlock(y,x, color); // Do not clear screen on redraw
			}
		}
}
