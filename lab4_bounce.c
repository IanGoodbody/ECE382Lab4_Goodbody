/*
 * lab4_bounce.c
 *
 *  Created on: Oct 21, 2014
 *      Author: C2C Ian Goodbody
 *    Function: Implements the B functionality
 * 		For this lab. Creates a single
 * 		ball that bounces around the screen
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
	x = 3;			// Place the ball on the fourth pixel right and down
	y = 3;
	xVel = -1;		// Move the ball towards the top left corner
	yVel = -1;

	drawPattern(y, x, patternPtr, GHOST_WD);	// Draw first image

	while(1)
	{
		int i = 8;
		while(i > 0)
		{
			waitNLoops(65535); // Max for an unsigned short
			i--;
		}

		//Change direction if there is a collision and the ball is still moving towards the wall
		if((x <= 0 && xVel < 0) || (x >= SCREEN_WIDTH-GHOST_WD && xVel > 0))
			xVel *= -1;

		if((y <= 0 && yVel < 0) || (y >= SCREEN_HEIGHT-8 && yVel > 0))
			yVel *= -1;

		// Move the ball
		x += xVel;
		y += yVel;

		// Redraw
		clearDisplay();
		drawPattern(y, x, patternPtr, GHOST_WD); // Yay matlab style array indexing!!!
	}

}
