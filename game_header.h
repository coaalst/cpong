#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <time.h>
#include <math.h>
#include <string.h>
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif

#define MAX_PARTICLES   500
#define pi              3.142857

// Particle struktura
typedef struct {
  // Life
  int alive;	// is the particle alive?
  float life;	// particle lifespan
  float fade; // decay

  // Position/direction
  float xpos;
  float ypos;
  // Velocity/Direction, only goes down in y dir
  float vel;
  // Gravity
  float gravity;
}particles;

// Paticle System
particles par_sys[MAX_PARTICLES];

float slowdown;
float velocity;

// Tekst buffer
char string [100];

// Kretanje slajdera
int moved_left, moved_right, left, right;

// Kretanje lopte
int vertical_movment,
    vertical_ball_flight_modifier,
    vertical_ball_movement;

int horizontal_ball_flight_modifier,
    horizontal_ball_movement,
    horizontal_movement;


// Promenljive igre
int score, count;
int loop;

void initGame(void);
void initParticles(int i);
void keyboard(unsigned char key_pressed, int x_cord, int y_cord);
void displayGame(void);
