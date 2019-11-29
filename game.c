#include "game_header.h"

// Init promenljive  za poziciju
int moved_left = 0, moved_right = 0, left = 0, right = 0;

// Promenljive za let lopte
float random_trajectory_modifier = 0;

int vertical_movement = 0,
    vertical_ball_flight_modifier = 1,
    vertical_ball_movement = 0;

int horizontal_ball_flight_modifier = 1,
    horizontal_ball_movement = 0,
    horizontal_movement = 0;

int last_x = 0,
    last_y = 0;

// Promenljive za skor
int score = 0, count = 1, game = 1;

GLubyte fish[] = {
    0x00,
    0x60,
    0x01,
    0x00,
    0x00,
    0x90,
    0x01,
    0x00,
    0x03,
    0xf8,
    0x02,
    0x80,
    0x1c,
    0x37,
    0xe4,
    0x40,
    0x20,
    0x40,
    0x90,
    0x40,
    0xc0,
    0x40,
    0x78,
    0x80,
    0x41,
    0x37,
    0x84,
    0x80,
    0x1c,
    0x1a,
    0x04,
    0x80,
    0x03,
    0xe2,
    0x02,
    0x40,
    0x00,
    0x11,
    0x01,
    0x40,
    0x00,
    0x0f,
    0x00,
    0xe0,
};

// Return a random float in the range 0.0 to 1.0.
GLfloat randomFloat()
{
    return (GLfloat)rand() / RAND_MAX;
}

/**
 * Funkcija za pokretanje programa
 * Uzima argumente iz linije
 */
int main(int argc, char **argv)
{
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
    glutIdleFunc(displayGame);
    glutMainLoop();
}

/**
 * Funkcija za hvatanje korisnickog inputa
 */
void keyboard(unsigned char key, int x, int y)
{
    left = -200 + 200 * (moved_right - moved_left);
    right = 200 + 200 * (moved_right - moved_left);

    // Ako smo dosli do levog kraja ekrana
    if (left == -600)
    {
        if (key == 100)
            moved_right++;
    }

    // Ako smo dosli do desnog kraja ekrana
    else if (right == 600)
    {
        if (key == 97)
            moved_left++;
    }

    // Ako imamo gde da odemo
    else
    {
        if (key == 97)
            moved_left++;
        if (key == 100)
            moved_right++;
    }
    if (key == 115)
    {
        game = 0;
    }
    // Poziv za update
    glutPostRedisplay();
}

/**
 * Init igre
 */
