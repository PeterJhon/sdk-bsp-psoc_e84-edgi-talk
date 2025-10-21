# Edgi-Talk_LSM6DS3 Example Project

## Introduction

This example is based on the **Edgi-Talk Platform** and runs on the **RT-Thread Real-Time Operating System**, demonstrating how to drive the **LSM6DS3 6-axis sensor (accelerometer + gyroscope + temperature)**.

Through this example, users can learn how to:

* Use RT-Thread’s **I²C device driver framework**
* Initialize and configure LSM6DS3 registers
* Read **three-axis acceleration**, **three-axis angular velocity**, and **temperature data**
* Output sensor data via the serial port

---

## Software Description

* Developed on the **Edgi-Talk** platform.
* Uses **RT-Thread** as the OS kernel.
* Example features include:

  * Detecting and verifying the device ID
  * Sensor reset and restoring default configuration
  * Configuring output data rate and measurement range
  * Polling to read acceleration, angular rate, and temperature data
  * Serial port output of sensor data

## Usage

### Build and Flash

1. Open the project and complete the build process.
2. Connect the board’s **USB interface** to your PC using the **onboard DAP debugger**.
3. Use a programming tool to flash the compiled firmware to the development board.

### Running the Demo

* After programming, power on the board to run the example.

```
Acceleration [mg]:  15.23   -3.12   1000.45
Angular rate [mdps]: 2.50   -1.25    0.75
Temperature [degC]:  26.54
```

* The **blue LED** will blink every 500ms, indicating that the system scheduler is running normally.

---

## Notes

* To modify the project’s **graphical configuration**, open the configuration file using:

  ```
  tools/device-configurator/device-configurator.exe
  libs/TARGET_APP_KIT_PSE84_EVAL_EPC2/config/design.modus
  ```

* After modification, save the configuration and regenerate the code.

## Boot Process

The system boot sequence is as follows:

```
+------------------+
|   Secure M33     |
|  (Secure Core)   |
+------------------+
          |
          v
+------------------+
|       M33        |
| (Non-secure Core)|
+------------------+
          |
          v
+-------------------+
|       M55         |
| (Application Core)|
+-------------------+
```

⚠️ Please strictly follow the above flashing sequence; otherwise, the system may fail to run properly.

---

* If this example does not run correctly, first compile and flash the **Edgi-Talk_M33_S_Template** project to ensure proper initialization and core startup sequence, then run this example.
* To enable the M55 core, open the following configuration in the **M33 project**:

```
RT-Thread Settings --> Hardware --> select SOC Multi Core Mode --> Enable CM55 Core
```
