#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

using namespace std;

// macros
#define PI (2 * acos(0.0))
#define OUTOFTHESCREEN 200

//colmena enemiga
const int rowVal = 3;
const int colVal = 12;

void circle(float radius_x, float radius_y)
{
    int i = 0;
    float angle = 0.0;

    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex3f(cos(angle) * radius_x, sin(angle) * radius_y, 0);
    }
    glEnd();
}

void rectangle(float x, float y, float z, float a, float b, float red, float green, float blue)
{
    glColor3f(red, green, blue);

    glBegin(GL_QUADS);
    {
        glVertex3f(x, y, z);
        glVertex3f(x + a, y, z);

        glVertex3f(x + a, y - b, z);
        glVertex3f(x, y - b, z);
    }
    glEnd();
}
//lineas
void drawAxes()
{

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    {
        glVertex3f(1000, 0, 0);
        glVertex3f(-1000, 0, 0);

        glVertex3f(0, -1000, 0);
        glVertex3f(0, 1000, 0);

        glVertex3f(0, 0, 1000);
        glVertex3f(0, 0, -1000);
    }
    glEnd();
}


void drawGrid()
{
    int i;

    glColor3f(0.6, 0.6, 0.6); //grey
    glBegin(GL_LINES);
    {
        for (i = -8; i <= 8; i++)
        {

            if (i == 0)
                continue; //SKIP the MAIN axes

            //lines parallel to Y-axis
            glVertex3f(i * 10, -90, 0);
            glVertex3f(i * 10, 90, 0);

            //lines parallel to X-axis
            glVertex3f(-90, i * 10, 0);
            glVertex3f(90, i * 10, 0);
        }
    }
    glEnd();
}

void background()
{
    int a = 100; //tamaño
    glBegin(GL_QUADS); //dibujar un cuadrado
    {
        glColor3f(0,0,0.4);
        glVertex3f(a, a, 0);
        glColor3f(0.1, 0, 1);
        glVertex3f(a, -a, 0);
        glColor3f(0.1, 0, 1);
        glVertex3f(-a, -a, 0);
        glColor3f(0,0, 0.4);
        glVertex3f(-a, a, 0);
    }
    glEnd();
}

