//
//  DrawObtacle.cpp
//  Assignment1
//
//  Created by NANNA on 17/10/2024.
//

#include "DrawObtacle.hpp"
#define GL_SCIENCE_DEPRECATION
#include <GLUT/glut.h>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <cmath>

void drawObstacle(int x, int y, int w, int h) {
    
    glColor3d(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
    
    glColor3d(0.5, 0.5, 0.5);
    glBegin(GL_TRIANGLES);
    glVertex2d(x, y + h);
    glVertex2d(x + (w / 4), y + h + 50);
    glVertex2d(x + (w/2), y + h);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex2d(x+(w/2), y + h);
    glVertex2d(x + (w/2)+(w/4), y + h + 50);
    glVertex2d(x + w, y + h);
    glEnd();
}

