#include<stdio.h>
#include <GL/gl.h>
#include<GL/glut.h>
#include<math.h>
#define pi 3.142857

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

void initGame(void);
void keyboard(unsigned char key_pressed, int x_cord, int y_cord);
void displayGame(void);
