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

// Promenljive za skor
int score = 0, count = 1, game = 1;

//promenljive za kisu
float slowdown = 2.0;
float velocity = 1.0;


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

    if (key == 113)
        exit(1);
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


}

void displayGame()
{

    if (game == 2)
    {
        play_death_animation();
    }
    // Display animation
    if (game == 1)
    {
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Crvene linije
        int col = 0;
        for (col = 0; col <= 2; col++)
        {

            if (col % 2 == 0)
            {
                glColor3f(3 / 255.0f, 252 / 255.0f, 240 / 255.0f);
                sprintf(string, "Press S to start");
                drawText(string, -120, 80);
                drawText(string, -121, 80);
                drawText(string, -119, 80);
                Sleep(50);
            }

            else
            {
                glColor3f(1.0f, 0.0f, 0.0f);
                sprintf(string, "Press S to start");
                drawText(string, -120, 80);
                drawText(string, -121, 80);
                drawText(string, -119, 80);
                Sleep(50);
            }
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

            // Prozor
            glBegin(GL_LINE_LOOP);
            glColor3f(3 / 255.0f, 252 / 255.0f, 240 / 255.0f);
            glVertex2i(-600, -320);
            glVertex2i(-600, 320);
            glVertex2i(600, 320);
            glVertex2i(600, -320);
            glEnd();

            // Slider
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
                    game = 2;
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

/**
 * Funkcija za ispis teksta na ekran preko GLUT
 */
void drawText(char *string, int x, int y)
{
    char *c;
    glPushMatrix();
    glTranslatef(x, y, 0);
    if (game == 1)
        glScalef(0.3, 0.3, 1);
    else
        glScalef(1, 1, 1);
    for (c = string; *c != '\0'; c++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
}

/**
 * Funkcija za prikaz death screen-a
 */
void play_death_animation()
{

    // Init partikala
    for (loop = 0; loop < MAX_PARTICLES; loop++)
    {
        initParticles(loop);
    }
    draw_rain();

}

/**
 * Crtanje kise
 */
void draw_rain()
{
    glutPostRedisplay();
    float x, y;
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(3 / 255.0f, 252 / 255.0f, 240 / 255.0f);

    glClear(GL_COLOR_BUFFER_BIT);
    for (loop = 0; loop < MAX_PARTICLES; loop = loop + 2)
    {
        if (par_sys[loop].alive == 1)
        {
            Sleep(100);
            x = par_sys[loop].xpos;
            y = par_sys[loop].ypos;

            // Crtanje
            glBegin(GL_LINES);
            glVertex2f(x, y);
            glVertex2f(x, y + 0.5);
            glEnd();

            par_sys[loop].ypos += par_sys[loop].vel / (slowdown * 1000);
            par_sys[loop].vel += par_sys[loop].gravity;

            // Skidaj
            par_sys[loop].life -= par_sys[loop].fade;
            if (par_sys[loop].ypos <= -315) par_sys[loop].life = -1.0;

            // Ako nestaju, opet init
            if (par_sys[loop].life < 0.0) initParticles(loop);
        }
        glutSwapBuffers();
    }
}

/**
 * Funkcija za inicijalizaciju partikala
 * @param i - index particla
 */
void initParticles(int i) {
    par_sys[i].alive = 1;
    par_sys[i].life = 1.0;
    par_sys[i].fade = (float)(rand()%100)/1000.0f+0.003f;
    par_sys[i].xpos = (float) (rand() % 1240) - 620;
    par_sys[i].ypos = 340.0;
    printf("cord: x:%f, y:%f", par_sys[i].xpos, par_sys[i].ypos);
    par_sys[i].vel = velocity;
    par_sys[i].gravity = -0.8;
}

