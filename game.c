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
int score = 0, count = 1;

// Teksture
void* image_data[2];  // Pointer to raw RGB data for textures.
int image_width[2];   // Widths of texture images.
int image_height[2];

char *texture_file_names[1] = { // file names for the files from which texture images are loaded
    "res\\images\\slider.bmp",
    ""};

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

    // Poziv za update
    glutPostRedisplay();
}

/**
 * Init igre
 */
void initGame()
{

    // Pozadina crna
    glClearColor(153/255.0, 230/255.0, 255/255.0, 0.0);

    // Crvene linije
    glColor3f(1.0f, 0.0f, 0.0f);

    // Debljina
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Velicina ekrana
    gluOrtho2D(-620.0, 620.0, -340.0, 340.0);

    glEnable(GL_TEXTURE_2D);
    //loadTextures();

    // Random modifier
    srand((unsigned)time(NULL));
}

void displayGame()
{

    // tacka za krug
    int x, y, k;
    srand((unsigned)time(NULL));
    float random_trajectory_modifier = (float)rand() / RAND_MAX;
    printf("rand faktor:\t%f\n", random_trajectory_modifier);

    // Pokretanje lopte
    for (k = 0; k <= 5; k += 5)
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
        if ((vertical_ball_flight_modifier * vertical_movement) == 276)
        {
            if ((left > ((-1 * horizontal_ball_flight_modifier * horizontal_movement) + 20)) || (right < (-1 * horizontal_ball_flight_modifier * horizontal_movement) - 20))
            {
                printf("Kraj price, pod mac bato !!!\nSkor ti je :\t%d\n", score);
                printf("Levo pomerio:\t%d\n", moved_left);
                printf("Desno pomerio:\t%d\n", moved_right);
                exit(0);
            }
        }
        glutSwapBuffers();
    }
}

void loadTextures()
{
    /**
   for (i = 0; i < 2; i++) {
        loadBMP_custom(texture_file_names[i], i);
        if (image_data[i])
            printf("Texture image loaded from file %s, size %dx%d\n", texture_file_names[i], image_width[i], image_height[i]);

        else printf("Failed to get texture data from %s\n", texture_file_names[i]);
    }
    */
   int i = 0;
    loadBMP_custom(texture_file_names[i], i);
}

void loadBMP_custom(const char *imagepath, int i)
{
    // Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos = 0;     // Position in the file where the actual data begins
    unsigned int width, height = 0;
    unsigned int imageSize = 0; // = width*height*3
    // Actual RGB data
    unsigned char *data;

    // Open the file
    FILE *file = fopen(imagepath, "rb");
    if (!file)
    {
        printf("Image could not be opened: %s\n", texture_file_names[i]);
        exit(1);
    }

    // Citanje
    if (fread(header, 1, 54, file) != 54)
    { // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        exit(1);
    }

    // Validacija header-a
    if (header[0] != 'B' || header[1] != 'M')
    {
        printf("Not a correct BMP file\n");
        exit(1);
    }

    // Citanje
    dataPos = *(int *)&(header[0x0A]);
    imageSize = *(int *)&(header[0x22]);
    width = *(int *)&(header[0x12]);
    height = *(int *)&(header[0x16]);

    // Some BMP files are misformatted, guess missing information
    if (imageSize == 0)
        imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos == 0)
        dataPos = 54; // The BMP header is done that way

    // Create a buffer
    data[imageSize] = NULL;

    // Read the actual data from the file into the buffer
    fread(data, 1, imageSize, file);

    image_data[i] = data;
    image_width[i] = width;
    image_height[i] = height;

    //Everything is in memory now, the file can be closed
    fclose(file);

    /**
    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    */
}

