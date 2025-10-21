# Edgi-Talk_M55_Blink_LED Example Project

## Introduction

This example project is based on the **Edgi-Talk platform** and demonstrates the **green LED blinking** functionality running on the **RT-Thread real-time operating system**.
Through this project, users can quickly verify the board-level GPIO configuration and LED control logic, providing a fundamental reference for future hardware control and application development.

## Software Description

* The project is developed based on the **Edgi-Talk** platform.

* The example includes the following features:

  * Periodic blinking of the green LED
  * GPIO output control

* The project has a simple structure, making it easy to understand the LED control logic and hardware driver interface.

## Usage Instructions

### Compilation and Download

1. Open the project and complete the build process.
2. Connect the development board to the PC via the **onboard DAP downloader (USB interface)**.
3. Use a programming tool to flash the generated firmware onto the development board.

### Running Results

* After flashing, power on the development board to run the example project.
* The **green LED blinks every 500ms**, indicating that GPIO control and system scheduling are functioning properly.
* Users can modify the blinking period or LED control logic as needed.

## Notes

* To modify the project’s **graphical configuration**, open the configuration file with the following tool:

```
tools/device-configurator/device-configurator.exe
libs/TARGET_APP_KIT_PSE84_EVAL_EPC2/config/design.modus
```

* After making changes, save the configuration and regenerate the code.

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
| (Non-Secure Core)|
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

* If the example project does not run properly, it is recommended to first build and flash the **Edgi-Talk_M33_S_Template** project to ensure that the initialization and core startup process works correctly before running this example.
* To enable the M55 core, open the configuration in the **M33 project**:

  ```
  RT-Thread Settings --> Hardware --> select SOC Multi Core Mode --> Enable CM55 Core
  ```
