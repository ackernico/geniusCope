/*
 * genius.c
 *
 *  Created on: May 16, 2025
 *      Author: Nicolas Acker
 */

#include "genius.h"
#include "stm32f4xx_hal.h"
#include "tim.h"
#include "GFX_FUNCTIONS.h"
#include "ST7735.h"
#include "MPU9250.h"

#include <ctype.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int difficulty;
extern UART_HandleTypeDef huart2;

void geniusInit()
{
	/*Fill the circles with it colors*/
	fillScreen(WHITE);
	drawCircle(COORD_X_UP, COORD_Y_UP, RADIUS, BLACK); //UP circle
	drawCircle(COORD_X_DOWN, COORD_Y_DOWN, RADIUS, BLACK); //DOWN circle
	drawCircle(COORD_X_LEFT, COORD_Y_LEFT, RADIUS, BLACK); //LEFT circle
	drawCircle(COORD_X_RIGHT, COORD_Y_RIGHT, RADIUS, BLACK); //RIGHT circle
	/*Fill the circles with low opacity colors*/
	fillCircle(COORD_X_UP, COORD_Y_UP, RADIUS-1, color565(169, 169, 255)); //Filling the up circle with low opacity RED
	fillCircle(COORD_X_LEFT, COORD_Y_LEFT, RADIUS-1, color565(255, 169, 169)); //Filling the left circle with low opacity BLUE
	fillCircle(COORD_X_DOWN, COORD_Y_DOWN, RADIUS-1, color565(169, 255, 169)); //Filling the down circle with low opacity YELLOW
	fillCircle(COORD_X_RIGHT, COORD_Y_RIGHT, RADIUS-1, color565(169, 255, 255)); //Filling the right circle with low opacity GREEN
	/*Initiate the random numbers seed*/
	uint32_t seed = HAL_GetTick();
	seed ^= (MPU9250_Gyro_ReadX() << 16);
	seed ^= (MPU9250_Gyro_ReadY() << 8);
	srand(seed);
}

void geniusDifficulty(int diff)
{
	switch(diff)
	{
	case 0:
		difficulty = EASY_DELAY;
		break;
	case 1:
		difficulty = HARD_DELAY;
		break;
	case 3:
		difficulty = IMPOSSIBLE_DELAY;
		break;
	default:
	case 2:
		difficulty = MEDIUM_DELAY;
		break;
	}
}

void geniusToggleCircle(int position)
{
	switch(position)
	{
	/*  case n:
		Fill the circle with it color
		Delay according to the difficulty chosen
		Initiate the timer with it frequency
		Fill the circle with it color on low opacity
		Stop the timer
	 */
	case 0:
		fillCircle(COORD_X_UP, COORD_Y_UP, RADIUS-1, BLUE);
		HAL_Delay(difficulty);
		HAL_TIM_Base_Start_IT(&htim11);
		fillCircle(COORD_X_UP, COORD_Y_UP, RADIUS-1, color565(169, 169, 255));
		HAL_TIM_Base_Stop_IT(&htim11);
		break;
	case 1:
		fillCircle(COORD_X_DOWN, COORD_Y_DOWN, RADIUS-1, GREEN);
		HAL_Delay(difficulty);
		HAL_TIM_Base_Start_IT(&htim10);
		fillCircle(COORD_X_DOWN, COORD_Y_DOWN, RADIUS-1, color565(169, 255, 169));
		HAL_TIM_Base_Stop_IT(&htim10);
		break;
	case 2:
		fillCircle(COORD_X_LEFT, COORD_Y_LEFT, RADIUS-1, RED);
		HAL_Delay(difficulty);
		HAL_TIM_Base_Start_IT(&htim7);
		fillCircle(COORD_X_LEFT, COORD_Y_LEFT, RADIUS-1, color565(255, 169, 169));
		HAL_TIM_Base_Stop_IT(&htim7);
		break;
	case 3:
		fillCircle(COORD_X_RIGHT, COORD_Y_RIGHT, RADIUS-1, CYAN);
		HAL_Delay(difficulty);
		HAL_TIM_Base_Start_IT(&htim6);
		fillCircle(COORD_X_RIGHT, COORD_Y_RIGHT, RADIUS-1, color565(169, 255, 255));
		HAL_TIM_Base_Stop_IT(&htim6);
		break;
	default:
		break;
	}
}

