#include "archivos.h"
#include <iostream>
#include <string>

using namespace std;

// variables globales de la nube
float cloudOneY = OUTOFTHESCREEN;
float cloudTwoY = OUTOFTHESCREEN;
float cloudThreeY = OUTOFTHESCREEN;
float cloudFourY = OUTOFTHESCREEN;
float cloudFiveY = OUTOFTHESCREEN;

// game global variables
int INICIAR_JUEG0 = 0; // en cero muestra el menu, 1 se juega
int PUNTOA = 0;
string DETALLES = "";
int gameOverTimer = 0;

// posecion del avion
float avionInicialPosX = -5;
float avionPosX = avionInicialPosX;
float avionD = false;


// posiciones de bala
float balaInicialPosX;
float balainicialPosY = -45;
bool getBulletInitial = false;

// LOS METEORITOS
float meteoroInPosY = 60;
float tiempoMet = 0;

void showText(string text, float r, float g, float b, float x, float y, float z)
{
    glColor3f(r, g, b);
    glRasterPos3f(x, y, z);
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
}

void moveClouds() // nuves
{
    cloud(cloudOneY, 50, 0.4, 0.4);
    cloud(cloudTwoY, -50, 0.5, 0.7);
    cloud(cloudThreeY, -50, 0.9, 0.6);
    cloud(cloudFourY, 80, 0.6, 0.8);
    cloud(cloudFiveY, -100, 0.4, 0.4);
}

void iniciarD(string msg)
{
    meteoroInPosY = 60;
    tiempoMet = 0;
    DETALLES = msg;
    INICIAR_JUEG0 = 0;
    avionPosX = avionInicialPosX;
}

void specialKeyListener(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        if (INICIAR_JUEG0 == 1 && avionPosX < OUTOFTHESCREEN)
        {
            avionPosX += 4;
        }
        break;
    case GLUT_KEY_LEFT:
        if (INICIAR_JUEG0 == 1 && avionPosX > -OUTOFTHESCREEN)
        {
            avionPosX -= 4;
        }
        break;
    case GLUT_KEY_UP:
        if (INICIAR_JUEG0 == 1)
        {
            PUNTOA += 1;
            avionD = true;
        }
    default:
        break;
    }
}

void keyboardListener(unsigned char key, int x, int y)
{
    switch (key)
    {

    case '1': // COMENZAR
        if (INICIAR_JUEG0 != 1)
        {
            INICIAR_JUEG0 = 1;
            DETALLES = "";
            gameOverTimer = 0;
            PUNTOA = 0;
        }
        break;
    case '2': // TERMINAAR
        if (INICIAR_JUEG0 != 0)
        {
            iniciarD("quit");
        }
        break;
        /*   case 'S':
               if (INICIAR_JUEG0 != 1)
               {
                   INICIAR_JUEG0 = 1;
                   GAME_OVER = "";
                   gameOverTimer = 0;
                   SCORE = 0;
               }
               break;
           case 'Q':
               if (INICIAR_JUEG0 != 0)
               {
                   resetGame("quit");
               }
               break;
       */
    default:
        break;
    }
}

