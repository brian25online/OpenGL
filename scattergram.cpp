#include "scattergram.h"
#include <iostream>
#include<cstdlib>
#include <stdlib.h>
#include "math.h"
#include <Aria.h>

#include "scattergram.h"

// Implementation

// Constructor
scattergram::scattergram() : ArAction("scattergram")
{
	ArLog::init(ArLog::File, ArLog::Normal, "sg.xls"); // Makes ArLog write to sg.xls
	myfile.open("brian.txt");
	mypolar.open("polar.txt");
	int xleft = 0;
	int xright = 0;
	int yleft = 0;
	int yright = 0;
	int xleftone=0;
	int xrightone=0;
	int yleftone=0;
	int yrightone=0;

	int xlefttwo=0;
	int xrighttwo=0;
	int ylefttwo=0;
	int yrighttwo=0;
}

// Body of action
ArActionDesired * scattergram::fire(ArActionDesired d)
{
	desiredState.reset(); // reset the desired state (must be done)

						  // Get ARIA odometer readings 
	double robotX = myRobot->getX();
	double robotY = myRobot->getY();
	double robotTh = myRobot->getTh(); // (in degrees)

	double leftAngle; // (in degrees)
	double leftDistance = myRobot->checkRangeDevicesCurrentPolar(0.0, 90.0, &leftAngle);
	double rightAngle; // (in degrees)
	double rightDistance = myRobot->checkRangeDevicesCurrentPolar(-90.0, 0.0, &rightAngle);


	// for the left readings get x and y
	xleft = cos(leftAngle*(3.141/180))*(leftDistance);
	yleft = sin(leftAngle*(3.141 / 180))*(leftDistance);
	
	//for the right readings get x and y
	xright = cos(rightAngle*(3.141 / 180))*rightDistance;
	yright = cos(rightAngle*(3.141 / 180))*rightDistance;

	//for the roatation of the left readings 
	xleftone = xleft*(cos(robotTh*(3.141 / 180)) - sin(robotTh*(3.141 / 180)));
	yleftone = yleft*(sin(robotTh*(3.141 / 180)) + cos(robotTh*(3.141 / 180)));

	//for the rotation of the right readings
	xrightone = xright*(cos(robotTh*(3.141 / 180)) - sin(robotTh*(3.141 / 180)));
	yrightone = yright*(sin(robotTh*(3.141 / 180)) + cos(robotTh*(3.141 / 180)));

	//for the translation of the left readings
	xlefttwo = robotX + xleftone;
	ylefttwo = robotY + yleftone;

	//for the translation of the right readinds 
	xrighttwo = robotX + xrightone;
	yrighttwo = robotX + yrightone;

	std::cout << xlefttwo << "\t" << ylefttwo << "\t" << xrighttwo << "\t" << yrighttwo << std::endl;
	myfile << xlefttwo <<"\t"<< ylefttwo <<"\n"<< xrighttwo << "\t"<< yrighttwo << std::endl;


	//store the left points into an STL vector
	pointsone.x = xlefttwo;
	pointsone.y = ylefttwo;
	rightpoints.push_back(pointsone);

	//store the right points into an STL vector 
	points.x = xrighttwo;
	points.y = yrighttwo;
	rightpoints.push_back(points); //store into an STL vector 

	

	

	


	return &desiredState; // give the desired state to the robot for actioning
}