int geniusGetChoice(int xA, int yA)
{
	int choice;
	if(xA >= PARAM-300)        choice = 0;  //UP
	else if(xA <= -PARAM)  choice = 1;  //DOWN
	else if(yA >= PARAM)   choice = 2;  //LEFT
	else if(yA <= -PARAM)  choice = 3;  //RIGHT
	else                   choice = -1; //REST SPOT

	return choice;
}

int geniusGame()
{
	/*Game management*/
	int defeat = 0;
	int score = 0;
	/*Getting the points*/
	int rightOnes[150];
	int choice;
	/*Gyroscope axes*/
	int x, y;
	/*Displays buffer*/
	char buffer[50];
	/*Debug message*/
	char debugMsg[50];

	while (!defeat)
	{
		rightOnes[score] = rand() % 4;
		snprintf(buffer, 40, "%i", score);
		ST7735_WriteString(COORD_X_SCORE, COORD_Y_SCORE, buffer, Font_11x18, BLACK, WHITE);
		snprintf(buffer, 40, "%i\n", score);
		HAL_UART_Transmit_IT(&huart2, &buffer, strlen(buffer));

		for(int i = 0; i <= score; i++) //Showing all the sequence
		{
			geniusToggleCircle(rightOnes[i]);
			HAL_Delay(100);
		}

		for (int i = 0; i <= score; i++)
		{
			do {
				x = MPU9250_Gyro_ReadX();
				y = MPU9250_Gyro_ReadY();
				choice = geniusGetChoice(x, y);
				HAL_Delay(difficulty/2);
			} while (choice == -1);

			geniusToggleCircle(choice);

			if (choice != rightOnes[i])
			{
				defeat = 1;
				break;
			}
		}

		if (!defeat)
		{
			score++;
			HAL_Delay(difficulty/4);
		}
		else
		{

			/*Defeat message and sound effect*/
			HAL_TIM_Base_Start_IT(&htim11);
			ST7735_WriteString(COORD_X1_DEFEATMSG, COORD_Y_DEFEATMSG, "DER", Font_16x26, WHITE, BLUE);
			HAL_Delay(350);
			HAL_TIM_Base_Stop_IT(&htim11);

			HAL_Delay(50);

			HAL_TIM_Base_Start_IT(&htim10);
			ST7735_WriteString(COORD_X2_DEFEATMSG, COORD_Y_DEFEATMSG, "RO", Font_16x26, WHITE, BLUE);
			HAL_Delay(250);
			HAL_TIM_Base_Stop_IT(&htim10);

			HAL_Delay(50);

			HAL_TIM_Base_Start_IT(&htim7);
			ST7735_WriteString(COORD_X3_DEFEATMSG, COORD_Y_DEFEATMSG, "TA", Font_16x26, WHITE, BLUE);
			HAL_Delay(250);
			HAL_TIM_Base_Stop_IT(&htim7);

			snprintf(buffer, 40, "%i pontos", score);

			if(score >= 10)
			{
				ST7735_WriteString(COORD_X_FINALMSG, COORD_Y_FINALMSG+1, buffer, Font_7x10, BLACK, WHITE);
				drawRect(COORD_X_FINALMSG-1, COORD_Y_FINALMSG, 56+2+7, 11+1, BLUE);
				drawRect(COORD_X_FINALMSG, COORD_Y_FINALMSG, 56+7, 11, WHITE);
			}
			else
			{
				ST7735_WriteString(COORD_X_FINALMSG, COORD_Y_FINALMSG+1, buffer, Font_7x10, BLACK, WHITE);
				drawRect(COORD_X_FINALMSG-1, COORD_Y_FINALMSG, 56+2, 11+1, BLUE);
				drawRect(COORD_X_FINALMSG, COORD_Y_FINALMSG, 56, 11, WHITE);
			}
		}
	}

	return defeat;
}
