#include <stdlib.h>
#include <cmath>
#define GL_SCIENCE_DEPRECATION
#include <GLUT/glut.h>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "DrawPlayer.hpp"
#include "DrawCollectible.hpp"
#include "DrawPowerUp.hpp"
#include "GameBoundaries.hpp"
#include "DrawObtacle.hpp"
#include "SoundManager.hpp"

int obstacleXposition=1920;
int GemXposition=1920;
int playerXPosition=0;
int DodgeObstacleXposition=1920;
int PowerUp1Xposition = 1920;
int PowerUp2Xposition=1920;
int playerYPosition=0;
int UpVelocity=22.5f;
float velocity = 0.0f;
float gravity=-1.3f;
bool isDodged=false;
bool isJumping= false;
bool isShield=false;
int Score = 0;
int ObstacleProb=70;
int CollectibleProb=20;
int PowerUpProb=10;
int screenWidth = 1920;
int totalTimeInSeconds = 120;
int shieldTimeLeft = 0;
int jumpPowerUpTimeLeft=0;
float playerScaleX=1;

int BounceDirection=1;
int BounceOffset=0;
float ScaleXAnimation=1;
float ScaleYAnimation=1;
static bool gameOverPlayed = false;
static bool gameWinPlayed = false;
float AssetMovingSpeed=8;
float GameSpeed = 8;
int GameFrequency=2000;


struct Asset {
    int type;
    int x;
    int option;
};
std::vector<Asset> assets;

void updatePlayerPosition();
void countdownTimer(int value);

void generateObstacle(int x) {
    drawObstacle(x, 265, 50, 8);
}

void generateDodgeObstacle(int x) {
    glPushMatrix();
    glTranslated(x, 405, 0);
    glRotated(180, 1, 0, 0);
    drawObstacle(0, 0, 50, 8);
    glPopMatrix();
}

void generateCollectible(int x) {
    glPushMatrix();
    glTranslatef(x, 420, 0);
    glScalef(ScaleXAnimation, ScaleYAnimation, 1.0f);
    drawGemCollectible(0, 0, 30, 30);
    glPopMatrix();
}
void generatePower1(int x) {
    drawPowerUp1(x, 300+BounceOffset, 70, 70);
}
void generatePower2(int x){
    drawPowerUp2(x, 420+BounceOffset, 50, 50);
}

void countdownTimer(int value) {
    if (totalTimeInSeconds > 0) {
        totalTimeInSeconds--;
        glutTimerFunc(1000, countdownTimer, 0);
    }
    glutPostRedisplay();
}

void JumpdownTimer(int x) {
    if (jumpPowerUpTimeLeft > 0) {
        jumpPowerUpTimeLeft--;
        glutTimerFunc(1000, JumpdownTimer, 0);
    } else {
        UpVelocity = 22.5;
        jumpPowerUpTimeLeft = 0; // Ensure the timer is zero.
       
    }
    glutPostRedisplay();
}
void ShieldTimer(int value) {
    if (shieldTimeLeft > 0) {
        shieldTimeLeft--;  // Decrease the shield timer.
        glutTimerFunc(1000, ShieldTimer, 0);  // Call the function every second.
    } else {
        isShield = false;
    }
    glutPostRedisplay();  // Redraw the screen.
}



void spe(int k, int x,int y)
{
   
    if (k== GLUT_KEY_UP && !isJumping){
        isJumping=true;
        velocity=UpVelocity;
    }
    if(k==GLUT_KEY_DOWN && !isDodged && !isJumping){
        playerScaleX=0.75;
        isDodged=true;
        
    }
    
    glutPostRedisplay();
}
void SpecialKeyUp(int k, int x, int y) {
    if (k == GLUT_KEY_DOWN && isDodged) {
        playerScaleX =1;  // Reset the player's position after dodging
        isDodged = false;  // Reset dodge state
    }
    
    glutPostRedisplay();
}

void output(int x, int y, float r, float g, float b, void* font, const char* string) {
    glColor3f(r, g, b);  // Set text color
    
    glRasterPos2f(x,y);
    
    int len = strlen(string);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(font, string[i]);  // Render each character
    }
}

void emitAsset(int random,int Option) {
    int type=-1;
    
    if(random<ObstacleProb) type=0;
    else
        if(random<ObstacleProb+CollectibleProb) type=1;
        else
            type=2;
    
    Asset newAsset;
    newAsset.type = type;
    newAsset.option=Option;
    newAsset.x = screenWidth;  // Start at the right edge of the screen
    assets.push_back(newAsset);  // Store the new asset
}


void drawAsset(const Asset& asset) {
    switch (asset.type) {
        case 0:
            if(asset.option==1)
                generateObstacle(asset.x);
            else
                generateDodgeObstacle(asset.x);
            break;
        case 1:
            generateCollectible(asset.x);
            break;
        case 2:
            if(asset.option==1)
                generatePower1(asset.x);
            else
                generatePower2(asset.x);
            break;
    }
}