void initGame()
{
    // Debljina
    glPointSize(3.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Velicina ekrana
    gluOrtho2D(-620.0, 620.0, -340.0, 340.0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // (Actually, this one is the default)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
}

void displayGame()
{
    // Display animation
    if (game == 1)
    {
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Crvene linije
        int col = 0;
        for(col = 0; col <= 140; col++){
            glColor3f(3 / 255.0f, (252 - col) / 255.0f, (240 - col) / 255.0f);
            sprintf(string, "Press S to start");
            drawText(string, -120, 80);
            drawText(string, -121, 80);
            drawText(string, -119, 80);
            Sleep(10);
            glutSwapBuffers();
        }
         for(col = 0; col <= 140; col++){
            glColor3f(3 / 255.0f, (12 + col) / 255.0f, col / 255.0f);
            sprintf(string, "Press S to start");
            drawText(string, -120, 80);
            drawText(string, -121, 80);
            drawText(string, -119, 80);
            Sleep(10);
            glutSwapBuffers();
        }

    }

    // Display game
    if (game == 0)
    {
        // Pozadina crna
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Crvene linije
        glColor3f(3 / 255.0f, 252 / 255.0f, 240 / 255.0f);
        // tacka za krug
        int x, y, k;

        // Pokretanje lopte
        for (k = 0; k <= 15; k += 5)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_LINE_STRIP);

            // i nam je ugao, r nam je random faktor
            float i = 0;

            vertical_movement = vertical_movement + 6;
            horizontal_movement = horizontal_movement + 4;
            //nacrtamo krug na (0,12), iterated up to 2*pi, i.e., 360 degree
            while (i <= 2 * pi)
            {
                y = 12 + 20 * cos(i);
                x = 20 * sin(i);
                i = i + 0.000100;

                last_x = x;
                last_y = y;

                if (vertical_movement == 288 && vertical_ball_movement == 0)
                {
                    vertical_ball_flight_modifier = -1;
                    vertical_movement = -288;
                    vertical_ball_movement = 1;
                    score++;
                }
                if (vertical_movement == 288 && vertical_ball_movement == 1)
                {
                    vertical_ball_flight_modifier = 1;
                    vertical_movement = -288;
                    vertical_ball_movement = 0;
                }
                // horizontal_ball_movement 0 desno, 1 levo
                if (horizontal_movement == 580 && horizontal_ball_movement == 0)
                {
                    horizontal_ball_flight_modifier = -1;
                    horizontal_movement = -580;
                    horizontal_ball_movement = 1;
                }
                if (horizontal_movement == 580 && horizontal_ball_movement == 1)
                {
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
            glColor3f(3 / 255.0f, 252 / 255.0f, 240 / 255.0f);
            glVertex2i(-600, -320);
            glVertex2i(-600, 320);
            glVertex2i(600, 320);
            glVertex2i(600, -320);
            glEnd();

            // these four points draws smaller rectangle which is for catching ball
            glBegin(GL_POLYGON);
            glColor3f(3 / 255.0f, 252 / 255.0f, 240 / 255.0f);
            left = -200 + 200 * (moved_right - moved_left);
            right = 200 + 200 * (moved_right - moved_left);
            glVertex2i(left, -315);
            glVertex2i(left, -295);
            glVertex2i(right, -295);
            glVertex2i(right, -315);
            glColor3f(1.0f, 0.0f, 0.0f);
            glEnd();

            sprintf(string, "%d", score);
            drawText(string, 0, 80);
            drawText(string, 1, 80);
            drawText(string, -1, 80);

            // Da li je lopta udarena
            if ((vertical_ball_flight_modifier * vertical_movement) == 276)
            {
                if ((left > ((-1 * horizontal_ball_flight_modifier * horizontal_movement) + 20)) || (right < (-1 * horizontal_ball_flight_modifier * horizontal_movement) - 20))
                {
                    printf("Kraj price, pod mac bato !!!\nSkor ti je :\t%d\n", score);
                    printf("Levo pomerio:\t%d\n", moved_left);
                    printf("Desno pomerio:\t%d\n", moved_right);
                    play_death_animation();
                }

                else
                {
                    glBegin(GL_POLYGON);
                    glColor3f(1.0f, 0.0f, 0.0f);
                    left = -200 + 200 * (moved_right - moved_left);
                    right = 200 + 200 * (moved_right - moved_left);
                    glVertex2i(left, -315);
                    glVertex2i(left, -295);
                    glVertex2i(right, -295);
                    glVertex2i(right, -315);
                    glColor3f(1.0f, 0.0f, 0.0f);
                    glEnd();
                }
            }
            glutSwapBuffers();
        }
    }
}

void drawText(char *string, int x, int y)
{
    char *c;
    glPushMatrix();
    glTranslatef(x, y, 0);
    if(game == 1) glScalef(0.3, 0.3, 1);
    else glScalef(1, 1, 1);
    for (c = string; *c != '\0'; c++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
}

void play_death_animation()
{
    int num = 0;
    glClear(GL_COLOR_BUFFER_BIT);
    for (num = 0; num < 500; num += 1)
    {
        glBegin(GL_LINE_STRIP);
        printf("smrt");
        glVertex2i((last_x - horizontal_ball_flight_modifier * horizontal_movement), (last_y - vertical_ball_flight_modifier * vertical_movement));
        glEnd();

        // these four points draws outer rectangle which determines window
        glBegin(GL_LINE_LOOP);
        glRotatef(30, 0, 0, 0);
        glColor3f(3 / 255.0f, 252 / 255.0f, 240 / 255.0f);
        glVertex2i(-600, -320);
        glVertex2i(-600, 320);
        glVertex2i(600, 320);
        glVertex2i(600, -320);
        glEnd();

        // these four points draws smaller rectangle which is for catching ball
        glBegin(GL_POLYGON);
        glColor3f(3 / 255.0f, 252 / 255.0f, 240 / 255.0f);
        left = -200 + 200 * (moved_right - moved_left);
        right = 200 + 200 * (moved_right - moved_left);
        glVertex2i(left, -315);
        glVertex2i(left, -295);
        glVertex2i(right, -295);
        glVertex2i(right, -315);
        glColor3f(1.0f, 0.0f, 0.0f);
        glEnd();
        Sleep(10);
        glutSwapBuffers();
    }
    exit(0);
}
