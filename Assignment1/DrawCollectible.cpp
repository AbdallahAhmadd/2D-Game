//
//  DrawCollectible.cpp
//  Assignment1
//
//  Created by NANNA on 15/10/2024.
//

#include "DrawCollectible.hpp"
#define GL_SCIENCE_DEPRECATION
#include <GLUT/glut.h>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

void drawGemCollectible(int x, int y, float width, float height) {
    
    // Set the main color to a bright yellow for better contrast against the blue sky
    glColor3f(1.0, 0.8, 0.0);  // Golden yellow color
    
    // Draw the main quadrilateral part of the gem
    glBegin(GL_QUADS);
    glVertex2f(x - width / 2, y);
    glVertex2f(x + width / 2, y);
    glVertex2f(x + width / 3, y + height);
    glVertex2f(x - width / 3, y + height);
    glEnd();
    
    // Set the color for the upper triangle part of the gem to a lighter yellow
    glColor3f(1.0, 1.0, 0.5);  // Light yellow
    
    glBegin(GL_TRIANGLES);
    glVertex2f(x - width / 3, y + height);
    glVertex2f(x + width / 3, y + height);
    glVertex2f(x, y + height + (height / 2));
    glEnd();
    
    // Set the color for the lower triangle part of the gem to an orange color
    glColor3f(1.0, 0.5, 0.0);  // Bright orange
    
    glBegin(GL_TRIANGLES);
    glVertex2f(x - width / 2, y);
    glVertex2f(x + width / 2, y);
    glVertex2f(x, y - height / 2);
    glEnd();
}
