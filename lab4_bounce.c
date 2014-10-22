/*
 * lab4_bounce.c
 *
 *  Created on: Oct 21, 2014
 *      Author: C16Ian.Goodbody
 */


#include <msp430g2553.h>
#include "lab4_bounce.h"

void main()
{

	unsigned short	x, y;
	short xVel, yVel;

	unsigned char pattern[GHOST_WD] = {GHOST}; // Initialize the happy face pattern in memory
	unsigned char *patternPtr = pattern;

	// === Initialize system ================================================
	IFG1=0; /* clear interrupt flag1 */
	WDTCTL=WDTPW+WDTHOLD; /* stop WD */


	init();
	initNokia();
	clearDisplay();
	x = 3;
	y = 3;
	xVel = -1;
	yVel = -1;

	drawPattern(y, x, patternPtr, GHOST_WD);

	while(1)
	{
		int i = 8;
		while(i > 0)
		{
			waitNLoops(65535); // Max for an unsigned short
			i--;
		}

		// Need to account for velocity direction in this to make it bounce right.
		if((x <= 0 && xVel < 0) || (x >= SCREEN_WIDTH-GHOST_WD && xVel > 0))
			xVel *= -1;

		if((y <= 0 && yVel < 0) || (y >= SCREEN_HEIGHT-8 && yVel > 0))
			yVel *= -1;

		x += xVel;
		y += yVel;

		clearDisplay();
		drawPattern(y, x, patternPtr, GHOST_WD); // Yay matlab style array indexing!!!
	}

}
