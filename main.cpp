#include "Aria.h"
#include "wander.h"
#include"scattergram.h"
using namespace std;
int main(int argc, char **argv)
{
  Aria::init();
  ArArgumentParser argParser(&argc, argv);
  argParser.loadDefaultArguments();
  ArRobot robot;
  ArRobotConnector robotConnector(&argParser, &robot);


  if(!robotConnector.connectRobot())
  {
    ArLog::log(ArLog::Terse, "Could not connect to the robot.");
    if(argParser.checkHelpAndWarnUnparsed())
    {
        // -help not given, just exit.
        Aria::logOptions();
        Aria::exit(1);
    }
  }


  // Trigger argument parsing
  if (!Aria::parseArgs() || !argParser.checkHelpAndWarnUnparsed())
  {
    Aria::logOptions();
    Aria::exit(1);
  }

  ArKeyHandler keyHandler;
  Aria::setKeyHandler(&keyHandler);
  robot.attachKeyHandler(&keyHandler);

  ArLog::log(ArLog::Normal,"This program will make the robot wander around and develop a map. It uses some avoidance\n"
  "actions if obstacles are detected, otherwise it has a\n"
  "constant forward velocity.\n\nPress CTRL-C or Escape to exit.");
  
  ArSonarDevice sonar;
  robot.addRangeDevice(&sonar);

  robot.runAsync(true);


  // turn on the motors, turn off amigobot sounds
  robot.enableMotors();
  robot.comInt(ArCommands::SOUNDTOG, 0);

  // add a set of actions that combine together to effect the wander behavior
  ArActionStallRecover recover;
  ArActionBumpers bumpers;
  wander wander; 
  scattergram scattergrams;
 
 //render render;
  //render.display(scattergrams.rightpoints);
  robot.addAction(&scattergrams, 50);
  robot.addAction(&recover, 100);
  robot.addAction(&bumpers, 75);
  robot.addAction(&wander, 50);
  
  // wait for robot task loop to end before exiting the program
  robot.waitForRunExit();
  
  Aria::exit(0);
}
