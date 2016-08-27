#include <Aria.h>

#include "wander.h"
// Implementation

// Constructor
wander::wander() : ArAction("Wander")
{
  speed = 50; // Set the robots speed to 50 mm/s. 200 is top speed
}

// Body of action
ArActionDesired * wander::fire(ArActionDesired d)
{
 desiredState.reset(); // reset the desired state (must be done)

 double closestObstacle;
 double angleToClosestObstacle;
 double robotRadius = 300.00; // Should be able to get this from myRobot->getRobotRadius() but there is a problem with C++ Express - works in professionsal

 closestObstacle = myRobot->checkRangeDevicesCumulativePolar(-60,60,&angleToClosestObstacle) - robotRadius; // Find the closest

 if(closestObstacle < 300.0) desiredState.setDeltaHeading(15); // IF within 30cm turn 15 degrees

 desiredState.setVel(speed); // set the speed of the robot in the desired state

 ArLog::log(ArLog::Normal,"Robot(%.2f,%.2f,%.2f) Dist: %.2f\tAngle: %.2f",myRobot->getX(),myRobot->getY(),myRobot->getTh(),closestObstacle,angleToClosestObstacle);

 return &desiredState; // give the desired state to the robot for actioning
}


