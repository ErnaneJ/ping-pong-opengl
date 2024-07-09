#include "game.h"

void initialize(void)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
}

void keyboardCallback(int key, int x, int y)
{
  switch (key)
  {
  case 27: // ESC key
    exit(0);
    break;
  case 'w': // Player 1 move up
    if (player1PositionY < 0.7f)
      player1PositionY += playerSpeed;
    break;
  case 's': // Player 1 move down
    if (player1PositionY > -0.7f)
      player1PositionY -= playerSpeed;
    break;
  case GLUT_KEY_UP: // Player 2 move up
    if (player2PositionY < 0.7f)
      player2PositionY += playerSpeed;
    break;
  case GLUT_KEY_DOWN: // Player 2 move down
    if (player2PositionY > -0.7f)
      player2PositionY -= playerSpeed;
    break;
  }

  glutPostRedisplay(); // Request a screen update
}

void drawPlayer(float posX, float posY)
{
  glBegin(GL_QUADS);
  glColor3f(1.0f, 1.0f, 1.0f); // White color
  glVertex2f(posX, posY + 0.25f);
  glVertex2f(posX + 0.05f, posY + 0.25f);
  glVertex2f(posX + 0.05f, posY - 0.25f);
  glVertex2f(posX, posY - 0.25f);
  glEnd();
}

void drawBall(float posX, float posY, float radius, int segments)
{
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(1.0f, 0.0f, 0.0f); // Red color
  glVertex2f(posX, posY);      // Center of the ball

  float angle;
  for (int i = 0; i <= segments; ++i)
  {
    angle = i * 2.0f * M_PI / segments;
    glVertex2f(posX + radius * cos(angle), posY + radius * sin(angle));
  }
  glEnd();
}

void drawScore()
{
  // Position the score at the top center of the screen
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(-0.15f, 0.85f, 0.0f); // Adjustment for top center

  // Convert the score numbers to a string
  std::string scoreText = std::to_string(scorePlayer1) + " x " + std::to_string(scorePlayer2);

  // Draw the score
  glColor3f(1.0f, 1.0f, 1.0f); // White color

  glRasterPos2f(0.09f, 0.0f); // Position the text
  for (const char &c : scoreText)
  {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c); // Use bitmap font
  }

  glPopMatrix();
}

void updateBallPosition(int value)
{
  // Ball movement
  ballPositionX += ballSpeedX;
  ballPositionY += ballSpeedY;

  // Collision with walls
  if (ballPositionY >= 0.8f || ballPositionY <= -0.85f)
  {
    ballSpeedY = -ballSpeedY;
  }

  // Collision with players
  if (ballPositionX <= -0.85f && (ballPositionY >= player1PositionY - 0.245f && ballPositionY <= player1PositionY + 0.245f))
  {
    ballSpeedX = -ballSpeedX;
  }
  if (ballPositionX >= 0.8f && (ballPositionY >= player2PositionY - 0.245f && ballPositionY <= player2PositionY + 0.245f))
  {
    ballSpeedX = -ballSpeedX;
  }

  // Check if the ball is out of the screen
  if (ballPositionX <= -1.0f)
  {
    scorePlayer2++;
    ballPositionX = 0.0f;
    ballPositionY = 0.0f;
    ballSpeedX = -ballSpeedX;
  }
  if (ballPositionX >= 1.0f)
  {
    scorePlayer1++;
    ballPositionX = 0.0f;
    ballPositionY = 0.0f;
    ballSpeedX = -ballSpeedX;
  }

  glutTimerFunc(16, updateBallPosition, 0); // Call the function again after 16 ms (approximately 60 fps)
  glutPostRedisplay();                      // Request a screen update
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  // Draw the players
  drawPlayer(-0.9f, player1PositionY);
  drawPlayer(0.85f, player2PositionY);

  // Draw the ball
  drawBall(ballPositionX, ballPositionY, .025f, 100);

  drawScore();
  glFlush();
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Define the coordinate space
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
