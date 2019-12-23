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

#define MAX_PARTICLES   200
#define pi              3.142857

// Particle struktura
typedef struct {
  float life;
  // Position
  float xpos;
  float ypos;
  // Velocity
  float vel;
}particles;

// Paticle System
particles par_sys[MAX_PARTICLES];
int partical_init;
int partical_reset;
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
void drawText(char *string, int x, int y);
void play_death_animation(void);
void draw_rain(void);
void initParticles(int i);
void keyboard(unsigned char key_pressed, int x_cord, int y_cord);
void displayGame(void);
