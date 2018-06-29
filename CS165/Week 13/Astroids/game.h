/***********************************************************************
* Header File:
*    Game : Defines the Game class for Astroids
* Author:
*    Ryan Dockstader
* Summary:
*    Defines the Game class for Astroids
************************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>

#include "uiInteract.h"
#include "point.h"
#include "ship.h"
#include "rocks.h"
#include "bullet.h"

#define CLOSE_ENOUGH 15
#define AMOUNT_OF_LIVES 5

/*********************************************
* GAME
* Defines the Game class for Astroids
*********************************************/
class Game
{
public:
	//Constructors
	Game(Point tl, Point br); 

	// Other Public Methods
	void handleInput(const Interface & ui);
	void advance();
	void draw(const Interface & ui);
	void reset();

private:
	Point topLeft;
	Point bottomRight;
	std::vector<Rock*> rocks;
	std::vector<Bullet*> bullets;
	Ship* ship;
	int score;
	int lives;
	bool hasWon;

	float getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const;

	// Private Advance Functions
	void advanceBullets();
	void advanceRocks();
	void advanceShip();

	// Private Draw Functions
	void drawBullets();
	void drawRocks();
	void drawShip();
	void drawScore();
	void drawLives();

	// Private Clean Up Functions
	void cleanUpZombies();
	void cleanUpShip();
	void cleanUpBullets(bool deleteAll);
	void cleanUpRocks(bool deleteAll);

	// Private Collision Handlers
	void handleCollisions();
	void handleBulletCollisions();
	void handleShipCollisions();

	// Initializers
	void initializeRocks();
	void initializeVariables();


};


#endif /* GAME_H */
