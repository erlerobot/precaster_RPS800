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
