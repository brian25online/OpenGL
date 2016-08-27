#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<ctime>
#include<Aria.h>


struct vertex2D {
	int x;
	int y;
};

class scattergram: public ArAction // Class action inherits from ArAction
{
public:
	scattergram(); // Constructor
	virtual ~scattergram() {};  // Destructor
	virtual ArActionDesired * fire(ArActionDesired d); // Body of the action
	ArActionDesired desiredState; // Holds state of the robot that we wish to action
	std::ofstream myfile;
	std::ofstream mypolar;
	std::vector<vertex2D> leftpoints;
	std::vector<vertex2D> rightpoints;
	vertex2D points;
	vertex2D pointsone;
	//render renderone;
	int xleft;
	int xright;
	int yleft;
	int yright;

	int xleftone;
	int xrightone;
	int yleftone;
	int yrightone;

	int xlefttwo;
	int xrighttwo;
	int ylefttwo;
	int yrighttwo;
protected:
};

