/*************************************************************
 * File: game.cpp
 * Author: Br. Burton
 *
 * Description: Contains the implementations of the
 *  method bodies for the game class.
 *
 * Please DO NOT share this code with other students from
 *  other sections or other semesters. They may not receive
 *  the same code that you are receiving.
 *************************************************************/

#include "game.h"

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "bird.h"
#include "sacredBird.h"
#include "toughBird.h"

#include <vector>
#include <iostream>
using namespace std;

#define OFF_SCREEN_BORDER_AMOUNT 5


/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game :: Game(Point tl, Point br)
 : topLeft(tl), bottomRight(br), rifle(br)
{
   // Set up the initial conditions of the game
   score = 0;

   bird = NULL;
}

/****************************************
 * GAME DESTRUCTOR
 ****************************************/
Game :: ~Game()
{
	if (bird)
		delete bird;
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
	if (!isPaused)
	{
		advanceBullets();
		advanceBird();

		handleCollisions();
		cleanUpZombies();
	}
}

/***************************************
 * GAME :: ADVANCE BULLETS
 * Go through each bullet and advance it.
 ***************************************/
void Game :: advanceBullets()
{
   // Move each of the bullets forward if it is alive
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i].isAlive())
      {
         // this bullet is alive, so tell it to move forward
         bullets[i].advance();
         
         if (!isOnScreen(bullets[i].getPoint()))
         {
            // the bullet has left the screen
            bullets[i].kill();
         }
         
      }
   }
}

/**************************************************************************
 * GAME :: ADVANCE BIRD
 *
 * 1. If there is no bird, create one with some probability
 * 2. If there is a bird, and it's alive, advance it
 * 3. Check if the bird has gone of the screen, and if so, "kill" it
 **************************************************************************/
void Game :: advanceBird()
{
   if (bird == NULL)
   {
      // there is no bird right now, possibly create one
      
      // "resurrect" it will some random chance
      if (random(0, 30) == 0)
      {
          //create a new bird
		  switch (random(1, 4))
		  {
		  case 1:
			  bird = createBird();
			  break;
		  case 2:
			  bird = createSacredBird();
			  break;
		  case 3:
			  bird = createToughBird();
			  break;
		  }
         
      }
   }
   else
   {
      // we have a bird, make sure it's alive
      if (bird != NULL && bird->isAlive())
      {
         // move it forward
         bird->advance();
         // check if the bird has gone off the screen
         if (!isOnScreen(bird->getPoint()))
         {
            // We have missed the bird
            bird->kill();
         }
      }
   }
}

/**************************************************************************
 * GAME :: CREATE BIRD
 * Create a bird of a random type according to the rules of the game.
 **************************************************************************/
Bird* Game :: createBird()
{
   Bird* newBird = NULL;

   // TODO: Fill this in
	newBird = new Bird();

   
   return newBird;
}

SacredBird * Game::createSacredBird()
{
	return new SacredBird();
}

ToughBird * Game::createToughBird()
{
	return new ToughBird();
}

/**************************************************************************
 * GAME :: IS ON SCREEN
 * Determines if a given point is on the screen.
 **************************************************************************/
bool Game :: isOnScreen(const Point & point)
{
   return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
      && point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
      && point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
      && point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/**************************************************************************
 * GAME :: HANDLE COLLISIONS
 * Check for a collision between a bird and a bullet.
 **************************************************************************/
void Game :: handleCollisions()
{
   // now check for a hit (if it is close enough to any live bullets)
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i].isAlive())
      {
         // this bullet is alive, see if its too close

         // check if the bird is at this point (in case it was hit)
         if (bird != NULL && bird->isAlive())
         {
            // BTW, this logic could be more sophisiticated, but this will
            // get the job done for now...
            if (fabs(bullets[i].getPoint().getX() - bird->getPoint().getX()) < CLOSE_ENOUGH
                && fabs(bullets[i].getPoint().getY() - bird->getPoint().getY()) < CLOSE_ENOUGH)
            {
               //we have a hit!
               
               // hit the bird
               int points = bird->hit();
               score += points;
			   //std::cout << "Points: " << points << std::endl;
               
               // the bullet is dead as well
               bullets[i].kill();
            }
         }
      } // if bullet is alive  
   } // for bullets
}

/**************************************************************************
 * GAME :: CLEAN UP ZOMBIES
 * Remove any dead objects (take bullets out of the list, deallocate bird)
 **************************************************************************/
void Game :: cleanUpZombies()
{
   // check for dead bird
   if (bird != NULL && !bird->isAlive())
   {
	   bird = NULL;
   }
  
   // Look for dead bullets
   vector<Bullet>::iterator bulletIt = bullets.begin();
   while (bulletIt != bullets.end())
   {
      Bullet bullet = *bulletIt;
      // Asteroids Hint:
      // If we had a list of pointers, we would need this line instead:
      //Bullet* pBullet = *bulletIt;
      
      if (!bullet.isAlive())
      {
         // If we had a list of pointers, we would need to delete the memory here...
         
         
         // remove from list and advance
         bulletIt = bullets.erase(bulletIt);
      }
      else
      {
         bulletIt++; // advance
      }
   }
   
}

/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game :: handleInput(const Interface & ui)
{
   // Change the direction of the rifle
   if (ui.isLeft())
   {
      rifle.moveLeft();
   }
   
   if (ui.isRight())
   {
      rifle.moveRight();
   }
   
   // Check for "Spacebar
   if (ui.isSpace())
   {
      Bullet newBullet;
      newBullet.fire(rifle.getPoint(), rifle.getAngle());
      
      bullets.push_back(newBullet);
   }

   // check for "up"
   if (ui.isUp())
   {
	   isPaused = (isPaused) ? false : true;
   }
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui)
{
   // draw the bird

   // Check if you have a valid bird and if it's alive
	if (bird != NULL && bird->isAlive())
	{
		// then call it's draw method
		bird->draw();
	}
  // draw the rifle
   rifle.draw();
   
   // draw the bullets, if they are alive
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i].isAlive())
      {
         bullets[i].draw();
      }
   }
   
   // Put the score on the screen
   Point scoreLocation;
   scoreLocation.setX(topLeft.getX() + 5);
   scoreLocation.setY(topLeft.getY() - 5);
   
   drawNumber(scoreLocation, score);
   if (isPaused)
   {
	   Point midPoint;
	   midPoint.setX(midPoint.getX() - 5);
	   drawText(midPoint, "PAUSED");
   }
   



}

