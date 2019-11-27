#include "game_header.h"

// Init promenljive  za poziciju
int moved_left = 0, moved_right = 0, left = 0, right = 0;

// Promenljive za let lopte
int vertical_movement = 0,
    vertical_ball_flight_modifier = 1,
    vertical_ball_movement = 0;

int horizontal_ball_flight_modifier = 1,
    horizontal_ball_movement = 0,
    horizontal_movement = 0;

// Promenljive za skor
int score = 0, count = 1;

/**
 * Funkcija za pokretanje programa
 * Uzima argumente iz linije
 */
int main (int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    // Velicina prozora
    glutInitWindowSize(1100, 600);

    // Pozicija na ekranu
    glutInitWindowPosition(0, 0);

    // Ime za prozor
    glutCreateWindow("Coin ultra kul pong");

    // keyboard function
    glutKeyboardFunc(keyboard);

    // Initiate the game
    initGame();
    glutDisplayFunc(displayGame);
    glutMainLoop();
}

/**
 * Funkcija za hvatanje korisnickog inputa
 */
void keyboard(unsigned char key, int x, int y) {
    left = -200 + 200 * (moved_right - moved_left);
    right = 200 + 200 * (moved_right - moved_left);

    // Ako smo dosli do levog kraja ekrana
    if (left == -600){
        if (key == 100) moved_right++;
    }

    // Ako smo dosli do desnog kraja ekrana
    else if (right == 600){
        if (key == 97) moved_left++;
    }

    // Ako imamo gde da odemo
    else {
        if (key == 97) moved_left++;
        if (key == 100) moved_right++;
    }

    // Poziv za update
    glutPostRedisplay();
}

/**
 * Init igre
 */
void initGame (){

    // Pozadina crna
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Crvene linije
    glColor3f(1.0f, 0.0f, 0.0f);

    // Debljina
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Velicina ekrana
    gluOrtho2D(-620.0, 620.0, -340.0, 340.0);
}

void displayGame() {
    // x and y keeps point on circumference of circle
    int x, y, k;
    // outer 'for loop' is to for making motion in ball
    for (k = 0; k <= 400; k += 5) {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_LINE_STRIP);
        // i keeps track of angle
        float i = 0;
        vertical_movement = vertical_movement + 6;
        horizontal_movement = horizontal_movement + 4;
        // drawing of circle centre at (0, 12) iterated up to 2*pi, i.e., 360 degree
        while (i <= 2 * pi) {
            y = 12 + 20 * cos(i);
            x = 20 * sin(i);
            i = i + 0.5;

            if (vertical_movement == 288 && vertical_ball_movement == 0) {
                vertical_ball_flight_modifier = -1;
                vertical_movement = -288;
                vertical_ball_movement = 1;
                score++;
            }
            if (vertical_movement == 288 && vertical_ball_movement == 1) {
                vertical_ball_flight_modifier = 1;
                vertical_movement = -288;
                vertical_ball_movement = 0;
            }
            // horizontal_ball_movement 0 desno, 1 levo
            if (horizontal_movement == 580 && horizontal_ball_movement == 0) {
                horizontal_ball_flight_modifier = -1;
                horizontal_movement = -580;
                horizontal_ball_movement = 1;
            }
            if (horizontal_movement == 580 && horizontal_ball_movement == 1) {
                horizontal_ball_flight_modifier = 1;
                horizontal_movement = -580;
                horizontal_ball_movement = 0;
            }
            // Funkcija za loptu
            glVertex2i((x - horizontal_ball_flight_modifier * horizontal_movement), (y - vertical_ball_flight_modifier * vertical_movement));
        }
        glEnd();

        // these four points draws outer rectangle which determines window
        glBegin(GL_LINE_LOOP);
            glVertex2i(-600, -320);
            glVertex2i(-600, 320);
            glVertex2i(600, 320);
            glVertex2i(600, -320);
        glEnd();

        // these four points draws smaller rectangle which is for catching ball
        glBegin(GL_LINE_LOOP);
        left = -200 + 200 * (moved_right - moved_left);
        right = 200 + 200 * (moved_right - moved_left);
            glVertex2i(left, -315);
            glVertex2i(left, -295);
            glVertex2i(right, -295);
            glVertex2i(right, -315);
        glEnd();

        // Da li je lopta udarena
        if ((vertical_ball_flight_modifier * vertical_movement) == 276) {
            if ((left > ((-1 * horizontal_ball_flight_modifier * horizontal_movement) + 20)) || (right < (-1 * horizontal_ball_flight_modifier * horizontal_movement) - 20)) {
                printf("Kraj price, pod mac bato !!!\nSkor ti je :\t%d\n", score);
                printf("Levo pomerio:\t%d\n", moved_left);
                printf("Desno pomerio:\t%d\n", moved_right);
                exit(0);
            }
        }
        glutSwapBuffers();
    }
}

