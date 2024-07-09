#include "game.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

float player1PositionY = 0.0f;
float player2PositionY = 0.0f;
float ballPositionX = 0.0f;
float ballPositionY = 0.0f;
float ballSpeedX = 0.01f;
float ballSpeedY = 0.005f;
float playerSpeed = 0.1f;
int scorePlayer1 = 0;
int scorePlayer2 = 0;

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Ping Pong Game");

  initialize();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutSpecialFunc(keyboardCallback);

  glutTimerFunc(0, updateBallPosition, 0);

  glutMainLoop();

  return 0;
};
