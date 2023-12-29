<img src="/Images/IR_Sensor.jpg" width="200" align="right">The IR sensor is great for Arduino obstacle avoidance or line-following applications.

As with most Arduino-compatible sensors, the 3-5 V unit has power, round, and signal pins, which plug directly into the corresponding sensor pins on the [Arduino Nano IO Shield](IO_Shield.md).

The sensor has two built-in LEDs.  One will come on when power is applied to the unit and the other will light up when the sensor detects an object or light surface.

There's also an adjustable potentiometer on the sensor that allows you to set the threshold at which the device will responds to a proximity signal.

The sensor pin should be connected directly to one of the input pins (A0-A7) on the Arduino.

The voltage on the signal pin will jump from low to high  when an object breaches a distance threshold set by the potentiometer.  A similar voltage transition will occur when a downward facing IR sensor passes from a dark to a light surface.

The best way to tune the IR sensor to your application is to connect it to the +5V and ground pins on your powered Arduino unit and then use a phillips screw driver to adjust the potentiometer so the signal LED responds correctly to an obstacle or light. There is no need to program the Arduino when using the potentiometer to adjust the response threshold.
