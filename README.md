# Modul242-SoltMachine

Welcome to the Slot Machine GitHub repository! This project is a digital implementation of a classic slot machine game, designed to be run on three M5Stack Core 2 devices. With this project, you can experience the excitement of seeing the reels spin to potentially win big!

## Requirements
To run this Slot Machine project, you will need the following:

- Three M5Stack Core 2 devices.
- Internet connection to download the necessary dependencies.
- Gesture recognition sensor

## Installation
To get started with the Slot Machine project, follow these steps:

1. Clone this repository to your local machine using the following command:
```
git clone https://github.com/your-username/slot-machine.git
```
3. Add a config.cpp to the base folder of the project with the following content:
```
#ifndef CONFIG_H_
#define CONFIG_H_

// mqtt configuration (username, password not used)
const char *mqtt_server = "cloud.tbz.ch";
const char *clientId = "123456789ABUOZ";
const char *username = "";
const char *password = "";

// WiFi configuration
const char *ssid = "LERNKUBE";
const char *passphrase = "l3rnk4b3";

#endif // BASE_H
```
3. Connect your M5Stack Core 2 device to your computer
4. Ctrl + Shift + P => Upload and Monitor

## Usage
To play the Slot Machine game, follow these steps:

1. Ensure that all three M5Stack Core 2 devices are turned on and connected.
2. Hover over the gesture sensor to spin.
3. Watch as the reels spin and come to a stop. If you match certain symbols, you may win a prize!

Have fun and enjoy the Slot Machine experience!