void cloud(float &initialPosY, float initialPosX, float speed, float scale)
{
    initialPosY -= speed;
    if (initialPosY < -OUTOFTHESCREEN)
    {
        initialPosY = OUTOFTHESCREEN;
    }

    glPushMatrix();
    glScalef(scale, scale, 0);
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glTranslatef(initialPosX, initialPosY, 0),
        circle(12, 15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(initialPosX + 20, initialPosY, 0),
        circle(15, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(initialPosX + 40, initialPosY, 0),
        circle(12, 15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(initialPosX + 10, initialPosY - 10, 0),
        circle(15, 15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(initialPosX + 30, initialPosY - 10, 0),
        circle(15, 15);
    glPopMatrix();

    glPopMatrix();
}

void avion(float x, float y, float z, float scale, float primaryR, float primaryG, float primaryB, float secondaryR, float secondaryG, float secondaryB)
{
    glPushMatrix();
    glScalef(scale, scale, scale);

    // cabeza
    glColor3f(primaryR, primaryG, primaryB);
    glBegin(GL_POLYGON);
    {
        glColor3f(0.2f, 0.0f, 0.0f);
        glVertex3f(x, y, z);
        glColor3f(0.2f, 0.0f, 0.0f);
        glVertex3f(x + 4, y + 8, z);
        glColor3f(0.2f, 0.0f, 0.0f);
        glVertex3f(x + 6, y + 8, z);
        glColor3f(0.2f, 0.0f, 0.0f);
        glVertex3f(x + 10, y, z);
    }
    glEnd();

    // cuerpo
    glColor3f(secondaryR, secondaryG, secondaryB);
    glBegin(GL_QUADS);
    {
        glColor3f(secondaryR, secondaryG, secondaryB);
        glVertex3f(x, y, z);///
        glColor3f(primaryR, primaryG, primaryB);
        glVertex3f(x + 10, y, z); ///
        glColor3f(0.2f, 0.0f, 0.0f); 
        glVertex3f(x + 13, y - 50, z);///
        glColor3f(0.2f, 0.0f, 0.0f);
        glVertex3f(x -3, y - 50, z); ////
    }
    glEnd();

    // ala derecha
   // glColor3f(primaryR, primaryG, primaryB);
    glBegin(GL_POLYGON);
    {
        glColor3f(0.3f, 0.0f, 0.0f);
        glVertex3f(x + 10, y - 10, z);
        glColor3f(0.3f, 0.0f, 0.0f);
        glVertex3f(x + 38, y - 10, z);
        glColor3f(0.3f, 0.0f, 0.0f);
        glVertex3f(x + 38, y - 12, z);
        glColor3f(0.3f, 0.0f, 0.0f);
        glVertex3f(x + 10, y - 30, z);
        glColor3f(0.3f, 0.0f, 0.0f);
    }
    glEnd();

    // cola
   // glColor3f(secondaryR, secondaryG, secondaryB);
    glBegin(GL_POLYGON);
    {
        glColor3f(0.2f, 0.0f, 0.0f);
        glVertex3f(x + 5, y - 40, z); ///
        glColor3f(0.2f, 0.0f, 0.0f);
        glVertex3f(x + 13, y - 63, z); ///
        glColor3f(0.3f, 0.0f, 0.0f);
        glVertex3f(x + 13, y - 65, z); ////
        glColor3f(0.3f, 0.0f, 0.0f);
        glVertex3f(x + 5, y - 53, z);  ////<<<
        glColor3f(0.3f, 0.0f, 0.0f);
        glVertex3f(x - 3, y - 65, z);
        glColor3f(0.3f, 0.0f, 0.0f);
        glVertex3f(x - 3, y - 63, z);
        glColor3f(0.f, 0.0f, 0.0f);
    }
    glEnd();

    /* abajo
    glColor3f(primaryR, primaryG, primaryB);
    glBegin(GL_POLYGON);
    {
        glColor3f(0.5f, 0.0f, 0.0f);
        glVertex3f(x + 10, y - 50, z);
        glColor3f(0.5f, 0.0f, 0.0f);
        glVertex3f(x + 5, y - 60, z);
        glColor3f(0.5f, 0.0f, 0.0f);
        glVertex3f(x, y - 50, z);
    }
    glEnd();
    */
    // ala izquierda
    //glColor3f(primaryR, primaryG, primaryB);
    glBegin(GL_POLYGON);
    {
        glColor3f(0.3f, 0.0f, 0.0f);
        glVertex3f(x, y - 10, z);
        glColor3f(0.3f, 0.0f, 0.0f);
        glVertex3f(x - 28, y - 10, z);
        glColor3f(0.3f, 0.0f, 0.0f);
        glVertex3f(x - 28, y - 12, z);
        glColor3f(0.3f, 0.0f, 0.0f);
        glVertex3f(x, y - 30, z);
        
    }
    glEnd();
    glPopMatrix();
}

void bala(float &initialPosY, float initialPosX, float z)
{
    float posicion = initialPosY;
    if (initialPosY != -300)
    {
        initialPosY += 1;
    }

    glColor3f(0.5, 1, 0);
    glPushMatrix();
    glTranslatef(initialPosX, initialPosY, z),
        circle(2, 2);
    glPopMatrix();






}

void enemy(float x, float y, float z, float red, float green, float blue)
{
    glColor3f(red, green, blue);
   
    glBegin(GL_QUADS);
    {
       
         glColor3f(red, 0, 0);
        glVertex3f(x -2.8, y, z);///
        glColor3f(red, 0, 0);
        glVertex3f(x + 2, y, z); ///
        glColor3f(1, 1, 0);
        glVertex3f(x + 2, y - 2, z);///
        glColor3f(red, 0, 0);
        glVertex3f(x - 3, y - 2, z); ////
    }
    glEnd();
}

void enemyHive(float x, float y, float z)
{
    srand((unsigned)time(NULL));
    for (int row = 0; row < rowVal; row++)
    {
        for (int col = 0; col < colVal; col++)
        {
            float r = ((float)rand() / RAND_MAX);
            float g = ((float)rand() / RAND_MAX);
            float b = ((float)rand() / RAND_MAX);
            enemy(x + 10 * col, y - 10 * row, z, r, g, b);
        }
    }
}
