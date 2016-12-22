# precaster_rangefinder_rps800

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

## Compiling the code

Clone this repository in a ROS workspace

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
