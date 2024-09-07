 	Validation and Prototype

This section details the development of a prototype pipeline designed for controlling an autonomous vehicle. The pipeline utilizes a combination of readily available sensors and custom-designed sensors created by the research team. A dedicated low-level control system (LCS), depicted in Figure 5.7.1, manages communication and control between the sensors and any involved motors using ROSserial. The primary objective of this section is to present the design and implementation of this prototype pipeline, serving as a foundation for further validation and development in subsequent sections.

**Figure 5.7.1**

For the used sensors, we used an IMU integrated in the Zed 2i camera and a modified servo motor used as a steering angle Encoder mounted on the steering rod.

The modification applied to the SG90 Servo was an extra connection welded to the output signal of the potentiometer used in the motor to originally control its angle, after that, this signal is mapped to the angle limits of the motor. thus creating an angle encoder from a servo motor (SG90)  figure 5.7.2 shows the servo circuit  
Now discussing the intuition regarding the motor control for longitudinal control  
   
 Torque vectoring:  
	Most modern cars, especially those with just one electric motor, rely on a key part called a differential to handle how the car behaves when turning. This differential becomes especially important when the car goes around a curve. Since the car is turning, the inner wheel doesn't need to travel as far as the outer wheel. The differential allows the inner wheel to spin slower than the outer wheel, which helps the car turn smoothly and prevents the tires from scrubbing.  
In our case, we use two in-hub motors and no differential to control the wheel speed and thus we use torque vectoring, where we can control each wheel independently and simultaneously keep the resultant (required )  car velocity required by the higher control in the subsystem.

First, when receiving the target velocity to be achieved and the current steering angle   
We can calculate the instant radius of the vehicle ‘r’ which is pivotal in our algorithm  
As shown in figure 5.7.3 and figure 5.7.4 shows the pseudocode.

Fig 5.7.3

Fig 5 .7.3

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

Then we compute the direction of steering either positive or negative(+ve is right while \-ve is left on a local frame for the vehicle) by knowing which part is left and right by the sign of the angle we can compute the outer and inner wheel and calculate the target velocity for each wheel   
With the assumption that both have the same angular velocity as the geometric center of the car.  
the   symbolizes the track width.

###                                         centre\=inner=outer

### Inner velocity\=(r-(1/2\*()))r

### outer velocity\=(r+(1/2\*()))r

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 		Due to the inconstant acceleration of the original car design (presence of jerk) and the unmatched speed between the car which is 32 m/s and the max velocity for the prototype of 1.4524 m/s.We can derive the following mapping function. 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### After calculating the needed velocity for the prototype to match the vehicle behavior, we map the motor driver's output.

			  
The below figure shows the overall algorithm.

### 

### 

### 

### 

### 

### 

Steering control :  
	The steering control system was composed of two part the the actuation part mounted on the end of the steering rod (nearest point for the steering geometry ) and the steering encoder (customised servo) mounted on the top of the rod to ensure a closed loop control system as shown in  figure: 5.7.x where the green nodes represent the low control system while the blue nodes are the sensors of the system other than the camera.

This section discusses the algorithm behind the steering control system and the conversion from an open loop system(dc motor) to  a servo motor  
First we get the required angle from the control node we translate them to match the origen of the encoder ,so the reference angel matches the required angle

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### Then according to the error we produce a signal to actuate the motor 

1 if the target is greater than the actual,-1 if the target is actual angle greater than the target and 0 if the angel is achieved or in a margin of error set in the algorithm

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 

### 
