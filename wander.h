#ifndef WANDER_H
#define WANDER_H

// Signatures

class wander : public ArAction // Class action inherits from ArAction
{
 public:
   wander(); // Constructor
   virtual ~wander() {}  // Destructor
   virtual ArActionDesired * fire(ArActionDesired d); // Body of the action
   ArActionDesired desiredState; // Holds state of the robot that we wish to action
 protected:
   int speed; // Speed of the robot in mm/s
};

#endif
