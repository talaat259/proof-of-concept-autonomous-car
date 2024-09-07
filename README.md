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
![Alt Text](https://github.com/talaat259/proof-of-concept-autonomous-car/blob/main/images/image16.png)
### 

### 

### 

### 

### 
After determining the required velocities to align the prototype with the desired vehicle behavior, we proceed to map these velocities to the motor driver's output. This mapping ensures that the calculated velocities are appropriately translated into commands that drive the motors, thereby achieving the desired performance and handling characteristics for the prototype.




![Alt Text](https://github.com/talaat259/proof-of-concept-autonomous-car/blob/main/images/image12.png)
### 

Steering control :  
	The steering control system consists of two main components: the actuation mechanism and the steering encoder. The actuation mechanism is mounted at the end of the steering rod, providing precise control at the point closest to the steering geometry. The steering encoder, a customized servo, is positioned at the top of the steering rod to enable a closed-loop control system.

Figure 5.7.x illustrates the system, with green nodes representing the low-level control components and blue nodes denoting the sensors, excluding the camera. This configuration ensures accurate feedback and control, integrating both actuation and measurement to optimize steering performance.



![Alt Text](https://github.com/talaat259/proof-of-concept-autonomous-car/blob/main/images/image17.png)


This section explores the algorithm underpinning the steering control system, focusing on the transition from an open-loop system using a DC motor to a closed-loop system employing a servo motor.


Initially, we obtain the desired steering angle from the control node. This angle is then translated to align with the origin of the encoder, ensuring that the reference angle accurately reflects the required steering angle. This process facilitates precise alignment between the control commands and the actual steering position, enabling effective closed-loop control with the servo motor.


### 


![Alt Text]( https://github.com/talaat259/proof-of-concept-autonomous-car/blob/main/images/image10.png)



### 

###

### 

### 

### 

### 

### 

### 

### 

Based on the calculated error between the target angle and the actual angle, we generate a control signal to actuate the motor:

Signal +1: If the target angle is greater than the actual angle, indicating that the steering needs to be adjusted to a larger angle.
Signal -1: If the actual angle exceeds the target angle, meaning the steering needs to be adjusted to a smaller angle.
Signal 0: If the actual angle matches the target angle within a predefined margin of error, indicating that the steering is correctly positioned.
This control signal drives the motor to correct any discrepancies and achieve the desired steering angle with precision.






![Alt Text](https://github.com/talaat259/proof-of-concept-autonomous-car/blob/main/images/image8.png)







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
