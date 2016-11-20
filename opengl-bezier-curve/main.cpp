//
//  main.cpp
//  opengl-bezier-curve
//
//  Created by Ahmed Mohamed on 11/20/16.
//  Copyright © 2016 Ahmed Mohamed. All rights reserved.
//

#include <OpenGl/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <iostream>
#include <math.h>

int p0[2];
int p1[2];
int p2[2];
int p3[2];
int tar=4;


//this is the method used to print text in OpenGL
//there are three parameters,
//the first two are the coordinates where the text is display,
//the third coordinate is the string containing the text to display
void print(int x, int y, char *string)
{
    int len, i;
    
    //set the position of the text in the window using the x and y coordinates
    glRasterPos2f(x, y);
    
    //get the length of the string to display
    len = (int) strlen(string);
    
    //loop to display character by character
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
    }
}

int* bezier(float t, int* p0,int* p1,int* p2,int* p3)
{
    int res[2];
    res[0]=pow((1-t),3)*p0[0]+3*t*pow((1-t),2)*p1[0]+3*pow(t,2)*(1-t)*p2[0]+pow(t,3)*p3[0];
    res[1]=pow((1-t),3)*p0[1]+3*t*pow((1-t),2)*p1[1]+3*pow(t,2)*(1-t)*p2[1]+pow(t,3)*p3[1];
    return res;
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    print(750,500,"Bezier Control Points");
    glColor3f(1,0,0);
    char* p0s [20];
    sprintf((char *)p0s,"P0={%d,%d}",p0[0],p0[1]);
    print(785,450,(char *)p0s);
    glColor3f(0,1,0);
    char* p1s [20];
    sprintf((char *)p1s,"P1={%d,%d}",p1[0],p1[1]);
    print(785,400,(char *)p1s);
    glColor3f(0,0,1);
    char* p2s [20];
    sprintf((char *)p2s,"P2={%d,%d}",p2[0],p2[1]);
    print(785,350,(char *)p2s);
    glColor3f(1,1,1);
    char* p3s [20];
    sprintf((char *)p3s,"P3={%d,%d}",p3[0],p3[1]);
    print(785,300,(char *)p3s);
    
    glPointSize(1);
    glColor3f(1,1,0);
    glBegin(GL_POINTS);
    for(float t=0;t<1;t+=0.001)
    {
        int* p =bezier(t,p0,p1,p2,p3);
        glVertex3f(p[0],p[1],0);
    }
    glEnd();
    glPointSize(9);
    glBegin(GL_POINTS);
    glColor3f(1,0,0);
    glVertex3f(p0[0],p0[1],0);
    glColor3f(0,1,0);
    glVertex3f(p1[0],p1[1],0);
    glColor3f(0,0,1);
    glVertex3f(p2[0],p2[1],0);
    glColor3f(1,1,1);
    glVertex3f(p3[0],p3[1],0);
    glEnd();
    
    glFlush();
}

void mo(int x, int y)
{
    y=600-y;
    if(x<0)
        x=0;
    if(x>700)
        x=700;
    if(y<0)
        y=0;
    if(y>600)
        y=600;
    if(tar==0)
    {
        p0[0]=x;
        p0[1]=y;
    }
    else if(tar==1)
    {
        p1[0]=x;
        p1[1]=y;
    }
    else if(tar==2)
    {
        p2[0]=x;
        p2[1]=y;
    }
    if(tar==3)
    {
        p3[0]=x;
        p3[1]=y;
    }
    glutPostRedisplay();
}

void mou(int b,int s,int x, int y)
{
    y=600-y;
    if(b==GLUT_LEFT_BUTTON && s==GLUT_DOWN)
    {
        if(p0[0]<x+9&&p0[0]>x-9&&p0[1]<y+9&&p0[1]>y-9)
        {
            tar=0;
        }
        else if(p1[0]<x+9&&p1[0]>x-9&&p1[1]<y+9&&p1[1]>y-9)
        {
            tar=1;
        }
        else if(p2[0]<x+9&&p2[0]>x-9&&p2[1]<y+9&&p2[1]>y-9)
        {
            tar=2;
        }
        else if(p3[0]<x+9&&p3[0]>x-9&&p3[1]<y+9&&p3[1]>y-9)
        {
            tar=3;
        }
    }
    if(b==GLUT_LEFT_BUTTON && s==GLUT_UP)
        tar=4;
}

int main(int argc, char** argr) {
    glutInit(&argc, argr);
    
    glutInitWindowSize(1000, 600);
    
    p0[0]=100;
    p0[1]=100;
    
    p1[0]=100;
    p1[1]=500;
    
    p2[0]=500;
    p2[1]=500;
    
    p3[0]=500;
    p3[1]=100;
    
    glutCreateWindow("OpenGL - Bezier Curve Stimulation");
    glutDisplayFunc(Display);
    glutMotionFunc(mo);
    glutMouseFunc(mou);
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    gluOrtho2D(0.0, 1000, 0.0, 600);
    
    glutMainLoop();
    return 0;
}