void Timer(int value) {
    int randomType = rand() % 100;
    int randomOption= rand()%2;
    emitAsset(randomType,randomOption);
    glutTimerFunc(GameFrequency, Timer, 0);
}

void UpdateScore(int value) {
    if(HeartsAvail>0 && totalTimeInSeconds>=60 ){
        Score += 10;
        glutPostRedisplay();
        glutTimerFunc(1000, UpdateScore, 0);
    }
    else if(HeartsAvail>0 &&totalTimeInSeconds>0){
        Score += 20;
        glutPostRedisplay();
        glutTimerFunc(1000, UpdateScore, 0);
    }
}
bool checkCollision(const Asset& asset) {
    
    int playerX = 20;
    int playerY = 250 + playerYPosition;
    int playerWidth = 100;
    int playerHeight = isDodged ? 100 : 150;
    
    
    int assetWidth, assetHeight, assetY;
    
    if (asset.type == 1) {
        assetWidth = 30;
        assetHeight = 30;
        assetY = 420;
    }
    else if (asset.type == 0 && asset.option == 1) {
        assetWidth = 50;
        assetHeight = 58;
        assetY = 265;
    }
    else if (asset.type == 0 && asset.option == 0) {
        assetWidth = 50;
        assetHeight = 58;
        assetY = 360;
        if (isDodged) {
            return false;
        }
    }
    else if (asset.type == 2 && asset.option == 1) {
        assetWidth = 20;
        assetHeight = 20;
        assetY = 265;
    }
    else {
        assetWidth = 50;
        assetHeight = 60;
        assetY = 420;
    }
    
    bool collisionX = playerX < asset.x + assetWidth &&
    playerX + playerWidth > asset.x;
    
    bool collisionY = playerY < assetY + assetHeight &&
    playerY + playerHeight > assetY;

    
    if (collisionX && collisionY) {
        if (asset.type == 2 && asset.option==0) {
               UpVelocity = 30;
               jumpPowerUpTimeLeft=5;
               glutTimerFunc(1000, JumpdownTimer, 0);
           }
        if(asset.type==2 && asset.option==1){
            isShield = true;
            shieldTimeLeft = 5;
            glutTimerFunc(1000, ShieldTimer, 0);
        }
        
        if(asset.type==0 && !isShield){
            HeartsAvail--;
        }
        if(asset.type==1){
            Score+=100;
        }
       
        return true;
       }

       return false;  // No collision
   }

void IncreaseGameSpeed(int value){
    if(AssetMovingSpeed<GameSpeed){
        AssetMovingSpeed+=0.1;
        if(AssetMovingSpeed>GameSpeed){
            AssetMovingSpeed=GameSpeed;
        }
        glutTimerFunc(30, IncreaseGameSpeed, 0);
    }
}



void updatePlayerPosition() {
    
    if (HeartsAvail != 0 && totalTimeInSeconds==0 && gameWinPlayed==false) {
        playSound("Gamewin");
        gameWinPlayed=true;
    }
    
    if (HeartsAvail==0 && gameOverPlayed==false) {
        playSound("Gameover");
        gameOverPlayed=true;
    }
    // Increase speed based on remaining time
       if (totalTimeInSeconds <= 120 && totalTimeInSeconds > 90) {
           GameFrequency=2000;
           AssetMovingSpeed = 8;  // Initial speed.
           GameSpeed=8;
       } else if (totalTimeInSeconds <= 90 && totalTimeInSeconds > 60) {
           GameFrequency=1500;
           GameSpeed=10;
           IncreaseGameSpeed(0);
       } else if (totalTimeInSeconds <= 60 && totalTimeInSeconds > 30) {
           GameFrequency=1000;
           GameSpeed=12;
           IncreaseGameSpeed(0);
       } else if (totalTimeInSeconds <= 30) {
           GameFrequency=650;
           GameSpeed=14.0;
           IncreaseGameSpeed(0);
       }
    
    
    //powerups animation
    if (BounceOffset >= 20 && BounceDirection > 0) {
        BounceDirection = -1;
    } else if (BounceOffset <= 0 && BounceDirection < 0) {
        BounceDirection = 1;
    }
    BounceOffset += BounceDirection;

    //collectible animation
    static float scaleSpeed = 0.01f;
       ScaleXAnimation += scaleSpeed;
       if (ScaleXAnimation >= 1.1f || ScaleXAnimation <= 0.9f) {
           scaleSpeed = -scaleSpeed;
       }
       ScaleYAnimation = ScaleXAnimation;
    
    
    bool collidedWithObstacle = false;
       for (auto assetIterator = assets.begin(); assetIterator != assets.end(); ) {
           if(HeartsAvail==0 || totalTimeInSeconds==0)
               AssetMovingSpeed=0;
            
           else
               assetIterator->x -= AssetMovingSpeed;
               

           if (checkCollision(*assetIterator)) {
               if (assetIterator->type == 0) {
                   if (!isShield){
                       collidedWithObstacle = true;
                       playSound("hit");
                   }
                        
               }
               else{
                   playSound("collect");
                   assetIterator = assets.erase(assetIterator);
               }
               ++assetIterator;
           }
           else if (assetIterator->x < -50) {
               assetIterator = assets.erase(assetIterator);
           }
           else {
               ++assetIterator;  // Move to the next asset
           }
       }

     
    if (collidedWithObstacle) {
            for (auto& asset : assets) {
                asset.x += 500;
            }
        for (auto it = assets.begin(); it != assets.end(); ) {
            if (it->x > 1600) {
                it = assets.erase(it);
            } else {
                ++it;
            }
        }
            AssetMovingSpeed = AssetMovingSpeed*0.7;
            collidedWithObstacle = false;
            glutTimerFunc(1000, IncreaseGameSpeed, 0);
    }

    
    if (isJumping) {
        playerYPosition += velocity;
        velocity += gravity;
        
        if (playerYPosition <= 0) {
            playerYPosition = 0;
            isJumping = false;
            velocity = 0.0f;
        }
    }
    
    glutPostRedisplay();
}

