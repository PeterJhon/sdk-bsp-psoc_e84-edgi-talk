# Xiaozhi Example Project

## Introduction

This example project is based on the **Edgi-Talk platform** and demonstrates the **basic functionality of the Xiaozhi voice interaction device**, running on the **RT-Thread real-time operating system**.
It allows users to quickly verify device features such as **WiFi connectivity**, **button wake-up**, and **voice interaction**, providing a reference for future application development.

## Software Description

* Developed on the **Edgi-Talk** platform.
* Example features include:

  * WiFi connection and status display
  * Button wake-up and voice interaction
  * Device state management (standby, listening, sleep, etc.)

## Usage

### Build and Flash

1. Open the project and complete the build.
2. Connect the board’s **USB interface** to the PC using the **onboard DAP debugger**.
3. Use a programming tool to flash the compiled firmware to the device.

### Running the Demo

* After flashing, power on the device to run the example.

* The screen will display the current status, including:

  * **Connecting**: connecting to WiFi
  * **On standby**: standby mode
  * **Listening**: listening mode, ready for voice interaction
  * **Sleeping**: sleep mode

* Pressing the top button will switch the device to **Listening** mode for voice interaction.

## Notes

* The first time, you need to bind the device via the [Xiaozhi official website](https://xiaozhi.me/).
* Ensure the WiFi SSID and password are correct, and use the **2.4 GHz band**.
* The device should be used in an environment with internet access.
* To modify the project’s **graphical configuration**, use the following tools:

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
| (Secure Core)    |
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

⚠️ Please strictly follow the above flashing sequence; otherwise, the device may not operate properly.

---

* If the example project does not run correctly, it is recommended to first build and flash the **Edgi-Talk_M33_S_Template** project to ensure proper initialization and core boot sequence before running this demo.
* To enable the M55 core, open the configuration in the **M33 project**:

```
RT-Thread Settings --> Hardware --> select SOC Multi Core Mode --> Enable CM55 Core
```
