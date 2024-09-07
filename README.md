 	Validation and Prototype

This section outlines the creation of a prototype pipeline for controlling an autonomous vehicle, leveraging a combination of commercially available sensors alongside custom-designed sensors. A specialized low-level control system (LCS), as illustrated in Figure 1.3, is employed to manage communication and control between the sensors and actuators, utilizing ROSserial for seamless integration. The primary aim of this section is to present the design and implementation of this prototype pipeline, which establishes the groundwork for subsequent validation, refinement, and development in later stages of the project.
**Figure 1.3**
![Alt Text](https://github.com/talaat259/proof-of-concept-autonomous-car/blob/main/images/image11.png)


For the sensor setup, the integrated IMU within the Zed 2i camera and a modified servo motor, repurposed as a steering angle encoder mounted on the steering rod, were utilized.

The modification applied to the SG90 servo motor involved the addition of an external connection soldered to the potentiometer's output signal, which is typically used to control the motor's angle. This signal is then calibrated to correspond to the motor's angular limits, effectively transforming the SG90 servo into a functional steering angle encoder. Figure 1.2 illustrates the  servo circuit.
**Figure 1.2**
![Alt Text](https://github.com/talaat259/proof-of-concept-autonomous-car/blob/main/images/image9.jpg)

Now discussing the intuition regarding the motor control for longitudinal control  
   
 Torque vectoring:  
	In modern vehicles, particularly those with a single electric motor, a crucial component known as the differential plays a key role in ensuring smooth handling during turns. The differential becomes especially critical when navigating curves, as the inner wheel covers a shorter distance than the outer wheel. It enables the inner wheel to rotate at a slower speed than the outer wheel, allowing for smooth cornering and preventing tire wear due to scrubbing.

In our system, we employ two in-hub motors instead of a traditional differential, utilizing a torque vectoring approach. This allows for independent control of each wheel's speed while maintaining the overall vehicle velocity as determined by the higher-level control subsystem. This method ensures precise handling and optimal performance without the need for a mechanical differential.

Upon receiving the target velocity and current steering angle, the algorithm calculates the instantaneous turning radius, denoted as 'r,' which is a critical factor in the vehicle's control logic. This calculation is essential for determining how the vehicle will maneuver, ensuring accurate and smooth operation.

Figure 1.3 illustrates the geometric relationship used to determine the radius, while Figure 1.4 presents the pseudocode that outlines the process for implementing this calculation within the control system.

Fig 1.3
![Alt Text](https://github.com/talaat259/proof-of-concept-autonomous-car/blob/main/images/image13.jpg)


Fig 1.4
![Alt Text](https://github.com/talaat259/proof-of-concept-autonomous-car/blob/main/images/image14.png)

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

Subsequently, the steering direction is computed as either positive (right) or negative (left) based on the sign of the steering angle in the vehicle's local frame. By determining the relative position of the wheels—left or right—using the sign of the angle, we can then calculate the target velocity for each wheel.

Assuming that both wheels share the same angular velocity as the geometric center of the vehicle, we compute the velocities for the inner and outer wheels. The track width, denoted by 
𝑤
w, plays a crucial role in this calculation, as it represents the distance between the left and right wheels.
![Alt Text](https://github.com/talaat259/proof-of-concept-autonomous-car/blob/main/images/omega_calc.png)


### 

### 

### 

### 

### 

### 

### 

### 

### 
![Alt Text](https://github.com/talaat259/proof-of-concept-autonomous-car/blob/main/images/image7.png)

### 

### 		Due to the inconstant acceleration of the original car design (presence of jerk) and the unmatched speed between the car which is 32 m/s and the max velocity for the prototype of 1.4524 m/s.We can derive the following mapping function. 

![Alt Text](https://github.com/talaat259/proof-of-concept-autonomous-car/blob/main/images/image15.png)

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
![Alt Text](https://github.com/talaat259/proof-of-concept-autonomous-car/blob/main/images/image15.png)
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
