# Developing a C++ State Machine Class
## Finished Video
[Finished Video](https://youtu.be/fDkzkp8z66M)
## Description
Finite state machines are a great way to visualize, code, and troubleshoot complex machine behavior.  I created a simple C++ state machine class to use when developing and testing my tournament Line Racer robot.  This video demos the C++ Mealy State Machine class by using it to code an Arduino traffic light on the Wokwi website.

Please consider supporting this project at https://patreon.com/tournamentrobotics to gain full access to the construction and programming guides described in these videos.
## Script
Hi. My name is Dave and I'm developing a series of robotic challenges that will help students learn about coding and problem solving.

I recently printed and assembled a simple line-following robot for use in the Line Racer competition.  

This robot maneuvers using two wheels and has a pair of IR sensors mounted to the front of the chassis that allow it to follow a winding line.

My next step is to program the robot using the Arduino coding environment.

In this video I'll demonstrate a C++ class that I created to help program the robot using a finite state machine.

Finite state machines are wonderful programming devices that allow you to design and code complex mechanical behavior in a visual and intuitive manner.

There are many variations on state machines.  However, they all work by creating a network of inter-connected states that the program transits in response to environmental ques.

The type of state machine that I'll be using for my robot is known as a Mealy State Machine because actions are implemented as the program transitions between states rather than in the states themselves.

Let's go over to the Obsidian web page, which I created for my StateMachine class, and I'll show you how it works.

This C++ class essentially allows you to create a state machine in which the transition from one state to the next is triggered by a single Boolean event.

Depending on whether the event is true or false, the program will transition to one of two events and execute various actions in the process, such as setting a timer or activating a servo motor.

Although this is a simple mechanism, it can encode some very complex behaviors.

I'd like to use the example of a traffic light to demonstrate how I intend to design and program my robots using a state machine.

The traffic light will periodically cycle through green, yellow, and red lights.  Pressing a walk request button will prompt the traffic light to abort a green cycle and immediately signal the traffic to come to a stop.

The first thing you need to do in designing a state machine is identify the actions the robot will take to affect it's environment.  In the case of the traffic light, the device will either...

... (1) do nothing at all, (2) set a timer for each light cycle, or (3) turn the each of the lights on or off!

I've given each of these actions a three letter designator, which will make it easier to represent in the state diagram and resulting Arduino code.

Next, we need to define the events that will cause the traffic light to transition from one state to the next.  In this example, I've identified five Boolean events.

These include timer alarms for each of the lights that will indicate when a light has been on for the required amount of time.

There's also a walk request signal that is true whenever a pedestrian is pressing the walk request button.

Finally, an "Always True" event will be used to force a transition from one state to another.

As with the actions, I've assigned a three letter code to each of the five events.

Now that we've identified all possible actions and events, we need to create a state diagram that shows how the events trigger actions and guide the transition from one state to the next.

Here's what a state machine might look like for the our traffic light.

Each state is represented by a box that contains a unique state number in parenthesis and a coded Boolean event that will be used to trigger the transition to another state.

The transitions are represented by two arrows.  One arrow indicates the response that will be taken to a true event and the other shows what happens when a false event is detected.

Each arrow also lists one or more actions that will be performed as the program moves between states.

Notice that every state has two arrows coming out of it, even if one of those arrows points right back to the state that it started started from.  

These return arrows are generally accompanied with a NULL action, indicating that the state machine does nothing during this transition.

It's also important to point out that every state machine will start at state ZERO and move forward from there.

In our case, state ZERO listens to the "Always True" event and automatically proceeds directly to state ONE.  In the process, it turns on the green light and resets the green light timer.

The traffic light will then oscillate between states ONE and FOUR while it waits for either the green timer alarm or the walk request indicator to pop true and send the program to state TWO.

On the way to state TWO, the traffic light will turn off the green light, activate the yellow light, and reset the yellow light timer.

State TWO listens for the yellow timer alarm and moves to state THREE only when the alarm becomes true.  During this transition, it turns off the yellow light, flips on the red light, and resets the red light timer.

State THREE will listen for the red timer alarm and send control back to state ONE when the event becomes true, switching on the green light and it's timer in the process.

That's it for the state diagram.  

So, let's jump over to the Wokwi website and I'll show you how I use the StateMachine class to convert this state diagram into an Arduino program.

For those of you who aren't familiar with Wokwi, this is a free and absolutely amazing online tool that allows you to model an Arduino circuit and see how your code effects its performance.

On the right side of the screen is my traffic light circuit, which connects three LEDs and a walk request button to the Arduino Nano.

The left side of the screen shows the code that I created to implement the traffic light state machine, which we just discussed.

I begin the script by including the StateMachine, Timer, and Sensor classes that are used in the program.  All three of these classes are available here on Wokwi and on my Obsidian website.

Next, I define identifiers for each of the Arduino pins that receive or transmit signals to the various peripherals.

I also have a section to create each of the objects that will be used in this code. These include the state machine, the red, yellow, and green timers, and the walk button.  

When setting up each of the timers, I give it a predefined countdown interval in milliseconds.

Starting on line 18, I create action handles for each of the state machine actions and save them as integer constants.

I do the same for event handles in lines 33-40.

These handles come directly from the lists of actions and events that I identified when designing the state machine.

In the setup portion of the script, I link each of the LEDs and the walk button to specific pins on the Arduino board.

This is also where I construct the state machine by defining each of the states.

The addState function accepts accepts six state-specific parameters which indicate:

(1) The number of the state and the event that the state uses to choose and exit path,

(3) The destination-state and actions for a true event, and finally

(4) The destination-state and actions for a false event.

Note that when specifying multiple actions you do so by mathematically adding the action handles together.  This works because each action handle encodes a single bit in an integer number.

The data for each state is easily copied directly from the state diagram that we created earlier.

Finally, the loop script cycles through three different sections that iteratively:

(1) Log events by retrieving Boolean values from the timer and button objects,

(2) Call upon the StateMachine object to evaluate and advance the state pointer based on these events, and finally

(3) Implement any actions that the state machine is calling for by invoking functions associated with the LEDs and timer objects.

When I press the play button, Wokwi compiles the code and runs it on the simulated circuit.

As intended, the state machine iteratively activates the green, yellow, and red traffic lights. 

If you press the walk button while the the green light is active, the program will immediately abort the green cycle and activate the yellow and read lights to stop traffic.

And that's it.  That's all there is to designing and coding a state machine on the Arduino!

The great thing about using state machines is that they're visually intuitive, highly adaptable, and easy to troubleshoot by manually stepping through the state diagram.

They can also be built up to encode far more complex behaviors than those shown here.

You can quickly sketch out state diagrams on paper, identify one that works for your application, and code it on the Arduino using the StateMachine class I've presented here.

In the coming weeks I'll be using this StateMachine class to develop, test, and implement different functions in the Line Racer robot that I recently constructed.  

As I progress, I'll continue posting my code on the Obsidian website and documenting my efforts in these short videos.  

So please subscribe and follow along as I guide you through my process of developing and testing a Line Racer tournament robot!

Thanks for listening :)
