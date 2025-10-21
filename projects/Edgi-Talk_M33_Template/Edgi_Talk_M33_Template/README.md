# Edgi-Talk_M33_Template Example Project

## Introduction

This example project is based on the **RT-Thread real-time operating system** and runs on the **M33 core**.
It allows users to quickly experience the performance of RT-Thread on the M33 platform.
After successfully flashing the firmware and powering on the board, the **blue LED** on the development board will blink periodically, indicating that the system is running correctly.
Additionally, this project can serve as a foundation template for further development or project creation, helping users quickly get started and extend functionality.

## Software Description

* Developed on the **Edgi-Talk** platform.
* Uses **RT-Thread** as the operating system kernel.
* Example features include:

  * System initialization
  * LED indicator task (blinking)
* The project structure is clear, making it suitable as a starting point for learning RT-Thread or developing applications.

## Usage

### Build and Flash

1. Open the project and complete the build process.
2. Connect the board’s **USB interface** to your PC using the **onboard DAP debugger**.
3. Use a programming tool to flash the compiled firmware to the development board.

   * During flashing, the project will automatically invoke the following tool to merge the signed firmware:

     ```
     tools/edgeprotecttools/bin/edgeprotecttools.exe
     ```
   * By default, `proj_cm33_s_signed.hex` in the directory will be merged and flashed to the target device.

### Running the Demo

* After flashing, power on the board to run the example project.
* The **blue LED** will blink periodically, indicating that the RT-Thread system scheduler has started successfully.

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

⚠️ Please strictly follow the above flashing sequence; otherwise, the system may not operate properly.

* To enable the M55 core, open the configuration in:
  `RT-Thread Settings --> Hardware --> select SOC Multi Core Mode --> Enable CM55 Core`
