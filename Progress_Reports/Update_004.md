# Designing and Assembling the Line Racer Robot
I recently purchased the full set of electronic parts for the prototype Line Racer robot from Amazon.

These parts consist of: 
* An Arduino Nano microcontroller and an I/O board that will make it easier to connect jumper wires from the motors and sensors.
* A pair of servo motors that conveniently came with a couple wheels.
* Two UV sensors, which can be used to detect and follow a black line.
* AND a microphone that will allow the robot to begin racing when it hears a starter whistle.
* I also purchased a package of jumper cables for connecting the sensors to the Arduino controller
* AND machine screws for mounting the sensors to the chassis.
* The system will be powered by a battery back that holds four double-A batteries.

I've decided to use an open source parametric modeling application, called Open Ess-CAD, to design the chassis for my robot.

I like Open Ess-CAD because it allows you to create 3D structures using a simple coding language.  

Then, once you've coded the basic structure, you can easily adjust the dimensions by altering the parameters so that they fit your parts.

The opensource software also makes it easy for others to take models that were created in Open Ess-CAD and adapt them for their own use.

It took me a several iterations of printing and adjusting the chassis design before I ended up with something that would snuggly hold the the servos, sensors, and circuit board.

Having finally printed a chassis that works well with the electronic parts, I quickly assembled the prototype robot by:

Installing the servo motors in the holes on either side of the chassis and affixing the wheels to each of the motor shafts.

I then used machine screws to mount the downward-facing UV sensors and upward-facing mic to the raised hardpoints on the front of the chassis;

I also installed the Arduino Nano into the I/O board and used jumper cables to connect the servos and sensors to the appropriate voltage, ground, and signal pins on the I/O board.

Finally, I inserted the circuit board and battery pack into the slots on the top of the chassis and placed a marble in the recess on the bottom of the robot to serve as a temporary pivot wheel until I can think of something better.

I've posted a complete list of parts AND the Open Ess-CAD code for creating the chassis on the Obsidian website, which I've shared with my Patreon sponsors.

Next, I'll work on developing  and testing sensor classes in the Arduino programming language that will allow the robot to monitor signals from its environment.