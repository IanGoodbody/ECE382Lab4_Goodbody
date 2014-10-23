/*
 * lab4_pong.h
 *
 *  Created on: Oct 22, 2014
 *      Author: C16Ian.Goodbody
 */

#ifndef LAB4_PONG_H_
#define LAB4_PONG_H_

#define PADDLE_WD 3
#define PADDLE 0x00, 0xFF, 0xFF
#define PADDLE_HT 8

#define TRUE 1
#define FALSE 0

#define		UP_BUTTON		(P2IN & BIT5)
#define		DOWN_BUTTON		(P2IN & BIT4)
#define		AUX_BUTTON		(P2IN & BIT3)
#define		LEFT_BUTTON		(P2IN & BIT2)
#define		RIGHT_BUTTON	(P2IN & BIT1)
#define		ALL_BUTTONS		(P2IN & (BIT5 | BIT4 | BIT2 | BI1))

typedef unsigned char byte;

typedef struct vector {
	signed short x;
	signed short y;
} vectorStruct;

typedef struct ballThing { 			// It is not necessarily a ball, sorry but this is easier for me
	vectorStruct position;
	vectorStruct velocity;
	byte width;
	byte *pattern;
} ballStruct;

typedef struct paddleThing {
	vectorStruct position;
	byte width;
	byte *pattern;
} paddleStruct;

void drawBall(ballStruct *ballPtr);
void drawPaddle(paddleStruct *paddlePtr);

void moveBall(ballStruct *ballPtr);

void hitRight(ballStruct *ballPtr);
void hitLeft(ballStruct *ballPtr, paddleStruct *paddlePtr);
void hitTop(ballStruct *ballPtr);
void hitBottom(ballStruct *ballPtr);
void hitPaddle(ballStruct *ballPtr, paddleStruct *paddlePtr);

#endif /* LAB4_PONG_H_ */