void display()
{
    // limpiar la pantalla
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0); //de color negro
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // carga la matriz correcta - matriz
    glMatrixMode(GL_MODELVIEW);

    //iniciar matriz
    glLoadIdentity();

    // posición de la cámara,
    gluLookAt(0, 0, 100, 0, 0, 0, 0, 1, 0);

    //de nuevo seleccione MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);

    //funciones de dibujo de objetos

    if (INICIAR_JUEG0 == 0)
    {
        showText("VAMOS A JUGARRR", 0, 0, 0, -22, 24, 1);
        showText("Presiona 1 para comenzar", 0, 0, 0, -25, 10, 1);
        showText("Presiona 2 para terminar", 0, 0, 0, -25, 0, 1);

        avion(-5, -20, 0, 0.5, 0, 0, 0, 1, 1, 1);

        if (DETALLES.compare("iniciar") == 0)
        {
            if (gameOverTimer < 5000)
            {
                showText("¡GANASTE!", 1, 0, 0, -15, -65, 1);
                showText("Puntuacion: ", 0, 0, 0, -14, -75, 1);
                showText(to_string(PUNTOA), 0, 0, 0, 12, -75, 1);

                rectangle(-18, -55, 0, 35, 25, 1, 1, 1);
                gameOverTimer += 10;
            }
            else
            {
                DETALLES = "";
                gameOverTimer = 0;
                PUNTOA = 0;
            }
        }
        /* else if (DETALLES.compare("Ganste") == 0)
         {
             if (gameOverTimer < 5000)
             {
                 showText("¡GANASTE!", 1, 0, 1, -10, -65, 1);
                 showText("PUNTUA: ", 0, 0, 0, -14, -75, 1);
                 showText(to_string(PUNTOA), 0, 0, 0, 12, -75, 1);
                 gameOverTimer += 10;
             }
             else
             {
                 DETALLES = "";
                 gameOverTimer = 0;
                 PUNTOA = 0;
             }
         } */
        else if (DETALLES.compare("quit") == 0)
        {
            if (gameOverTimer < 5000)
            {
                showText("¡GANASTE!", 1, 0, 1, -10, -65, 1);
                showText("PUNTUACION: ", 0, 0, 0, -12, -75, 1);
                //  showText(to_string(SCORE), 0, 0, 0, 12, -75, 1);
                rectangle(-18, -55, 0, 40, 25, 1, 1, 1);
                gameOverTimer += 10;
            }
            else
            {
                DETALLES = "";
                gameOverTimer = 0;
                PUNTOA = 0;
            }
        }
    }
    else
    {
        showText("PRESIONE 2 PARA SALIR", 1, 1, 1, -78, 72, 3);
        //rectangle(-80, 80, 0, 45, 10, 0, 0.1, 0.1);

        showText("PUNT: ", 1, 1, 1, 51, 72, 1);
        showText(to_string(PUNTOA), 1, 1, 1, 72, 72, 1);
        //rectangle(50, 80, 0, 30, 10, 0, 0.1, 0.1);

        if (tiempoMet < 1500)
        {
            enemyHive(-60, meteoroInPosY, 0);
            tiempoMet += 10;
        }
        else
        {
            tiempoMet = 0;
            tiempoMet -= 10;

            if (meteoroInPosY < -10)
            {
                // juego perdido
                iniciarD("iniciar");
            }
        }
        if (avionD == true)
        {
            if (getBulletInitial == false)
            {
                balaInicialPosX = ((avionPosX + 5.0) * (3.0 / 10.0));
                getBulletInitial = true;
            }
            if (balainicialPosY >= meteoroInPosY - 10)
            {
                avionD = false;
                getBulletInitial = false;
                balainicialPosY = -45;
                float bulletOutScreen = -300;
                bala(bulletOutScreen, -300, 1);


                if (PUNTOA >= 15)
                {
                    // Game Over
                    iniciarD("Ganste");
                }
            }
            else
            {
                bala(balainicialPosY, balaInicialPosX, 1);
            }
        }
        avion(avionPosX, -180, 0, 0.3, 0, 0, 0, 1, 1, 1);
    }

    moveClouds(); // nuves
     //drawAxes();
    // drawGrid();
    background();


    //AGREGUE esta línea al final si usa doble búfer(es decir, GL_DOUBLE)
    glutSwapBuffers();
}

void animate()
{
    //codes for any changes in Models, Camera

    glutPostRedisplay(); // marks the current window as needing to be redisplayed
}

void init()
{
    //clear the screen
    glClearColor(0, 0, 0, 0);

    //load the PROJECTION matrix
    glMatrixMode(GL_PROJECTION);

    //initialize the matrix
    glLoadIdentity();

    //give PERSPECTIVE parameters
    gluPerspective(80, 1, 1, 5000);
}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB); //Depth, Double buffer, RGB color

    glutCreateWindow("JUEGO DE AVION");

    init();

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display); //display callback function
    glutIdleFunc(animate);    //what to do in the idle time (when no drawing is occuring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);

    glutMainLoop(); //The main loop of OpenGL
    cout << PUNTOA;

    return 0;
}
