# Car Driving With Model Predictive Control (MPC)
This is project 5 of Term 2 of Udacity Self-Driving Car Nanodegree. Program controls steering wheel, gas and brake to drive a car on the road. It uses model predictive control (MPC). This means that you have model of controlled object and you use this model to predict and optimize its future states to make your controlled object behave in desired way.

## Kinematic Model
Kinematic models are simplifications of dynamic models that ignore tire forces, gravity, and mass.

The states of car is consider with:

* position x, 
* position y, 
* the direction car torwarding psi
* the velocity of the car v. 

The actuators to be controlled are:

* the steering angle - delta
* the throttle and break (when positive hit the throttle, negative hit the brake)- a


The Car follow the simple Kinematic model:

* x[t+1] = x[t] + v[t] * cos(psi[t]) * dt
* y[t+1] = y[t] + v[t] * sin(psi[t]) * dt
* phi[t+]= psi[t] + v[t] / Lf * delta * dt
* v[t+1] = v[t] + a[t] * dt

Lf is distance between the front of the vehicle and its center of gravity

MPC optimize current and future actuators to keep states in desired values using following loss function:
```
Loss = cte^2 + epsi^2 + (v - v_target)^2 + delta^2 + a^2 + 1000 * (delta - delta_prev)^2 + 100 * (a - a_prev)^2
       ```

* cte - distance between car and the middle of the track
* epsi - difference between the direction of the car to the desired direction
* (v - v_target)^2 - difference between current speed to desired speed
* delta^2 and a^2 - to make the actuation not too big
* 1000* (delta - delta_prev)^2 and 100 * (a - a_prev)^2 - to make the actuation as smooth as possible


## Timestep Length and Elapsed Duration (N & dt)

At beginning I start N, and dt with 25 and 0.05 by copy from the quiz. Then I found the second sharp turn witch followed by another sharp turn will disturb the polyfit, so I reduce the N to 12 and keep the same dt as 0.05. Then it successfully control the car finish the full lap.

## Preprocessing
The coordinate from the simulator is in global coordinate, so the first step is convert it into car coordinate, see ```src/main.cpp``` from line 107 to line 112. Then can fit these coordinates with cubic polynomial (yellow line on the video).

## Model Predictive Control with Latency
To address the 100ms latency that when commander issue the actuators to the car  really get the effect of these actuators, I freeze actuators values during the delay to actuators values of previous step. And issue the actuators which is 100ms later. 
 


