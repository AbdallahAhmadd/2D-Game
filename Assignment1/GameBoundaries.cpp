#include "GameBoundaries.hpp"
#define GL_SCIENCE_DEPRECATION
#include <GLUT/glut.h>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <cmath>
#include <ctime>

int HeartsAvail = 5;

struct Bird {
    float x, y;
    float size;
};

// Array of fixed bird positions and sizes
Bird birds[5] = {
    {600.0f, 900.0f, 50.0f},   // Bird 2
    {1000.0f, 950.0f, 45.0f},  // Bird 3
    {1400.0f, 850.0f, 35.0f},  // Bird 4
    {1200.0f, 1000.0f, 50.0f}   // Bird 5
};

void drawStreetLamp(float x, float y) {
    // Draw the pole of the street lamp
    glColor3f(0.5f, 0.5f, 0.5f); // Grey color
    glBegin(GL_QUADS);
    glVertex2f(x - 5, y);
    glVertex2f(x + 5, y);
    glVertex2f(x + 5, y + 50);
    glVertex2f(x - 5, y + 50);
    glEnd();

    // Draw the lamp head
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color for the light
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 180; i++) { // Semi-circle for lamp head
        float angle = i * (M_PI / 180);
        float cx = x + cos(angle) * 20;
        float cy = (y + 50) + sin(angle) * 20;
        glVertex2f(cx, cy);
    }
    glEnd();
}

void drawCircle(float x_0,float y_0,int radius, int ang){
    glBegin(GL_TRIANGLE_FAN);
    for (int i=0 ; i <= 100 ;i++)
    {
        float angle = ang * 0.01 * M_PI * i;
        float x= x_0 + radius * cos(angle);
        float y= y_0 + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawHealth(){
    glColor3f(0.7, 0, 0);
    drawCircle(800, 700, 10,1);
    drawCircle(820, 700, 10,1);
    glBegin(GL_TRIANGLES);
    glVertex2d(790, 700);
    glVertex2d(810, 680);
    glVertex2d(830, 700);
    glEnd();
}
void DrawHealthBar() {
    for (int i=0;i<HeartsAvail;i++){
        glPushMatrix();
        glTranslated(750+(i*50), 300, 0);
        drawHealth();
        glPopMatrix();
    }
}

void drawStone(float x, float y, float size) {
    // Set a greyish color for the stone
    glColor3f(0.5f, 0.5f, 0.5f);  // Grey color

    // Draw the stone using a triangle strip to create an irregular shape
    glBegin(GL_TRIANGLE_STRIP);
    
    glVertex2f(x, y);                   // Bottom-left corner
    glVertex2f(x + size, y);             // Bottom-right corner
    glVertex2f(x + size / 2, y + size);  // Top-middle corner
    glVertex2f(x + size * 1.5, y + size / 2);  // Far-right corner
    
    glEnd();
}


void drawGround() {
    
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2d(0, 0);
    glVertex2d(1920, 0);
    glVertex2d(1920, 265);
    glVertex2d(0, 265);
    glEnd();
    
    // Draw top and bottom boundary lines (solid white lines)
    glColor3f(1.0f, 1.0f, 1.0f);  // White color
    
    // Top boundary line
    glBegin(GL_LINES);
    glVertex2d(0, 260);
    glVertex2d(1920, 260);
    glEnd();
    
    // Bottom boundary line
    glBegin(GL_LINES);
    glVertex2d(0, 5);
    glVertex2d(1920, 5);
    glEnd();
    
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(3.0f);
    
    
    glBegin(GL_LINES);
    for (int x = 0; x < 1920; x += 40) {
        glVertex2d(x, 130);
        glVertex2d(x + 20, 130);
    }
    glEnd();
    
        drawStreetLamp(200, 10);  // Example position for a street lamp
        drawStreetLamp(600, 10);
        drawStreetLamp(1000,10);
        drawStreetLamp(1400, 10);
        drawStreetLamp(1800, 10);
    
       drawStone(100, 70, 30);  // Example position for the stone
       drawStone(300, 200, 40);
       drawStone(700, 100, 35);
       drawStone(1620, 80, 50);
        
}


void drawSkyWithStars() {
    // Crimson sky background
    glColor3f(0.565f, 0.835f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2d(0, 265);  // Start at y = 265 to simulate a horizon
    glVertex2d(1920, 265);
    glVertex2d(1920, 1080);  // Full height for the sky
    glVertex2d(0, 1080);
    glEnd();
    
    // Set the color for the stars (white/silver)
    glColor3f(0.9f, 0.9f, 0.9f);  // Light silver color
    glPointSize(6.0f);  // Make stars a bit larger
    
    // Draw random stars across the sky
    glBegin(GL_POINTS);
    srand(time(NULL));  // Seed for random star placement
    for (int i = 0; i < 50; i++) {  // Let's create 100 stars
        float x = rand() % 1420;  // Random x-position
        float y = 865 + (rand() % (1080 - 265));  // Random y-position above the horizon
        
        glVertex2f(x, y);
    }
    glEnd();
    
    
    glColor3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < 5; i++) {
        float birdX = birds[i].x;
        float birdY = birds[i].y;
        float birdSize = birds[i].size;
        
        glBegin(GL_LINE_STRIP);
        
      
        glVertex2f(birdX, birdY);
        glVertex2f(birdX + (birdSize / 3), birdY - (birdSize / 4));
        glVertex2f(birdX + (birdSize / 2), birdY - (birdSize / 3));
        
        
        glVertex2f(birdX + (2 * birdSize / 3), birdY - (birdSize / 4));
        glVertex2f(birdX + birdSize, birdY);
        
        glEnd();
        
        
    }
    
    // Set cloud color to white
       glColor3f(1.0f, 1.0f, 1.0f);

       // Begin drawing the cloud using GL_POLYGON
       glBegin(GL_POLYGON);

       // Define vertices to create a curved cloud shape
       glVertex2f(200.0f, 900.0f);  // Leftmost part
       glVertex2f(220.0f, 920.0f);  // Curving upward
       glVertex2f(260.0f, 930.0f);  // Peak of the curve
       glVertex2f(300.0f, 920.0f);  // Slightly down
       glVertex2f(340.0f, 930.0f);  // Another peak
       glVertex2f(380.0f, 910.0f);  // Curve back down
       glVertex2f(400.0f, 900.0f);  // Bottom right part
       glVertex2f(370.0f, 880.0f);  // Bottom curve
       glVertex2f(330.0f, 870.0f);  // Continuing the curve
       glVertex2f(290.0f, 880.0f);  // Bottom middle
       glVertex2f(250.0f, 870.0f);  // Bottom left
       glVertex2f(220.0f, 880.0f);  // Left curve

       // End of cloud shape
       glEnd();
    
    
}
