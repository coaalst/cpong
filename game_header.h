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
  int alive;
  float life;	// particle lifespan
  float fade; // decay
  // boje
  float red;
  float green;
  float blue;
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
float zoom;
float pan;
float tilt;
float hailsize;

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

/**
 * Funkcija za inicijalizaciju partikala
 * @param i - index particla
 */
void initParticles(int i) {
    par_sys[i].alive = 1;
    par_sys[i].life = 1.0;
    par_sys[i].fade = (float)(rand()%100)/1000.0f+0.003f;

    par_sys[i].xpos = (float) (rand() % 21) - 10;
    par_sys[i].ypos = 10.0;


    par_sys[i].red = 0.5;
    par_sys[i].green = 0.5;
    par_sys[i].blue = 1.0;

    par_sys[i].vel = velocity;
    par_sys[i].gravity = -0.8;
}



void initGame(void);
void keyboard(unsigned char key_pressed, int x_cord, int y_cord);
void displayGame(void);
