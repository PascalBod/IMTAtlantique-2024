# Install ESP-IDF 4.4.6

Download ESP-IDF v4.4.6. This can be done directly from the command line:
```shell
$ cd ~/DevTools
$ git clone -b v4.4.6 --recursive https://github.com/espressif/esp-idf.git esp-idf-v4.4.6
$ cd esp-idf-v4.4.6
$ ./install.sh esp32
```

# Install corresponding version of ESP-WHO

Clone the *idfv4.4* branch of the ESP-WHO repository:
```shell
$ cd ~/DevTools
$ git clone -b idfv4.4 --recursive https://github.com/espressif/esp-who.git
$ cd esp-who
```

# Build an ESP-WHO example

Set up ESP-IDF environment:
```shell
$ . ~/DevTools/esp-idf-v4.4.6/export.sh
```

Go into the directory of the example to run:
```shell
$ cd ~/DevTools/esp-who/examples/human_face_detection/web
```

Configure the project:
```shell
$ idf.py menuconfig
```

Set the following options:
* *Component Config > ESP-WHO Configuration > Wi-Fi Configuration*:
  * *WiFi AP Password*: set a password with a minimum of 8 characters
  * *WiFi AP IP Address*: keep it to the default value, 192.168.4.1

Build the project:
```shell
$ idf.py build
```

If the following error message is displayed:
```
collect2: error: ld returned 1 exit status
ninja: build stopped: subcommand failed.
HINT: The applications static IRAM usage is larger than the available IRAM size.
```
set the following additional options:
* *Component Config > Wi-Fi*:
  * Uncheck *WiFi IRAM speed optimization*
  * Uncheck *Wifi RX IRAM speed optimization*

Flash the resulting binary file:
```shell
$ idfp.py -p /dev/ttyUSB0 flash
```
Adapt the device name, if necessary.

Display the application log messages:
```shell
$ idf.py monitor
```

# Run the example

Connect a smartphone or a PC to the Wi-FI access point created by the application, and named *Human Face Detection*. Then, from the connected device, visit the following URL with a web browser: `http://192.168.4.1`.

Click the *Start Stream* button, at the bottom of the web page.

The video stream appears on the web page.

Note: to make the ESP-EYE connect to a Wi-Fi access point and then connect your smartphone or your PC to the same Wi-Fi access point, thus keeping your access to the LAN, configure the following options:
* *Component Config > ESP-WHO Configuration > Wi-Fi Configuration*:
  * *WiFi STA SSID*
  * *WiFi STA Password*

Note: of course, a DHCP server must be active, on the LAN.

Look at the log messages written by the application. A line provides the IP address assigned to the ESP-EYE:
```
I (1841) camera wifi: got ip:192.168.1.15
```

Visit the associated URL, e.g. `http://192.168.1.15`, from a web browser, using a PC connected to the LAN.

Note: the ESP-EYE access point stays active. If no password is configured for it, it is open.

# Download and build the skeletonApp-camera

## Overview

The skeletonApp-camera application allows to get camera frames on a periodic basis, and can be modified in order to accept code that can process each frame.

## Download

Get the latest version of the IMTAtlantique-2024 repository:
```shell
$ cd ~/Dev/IMTAtlantique-2024
$ git pull origin main
```

The skeletonApp-camera project is in `sampleApplications/skeletonApp-camera` directory.

## Configure the source code

Configure the source code of the application as explained in its `README.md` file:
* In the top-level `CMakeLists.txt` file, adapt the definition of `EXTRA_COMPONENT_DIRS`
* In the project directory, run the `idf.py menuconfig` command, to set the type of the board and enable the SPI RAM

## Build, flash, run

Then, build, flash, run and monitor the application:
* `idf.py build`
* `idf.py flash`
* `idf.py monitor`

