//
//  DrawPowerUp.cpp
//  Assignment1
//
//  Created by NANNA on 15/10/2024.
//

#include "DrawPowerUp.hpp"
#define GL_SCIENCE_DEPRECATION
#include <GLUT/glut.h>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

void drawRect(int x, int y, int w, int h) {
    glColor3d(0,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}


void drawPowerUp1(int x, int y, int width, int height) {
    float halfWidth = width / 2.0;
    float halfHeight = height / 2.0;

   
    glColor3f(1.0, 0.8, 0.2);
    glBegin(GL_POLYGON);
    glVertex2f(x, y + halfHeight);
    glVertex2f(x - halfWidth, y);
    glVertex2f(x, y - halfHeight);
    glVertex2f(x + halfWidth, y);
    glEnd();

   
    glColor3f(1.0, 0.5, 0.0);
    float squareSize = width / 4.0;
    float squareX = x - squareSize / 2;
    float squareY = y - squareSize / 2;
    drawRect(squareX, squareY, squareSize, squareSize);

    // Metallic lines: Bronze-like color
    glColor3f(0.8, 0.5, 0.2);  // Bronze
    glBegin(GL_LINES);

    // Midpoints of the square
    float squareTopMidX = squareX + squareSize / 2;
    float squareTopMidY = squareY + squareSize;

    float squareBottomMidX = squareX + squareSize / 2;
    float squareBottomMidY = squareY;

    float squareLeftMidX = squareX;
    float squareLeftMidY = squareY + squareSize / 2;

    float squareRightMidX = squareX + squareSize;
    float squareRightMidY = squareY + squareSize / 2;

    // Draw the metallic lines
    glVertex2f(squareTopMidX, squareTopMidY);
    glVertex2f(x, y + halfHeight);

    glVertex2f(squareBottomMidX, squareBottomMidY);
    glVertex2f(x, y - halfHeight);

    glVertex2f(squareLeftMidX, squareLeftMidY);
    glVertex2f(x - halfWidth, y);

    glVertex2f(squareRightMidX, squareRightMidY);
    glVertex2f(x + halfWidth, y);

    glEnd();

    // Glowing points: Bright yellow for highlights
    glColor3f(1.0, 0.9, 0.4);  // Bright yellow
    glPointSize(8.0);  // Slightly larger point size
    glBegin(GL_POINTS);

    // Midpoints for glowing effect
    float midTopX = (squareTopMidX + x) / 2;
    float midTopY = (squareTopMidY + (y + halfHeight)) / 2;
    glVertex2f(midTopX, midTopY);

    float midBottomX = (squareBottomMidX + x) / 2;
    float midBottomY = (squareBottomMidY + (y - halfHeight)) / 2;
    glVertex2f(midBottomX, midBottomY);

    float midLeftX = (squareLeftMidX + (x - halfWidth)) / 2;
    float midLeftY = (squareLeftMidY + y) / 2;
    glVertex2f(midLeftX, midLeftY);

    float midRightX = (squareRightMidX + (x + halfWidth)) / 2;
    float midRightY = (squareRightMidY + y) / 2;
    glVertex2f(midRightX, midRightY);

    glEnd();
}


void drawPowerUp2(int x, int y, int width, int height) {
    int ArrowHeight = height * 0.8;

    // Draw the main rectangle with a glowing gold color
    glColor3f(1.0f, 0.85f, 0.2f);  // Gold for energy power-up
    drawRect(x, y, width, height);

    // Draw the central arrow line in vibrant red-orange to indicate energy
    glColor3f(1.0f, 0.4f, 0.0f);  // Red-orange streak of energy
    glBegin(GL_LINES);
    glVertex2d(x + (width / 2), y + 10);
    glVertex2d(x + (width / 2), y + ArrowHeight);
    glEnd();

    // Draw the arrow tips as a line strip in bright white to show energy movement
    glColor3f(1.0f, 1.0f, 1.0f);  // Bright white for accents
    glBegin(GL_LINE_STRIP);
    glVertex2d(x + 0.2 * width, y + ArrowHeight - (0.3 * ArrowHeight));
    glVertex2d(x + (width / 2), y + ArrowHeight);
    glVertex2d(x + 0.8 * width, y + ArrowHeight - (0.3 * ArrowHeight));
    glEnd();

    // Draw the upward triangle (boost effect) with a gradient of orange-red
    glColor3f(1.0f, 0.6f, 0.2f);  // Orange-red for energy boost
    glBegin(GL_TRIANGLES);
    glVertex2d(x, y + height);
    glVertex2d(x + width / 2, y + height + 20);  // Boosting upward
    glVertex2d(x + width, y + height);
    glEnd();

    // Add a glow effect around the power-up using a faint yellow outline
    glColor3f(1.0f, 0.9f, 0.4f);  // Faint yellow glow
    glLineWidth(2.0f);  // Thicker line for glow effect
    glBegin(GL_LINE_LOOP);
    glVertex2f(x - 5, y - 5);
    glVertex2f(x + width + 5, y - 5);
    glVertex2f(x + width + 5, y + height + 25);
    glVertex2f(x - 5, y + height + 25);
    glEnd();
}
