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

Clone this repository in a ROS 2.0 workspace

```
cd ~/ros2_ws/src
git clone https://github.com/erlerobot/precaster_rangefinder -b ros2
```
Now compile the code:
```
cd ~/ros2_ws/
source ~/ros2_ws/install/setup.bash
ament build --only-package precaster_rps800
```

## Execute

In other terminal source your ROS 2.0 workspace

```
source ~/ros2_ws/install/setup.bash
```

Now launch your ROS 2.0 driver:

```
precaster_rps800 /dev/ttyAMA0 230400
```

### Listener

If you want to visualize the measurement of the sensor, launch the listener node:

```
precaster_rps800_listener
```
