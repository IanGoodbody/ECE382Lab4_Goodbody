/*
 * lab4_pong.c
 *
 *  Created on: Oct 22, 2014
 *      Author: C16Ian.Goodbody
 */

#include <msp430g2553.h>
#include "lab4_bounce.h"
#include "lab4_pong.h"

#define PAT HAPPY
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
	ballPtr->position.y = 7;
	ballPtr->velocity.x = 1;
	ballPtr->velocity.y = 1;

	byte paddlePattern[PADDLE_WD] = {PADDLE};
	paddlePtr->pattern = paddlePattern;
	paddlePtr->width = PADDLE_WD;
	paddlePtr->position.x = 0;
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
			waitNLoops(65535); // Max for an unsigned short

			if(UP_BUTTON && DOWN_BUTTON)
			{
				buttonPressed=FALSE;
			}

			if(!buttonPressed)
			{
				if(UP_BUTTON == 0)
				{
					buttonPressed = TRUE;
					if(paddle.position.y > 0)
						paddle.position.y -= 2;
				}
				else if (DOWN_BUTTON == 0)
				{
					buttonPressed = TRUE;
					if(paddle.position.y < SCREEN_HEIGHT-8 )
						paddle.position.y += 2;
				}
			}
			clearDisplay();
			drawBall(ballPtr);
			drawPaddle(paddlePtr);
			i--;
		}

		hitTop(ballPtr);
		hitBottom(ballPtr);
		hitRight(ballPtr);
		hitLeft(ballPtr, paddlePtr);
		hitPaddle(ballPtr, paddlePtr);

		moveBall(ballPtr);

		clearDisplay();
		drawBall(ballPtr);
		drawPaddle(paddlePtr);
	}

}

void drawBall(ballStruct *ballPtr)
{
	drawPattern(ballPtr->position.y,
				ballPtr->position.x,
				ballPtr->pattern,
				ballPtr->width);
}

void drawPaddle(paddleStruct *paddlePtr)
{
	drawPattern(paddlePtr->position.y,
				paddlePtr->position.x,
				paddlePtr->pattern,
				paddlePtr->width);
}

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

void hitRight(ballStruct *ballPtr)
{
	if(ballPtr->position.x >= SCREEN_WIDTH-(ballPtr->width) && ballPtr->velocity.x > 0)
		ballPtr->velocity.x = -ballPtr->velocity.x;
}

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
void hitTop(ballStruct *ballPtr)
{
	if(ballPtr->position.y <= 0 && ballPtr->velocity.y < 0)
		ballPtr->velocity.y = -ballPtr->velocity.y;
}
void hitBottom(ballStruct *ballPtr)
{
	if(ballPtr->position.y >= SCREEN_HEIGHT-8 && ballPtr->velocity.y > 0)
		ballPtr->velocity.y = -ballPtr->velocity.y;
}
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
