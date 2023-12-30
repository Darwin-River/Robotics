One of the easiest ways to design, visualize, and program complex robot behaviors is through the use of finite state machines. 

A finite state machine is an abstract model that can be used for organizing a robot’s behavior around a number of distinct states and transitions, which cause the code to progress from one state to the next.

There are two basic kind of finite state machines:
* In Moore State Machines the actions that a robot performs are dictated by the state that it is entering. Moore machines are generally easier to construct but require more states to encode the same behaviors as a Mealy machine.
* In Mealy State Machines, actions occur during the transition between states and nothing happens while the robot is residing in a particular state.  Although, Mealy machines can be more concise than Moore machines, they are often not as intuitive to construct.

When designing a state machine, begin by identifying the tasks that you want the machine to perform. Then, map out the states and transitions that will get the bot to its goal.

## Using Mermaid to generate FSMs
You can make a state diagram using a free online tool called [[Mermaid]], which allows you to use a simple scripting language to create state diagrams and other types of graphically rendered thought maps. 