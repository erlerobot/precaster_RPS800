## precaster_rps800 (indigo) - 0.1.1-0

The packages in the `precaster_rps800` repository were released into the `indigo` distro by running `/usr/local/bin/bloom-release --rosdistro indigo --track indigo precaster_rps800` on `Thu, 22 Dec 2016 15:06:37 -0000`

The `precaster_rangefinder_rps800` package was released.

Version of package(s) in repository `precaster_rps800`:

- upstream repository: https://github.com/erlerobot/precaster_RPS800
- release repository: unknown
- rosdistro version: `null`
- old version: `null`
- new version: `0.1.1-0`

Versions of tools used:

- bloom version: `0.5.23`
- catkin_pkg version: `0.2.10`
- rosdep version: `0.11.5`
- rosdistro version: `0.5.0`
- vcstools version: `0.1.39`


- [Precaster Rangefinder RPS800](#precaster-rangefinder-rps800)
 - [Features](#features)
 - [Applications](#applications)
 - [Technical data](#technical-data)
- [Configuring precaster rangefinder rps800](#configuring-precaster-rangefinder-rps800)
- [Compiling the code from sources](#compiling-the-code-from-sources)
- [Launching manually](#launching-manually)
 - [Starting a roscore](#starting-a-roscore)
 - [Setting Parameters](#setting-parameters)
 - [Running the precaster rangefinder rps800 node](#running-the-precaster-rangefinder-rps800-node)
- [Launch file](#launch-file)

# Precaster rangefinder RPS800

[RPS800](https://www.precaster.com.tw/predustrial/rps800/) is designed as a compact and reliable laser distance measuring sensor. The pulse technology gives the good accuracy and response time in distance measuring and a stable output under the strong ambient light.

![](https://www.precaster.com.tw/predustrial/wp-content/uploads/2016/08/RPS800_img4.png)

### Features

 - Highly Customizable module fit for most duties.
 - Adjustable High Speed measuring up to 2000HZ.
 - Digital output with UART.
 - TOF Non-Contact Measuring Low Consumption Sensor.

### Applications

 - Robot Eyes Distance Measuring
 - Positioning and monitor of objects
 - Security Applications Movement Detections
 - Level and elevator Measuring
 - Drone Dodge Actions Control

### Technical data

| Model No. | CA113 Spec. | CA113 Tolerance|
| --- | --- | --- |
| Maximun measuring range| 6 meters | 6.5m |
| Minimum Measuring Range|  0.1 meters | 0.05m|
|  Repeatability Accuracy from 0.5m to 1m |  ±20 mm|  Standard Deviation 2σ, Kodak White Board|
| Repeatability Accuracy from 1m to 5m | ±40 mm|
| Repeatability Accuracy over 6m	 | ±1% of measured distance | |
| Measurement Time | 2000 Hz| |
| Unit		| Millimeter| |
| Power Source		| 6V|  ±0.2V|
| Power Consumption		| 0.25W | |
| Laser Radiation		| Class 1| |
| Laser Wavelength		| 808nm| |
| Operating Temperature Range		| -5°C~40°C| |
| Storage Temperature Range		| -20°C~60°C| |
| Serial Port Type		| UART| | |
| Dimensions		| 61 x 21 x 18 mm| |
| Weight		| 17.6g| ±5g | |

## Configuring precaster rangefinder rps800

Make sure that your node is able to access the data from the sensor

List the permissions of your serial port, for example in a Rpi2:

```
ls -l /dev/ttyAMA0
```

You will see something like to:

```
crw-rw-XX- 1 root dialout 204, 64 Dec 16 10:17 /dev/ttyAMA0
```

If **XX** is `rw`: the rangefinder is configured properly.

If **XX** is `--`: the rangefinder is not configured properly and you need to:

```
sudo chmod a+rw /dev/ttyAMA0
```

## Compiling the code from sources

Clone this repository in a ROS workspace or [create a new one](http://wiki.ros.org/catkin/Tutorials/create_a_workspace)

```
cd ~/ros_catkin_ws/src
git clone https://github.com/erlerobot/precaster_rangefinder
```
Now compile the code:

```
cd ~/ros_catkin_ws/
catkin_make_isolated --install --pkg precaster_rangefinder_rps800
```

## Launching manually
### Starting a roscore

A ros core must be running:

```
roscore
```

### Setting Parameters

We need to make sure that we have the correct configurations loaded on the parameter server.

If your sensor is not at the default `/dev/ttyAMA` you have to indicate where it is below:

```
rosparam set /precaster_rangefinder_rps800/port /dev/ttyAMA0
```
The same idea with the baudrate:
```
rosparam set /precaster_rangefinder_rps800/baudrate 230400
```

### Running the precaster rangefinder rps800 node

```
rosrun precaster_rangefinder_rps800 rps800
```

## Launch file

```
roslaunch precaster_rangefinder_rps800 rps800.launch
```

If you need to modify some parameters just do it in the launch file.
