#ifndef GAME_H
#define GAME_H

#define GL_SILENCE_DEPRECATION

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <iostream>
#include <string>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

extern float player1PositionY;
extern float player2PositionY;
extern float ballPositionX;
extern float ballPositionY;
extern float ballSpeedX;
extern float ballSpeedY;
extern float playerSpeed;
extern int scorePlayer1;
extern int scorePlayer2;

void initialize(void);
void keyboardCallback(int key, int x, int y);
void drawPlayer(float posX, float posY);
void drawBall(float posX, float posY, float radius, int segments);
void drawScore();
void updateBallPosition(int value);
void display();
void reshape(int w, int h);

#endif // GAME_H