void renderBoldStrokeText(float x, float y, float scale, float r, float g, float b, const char* string, int thickness = 3) {
    glColor3f(r, g, b);
    glPushMatrix();

   
    for (int i = -thickness; i <= thickness; ++i) {
        for (int j = -thickness; j <= thickness; ++j) {
            glPushMatrix();
            glTranslatef(x + i * 0.5f, y + j * 0.5f, 0); // Adjust the offsets for boldness
            glScalef(scale, scale, scale);
            for (const char* c = string; *c != '\0'; ++c) {
                glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
            }
            glPopMatrix();
        }
    }

    glPopMatrix();
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawSkyWithStars();
    
    DrawHealthBar();
    for (const auto& asset : assets) {
        drawAsset(asset);
    }
    
    glPushMatrix();

   
    glTranslatef(0, playerYPosition, 0);

 
    glTranslatef(0,250 , 0);
    glScaled(1, playerScaleX, 1);
    glTranslatef(0, -250, 0);

    
    drawPlayer(70, 350, 20);

    glPopMatrix();
    
    int minutes = totalTimeInSeconds / 60;
    int seconds = totalTimeInSeconds % 60;
    char timeString[16];
    sprintf(timeString, "Time:%02d:%02d", minutes, seconds);
    
    output(1700, 850, 1.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, timeString);
    char scoreText[16];
    
    sprintf(scoreText, "Score: %d", Score);
    output(1700, 900, 1.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, scoreText);
 
    if (isShield && shieldTimeLeft > 0) {
        char shieldText[16];
        sprintf(shieldText, "Shield: %d", shieldTimeLeft);
        output(1700, 800, 1.0f, 1.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, shieldText);  // Display in yellow.
    }

    if (jumpPowerUpTimeLeft > 0) {
        char JumpText[16];
        sprintf(JumpText, "Jump PowerUp: %d", jumpPowerUpTimeLeft);
        output(1700, 750, 1.0f, 1.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, JumpText);  // Display in light pink.
    }
    
    
    if (HeartsAvail <= 0) {
        char GameOver[16];
        sprintf(GameOver, "Game Over!");
        renderBoldStrokeText(200, 1080/2, 2, 1, 0, 0, GameOver);
       
    }
    if (HeartsAvail != 0 && totalTimeInSeconds==0) {
        char GameWin[32];
        char EndScore[16];
        sprintf(GameWin, "Winner Winner!");
        sprintf(EndScore, "Score:%d",Score);
        renderBoldStrokeText(60, 1080/2, 2, 0, 1, 0, GameWin);
        renderBoldStrokeText(1000, 1080/4, 1, 1, 0, 0, EndScore);
      
       
    }
    drawGround();
    
    
    glFlush();
}

int main(int argc, char** argr) {
    
    glutInit(&argc, argr);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    glutInitWindowSize(1920, 1080);
    
    glutInitWindowPosition(100, 100);
    glutTimerFunc(0, Timer, 0);
    glutTimerFunc(1000,UpdateScore,0);
    glutTimerFunc(1000,countdownTimer,0);
   
    glutCreateWindow("Nannas Game");
    glutIdleFunc(updatePlayerPosition);
    loadSounds();
    playSound("main");
    glutDisplayFunc(Display);
    glutSpecialFunc(spe);
    glutSpecialUpFunc(SpecialKeyUp);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    gluOrtho2D(0.0,1920.0, 0.0, 1080.0);
    
    
    
    glutMainLoop();
    
    return 0;
}
