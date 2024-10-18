//
//  DrawPlayer.cpp
//  Assignment1
//
//  Created by NANNA on 15/10/2024.
//

#include "DrawPlayer.hpp"
#define GL_SCIENCE_DEPRECATION
#include <GLUT/glut.h>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"


void drawCircle(int x, int y, float r) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3d(0, 0, 0);
    GLUquadric *quadObj = gluNewQuadric();
    gluDisk(quadObj, 0, r, 50, 50);
    glPopMatrix();
}


void drawPlayer(int startingX, int startingY, int sizeOfPlayer) {
    // Draw the player's head (circle) with radius sizeOfPlayer
    drawCircle(startingX, startingY, sizeOfPlayer);
    
   
    float antennaLength = sizeOfPlayer;
    
    // Rectangle body dimensions
    float squareBodyWidth = (sizeOfPlayer * 2) * 1.5;  // Width of the rectangle
    float squareBodyHeight = (sizeOfPlayer * 2);       // Height of the rectangle
    glColor3d(0, 0, 0);
    // Draw the antennas as lines
    glBegin(GL_LINES);
    // Right antenna
    glVertex2d(startingX, startingY + sizeOfPlayer);
    glVertex2d(startingX + antennaLength, startingY + sizeOfPlayer + antennaLength);
    
    // Left antenna
    glVertex2d(startingX, startingY + sizeOfPlayer);
    glVertex2d(startingX - antennaLength, startingY + sizeOfPlayer + antennaLength);
    glEnd();
    
    // Draw the rectangle body of the robot
    glBegin(GL_QUADS);
    // Top-left
    glVertex2d(startingX - (0.5 * squareBodyWidth), startingY - sizeOfPlayer);
    
    glVertex2d(startingX + (0.5 * squareBodyWidth), startingY - sizeOfPlayer);
    
   
    glVertex2d(startingX + (0.5 * squareBodyWidth), startingY - sizeOfPlayer - squareBodyHeight);
    
    
    glVertex2d(startingX - (0.5 * squareBodyWidth), startingY - sizeOfPlayer - squareBodyHeight);
    glEnd();
    
    
    glBegin(GL_TRIANGLES);
    
    glVertex2d(startingX, startingY - sizeOfPlayer - squareBodyHeight);  // Tip of the triangle
    
    glVertex2d(startingX - (0.3 * squareBodyWidth), startingY - sizeOfPlayer - squareBodyHeight - (sizeOfPlayer * 1.2));
    
    glVertex2d(startingX + (0.3 * squareBodyWidth), startingY - sizeOfPlayer - squareBodyHeight - (sizeOfPlayer * 1.2));
    glEnd();
    
    
    float middleY = (startingY - sizeOfPlayer) - (0.5 * squareBodyHeight);
    
    
    glBegin(GL_LINE_LOOP);
    
    
    glVertex2d(startingX - (0.5 * squareBodyWidth), middleY);
    glVertex2d(startingX - (0.5 * squareBodyWidth) - (sizeOfPlayer * 0.6), middleY + (sizeOfPlayer * 0.2));
    glVertex2d(startingX - (0.5 * squareBodyWidth) - (sizeOfPlayer * 1.0), middleY);
    glVertex2d(startingX - (0.5 * squareBodyWidth) - (sizeOfPlayer * 0.6), middleY - (sizeOfPlayer * 0.2));
    glVertex2d(startingX - (0.5 * squareBodyWidth), middleY);
    
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    
    
    glVertex2d(startingX + (0.5 * squareBodyWidth), middleY);
    glVertex2d(startingX + (0.5 * squareBodyWidth) + (sizeOfPlayer * 0.6), middleY + (sizeOfPlayer * 0.2));
    glVertex2d(startingX + (0.5 * squareBodyWidth) + (sizeOfPlayer * 1.0), middleY);
    glVertex2d(startingX + (0.5 * squareBodyWidth) + (sizeOfPlayer * 0.6), middleY - (sizeOfPlayer * 0.2));
    glVertex2d(startingX +(0.5 * squareBodyWidth), middleY);
    
    glEnd();
}
