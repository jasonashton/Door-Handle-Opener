# Door-Handle-Opener

Opens a door handle with a Nema 17.  
**Problem:** In our residence hall, we can open the main doors with our ID cards but have to use a key to open the individual rooms.  
**Solution:** We've built a spool-and-motor system to open the door handle without altering the existing door.

##Parts List
1. Custom Built Microcontroller (heavily based on Arduino Uno) <em>see wiki</em>
2. A4988 Motor Driver (allows us to drive motors with independent power supply)
3. Nema 17 Stepper Motor
4. 3D Printed Parts <em>see models</em>

##Configuring the Motor Driver
The Motor Driver we chose to use is the Polulu A4988  
The Motor we chose is a Nema 17

To configure the current limiting on the motor driver, we use the formula
Current Limit = VREF x 2.5

Measure the voltage on the potentiometer (VREF). In Full Step mode, the driver will
only pull 70% of the current.

Current Limit / 2.5 = VREF

To get a full-step coil current of 1.4 Amps, the limit should be 1.4A/0.7 or 2
Amps. To find VREF, 2A/2.5 = .8 Volts. 

However, that might run a bit hot. Anything over 1 Amp requires external
cooling. To achieve a 1 Amp load,
1A/0.7 = 10/7A & 10/7A/2.5 = .572 Volts on VREF
