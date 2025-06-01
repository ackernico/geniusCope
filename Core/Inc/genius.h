/*
 * genius.h
 *
 *  Created on: May 16, 2025
 *      Author: Nicolas Acker
 */

#ifndef INC_GENIUS_H_
#define INC_GENIUS_H_

/*Includes*/
#include <stdbool.h>

/*Delay time according to the difficulty*/
#define EASY_DELAY        300
#define MEDIUM_DELAY      200
#define HARD_DELAY        75
#define IMPOSSIBLE_DELAY  10
/*Circle radius*/
#define RADIUS 23
/*Gyroscope parameter*/
#define PARAM 3000
/*X Axis coordinates*/
#define COORD_X_UP          64
#define COORD_X_DOWN        64
#define COORD_X_LEFT        26
#define COORD_X_RIGHT       101
#define COORD_X_SCORE       59
#define COORD_X1_DEFEATMSG  7
#define COORD_X2_DEFEATMSG  55
#define COORD_X3_DEFEATMSG  87
#define COORD_X_FINALMSG	36
/*Y Axis coordinates*/
#define COORD_Y_UP         26
#define COORD_Y_DOWN       101
#define COORD_Y_LEFT       64
#define COORD_Y_RIGHT      64
#define COORD_Y_SCORE      55
#define COORD_Y_DEFEATMSG  54
#define COORD_Y_FINALMSG   80

/*Functions definition*/

/** geniusInit() - Initiate the game circles borders with white background
 *  @brief Initiate the objects from the genius game
 *  @param None
 *  @ret None
*/
void geniusInit();
/** geniusToggleCircle(int position) - Blink one of the circles with it color
 *  @brief Blink one of the circles with it color
 *  @param Position of the circle (0,1,2,3)
 *  @ret None
 */
void geniusToggleCircle(int position);
/** geniusDifficulty(char diff) - Choose the difficulty of the game
 *  @brief Choose the blinking time of the circles
 *  @param Difficulty (0 - easy, 1 - medium, 2 - hard, 3 - impossible)
 *  @ret None
 */
void geniusDifficulty(int diff);
/** geniusGetChoice(int xA, int yA); - Choose the circle with MPU9250
 *  @brief Choose the circle depending on the gyroscope position
 *  @param Axes of the gyroscope (x,y)
 *  @ret Chosen circle (0,1,2,3)
 */
int geniusGetChoice(int xA, int yA);
/** geniusGame() - Play the genius game
 *  @brief Keep the player on the loop until it loses
 *  @param None
 *  @ret Defeat bool state (0,1)
 */
int geniusGame();

#endif /* INC_GENIUS_H_ */
