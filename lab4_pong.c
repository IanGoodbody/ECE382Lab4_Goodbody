/*
 * lab4_pong.c
 *
 *  Created on: Oct 22, 2014
 *      Author: C2C Ian Goodbody
 *    Function:	Implements the A functionality
 *		For this lab. Creates a single
 *		player pong game with no AI.
 */

#include <msp430g2553.h>
#include "lab4_bounce.h"
#include "lab4_pong.h"

#define PAT HAPPY		// Allows the user to change a single line and change the pattern
#define PAT_WD HAPPY_WD

void main()
{
	byte buttonPressed;

	ballStruct ball;
	paddleStruct paddle;

	ballStruct *ballPtr = &ball;
	paddleStruct *paddlePtr = &paddle;

	byte ballPattern[PAT_WD] = {PAT}; // Initialize the happy face pattern in memory
	ballPtr->pattern = ballPattern;
	ballPtr->width = PAT_WD;	  
	ballPtr->position.x = 5;
	ballPtr->position.y = 7;	// Place the ball on the 6th pixel right and 8th pixel down
	ballPtr->velocity.x = 1;	// Set the velocity down and right
	ballPtr->velocity.y = 1;

	byte paddlePattern[PADDLE_WD] = {PADDLE};
	paddlePtr->pattern = paddlePattern;
	paddlePtr->width = PADDLE_WD;
	paddlePtr->position.x = 0;	// Place the paddle at the upper left corner of the screen
	paddlePtr->position.y = 0;

	// === Initialize system ================================================
	IFG1=0; /* clear interrupt flag1 */
	WDTCTL=WDTPW+WDTHOLD; /* stop WD */


	init();
	initNokia();
	clearDisplay();
	drawBall(ballPtr);
	drawPaddle(paddlePtr);

	buttonPressed = FALSE;

	int i;
	while(1)
	{
		i = 3;
		while(i > 0)
		{
			waitNLoops(65535); // 65535 is max for an unsigned short

			if(UP_BUTTON && DOWN_BUTTON)
			{
				buttonPressed=FALSE;	// If the up and down buttons are released allow the paddle to update
			}

			if(!buttonPressed)
			{
				if(UP_BUTTON == 0)
				{
					buttonPressed = TRUE;
					if(paddle.position.y > 0)
						paddle.position.y -= 2;	// Moving two pixels speeds up the paddle movement
				}
				else if (DOWN_BUTTON == 0)
				{
					buttonPressed = TRUE;
					if(paddle.position.y < SCREEN_HEIGHT-8 )
						paddle.position.y += 2;
				}
			}
			clearDisplay();		// Redraw the paddle at its new location 
			drawBall(ballPtr);	// Note this will slow the ball movement slightly
			drawPaddle(paddlePtr);
			i--;
		}

		hitTop(ballPtr);		// Check for collisions and update the ball parameters
		hitBottom(ballPtr);
		hitRight(ballPtr);
		hitLeft(ballPtr, paddlePtr);
		hitPaddle(ballPtr, paddlePtr);

		moveBall(ballPtr);

		clearDisplay();			// Redraw the screen
		drawBall(ballPtr);
		drawPaddle(paddlePtr);
	}

}

/*
 * drawBall: A wrapper function for the drawPattern()
 * 	     simplifying the function call in main
 */
void drawBall(ballStruct *ballPtr)
{
	drawPattern(ballPtr->position.y,
				ballPtr->position.x,
				ballPtr->pattern,
				ballPtr->width);
}
/*
 * drawPaddle: A wrapper function for the drawPattern()
 * 	       simplifying the function call in main
 */
void drawPaddle(paddleStruct *paddlePtr)
{
	drawPattern(paddlePtr->position.y,
				paddlePtr->position.x,
				paddlePtr->pattern,
				paddlePtr->width);
}

/*
 * moveBall: Updates the ball position based on its
 * 	     velocity properties
 */
void moveBall(ballStruct *ballPtr)
{
	/*
	if(ballPtr->velocity.x != 0)
		ballPtr->position.x += (ballPtr->velocity.x > 0) ? 1 : -1;

	if(ballPtr->velocity.y != 0)
		ballPtr->position.y += (ballPtr->velocity.y > 0) ? 1 : -1;
		*/
	ballPtr->position.x += ballPtr->velocity.x;
	ballPtr->position.y += ballPtr->velocity.y;
}

/*
 * hitRight: Chceks if the ball is at the right screen edge
 * 	     and if so reverses the x velocity
 */
void hitRight(ballStruct *ballPtr)
{
	if(ballPtr->position.x >= SCREEN_WIDTH-(ballPtr->width) && ballPtr->velocity.x > 0)
		ballPtr->velocity.x = -ballPtr->velocity.x;
}

/*
 * hitLeft: Chceks if the ball is past the paddle
 * 	     and if so moves the ball to the center of 
 *	     the screen with no velocity. (Game Over)
 */
void hitLeft(ballStruct *ballPtr, paddleStruct *paddlePtr)
{
	if(ballPtr->position.x < paddlePtr->width && ballPtr->velocity.x < 0)
	{
		ballPtr->position.x = 48-ballPtr->width;
		ballPtr->position.y = 30;
		ballPtr->velocity.x = 0;
		ballPtr->velocity.y = 0;
	}
}

/*
 * hitTop: Chceks if the ball is at the top screen edge
 * 	   and if so reverses the y velocity
 */
void hitTop(ballStruct *ballPtr)
{
	if(ballPtr->position.y <= 0 && ballPtr->velocity.y < 0)
		ballPtr->velocity.y = -ballPtr->velocity.y;
}

/*
 * hitBottom: Chceks if the ball is at the bottom screen edge
 * 	      and if so reverses the y velocity
 */
void hitBottom(ballStruct *ballPtr)
{
	if(ballPtr->position.y >= SCREEN_HEIGHT-8 && ballPtr->velocity.y > 0)
		ballPtr->velocity.y = -ballPtr->velocity.y;
}

/*
 * hitPaddle: Checks if the ball made contact with the paddle then changes the velocities
 * 	      reversing the x and increasing or decreasing they y depending on if the ball
 *	      strikes the edge or center of the paddle
 */
void hitPaddle(ballStruct *ballPtr, paddleStruct *paddlePtr)
{
	if(ballPtr->position.x == paddlePtr->width)
	{
		if(ballPtr->position.y >= (paddlePtr->position.y)-7 && ballPtr->position.y < (paddlePtr->position.y)-3)
		{
			if(ballPtr->velocity.y > -4)
			{
				ballPtr->velocity.y--;
				ballPtr->velocity.x = -ballPtr->velocity.x;
			}
		}
		else if (ballPtr->position.y >= (paddlePtr->position.y)-3 && ballPtr->position.y < (paddlePtr->position.y)+4)
		{
			ballPtr->velocity.x = -ballPtr->velocity.x;
		}
		else if (ballPtr->position.y >= (paddlePtr->position.y)+4 && ballPtr->position.y < (paddlePtr->position.y)+7)
		{
			if(ballPtr->velocity.y < 4)
			{
				ballPtr->velocity.y++;
				ballPtr->velocity.x = -ballPtr->velocity.x;
			}
		}
	}
}
