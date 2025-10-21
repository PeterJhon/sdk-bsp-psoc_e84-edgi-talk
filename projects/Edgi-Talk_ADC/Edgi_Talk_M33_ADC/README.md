# Edgi-Talk_ADC Example Project

## Introduction

This example project is based on the **Edgi-Talk platform** and runs on the **RT-Thread real-time operating system**.
It demonstrates how to use the **ADC (Analog-to-Digital Converter)**.
Through this project, users can quickly experience ADC data acquisition and processing functions, providing a reference for developing analog signal acquisition applications.
During operation, the blue indicator LED blinks periodically, indicating that the system has started and is running normally.

## Software Description

* The project is developed based on the **Edgi-Talk** platform.

* It uses **RT-Thread** as the operating system kernel.

* Example features:

  * ADC initialization and sampling
  * LED indicator blinking
  * ADC sampling results printed through the serial port

* The project structure is clear, making it easy for users to understand the ADC driver and RT-Thread thread mechanism.

## Usage Instructions

### Compilation and Download

1. Open the project and complete the build process.
2. Connect the development board to the PC using the **onboard DAP downloader** via USB.
3. Use the programming tool to flash the generated firmware onto the development board.

### Running Results

* After flashing, power on the development board to run the example project.
* The **blue indicator LED** blinks every 500ms, indicating normal system scheduling.
* The ADC sampling results of the battery voltage will be printed through the serial port, as shown below:

  ```
  Value is: 3.123 V
  Value is: 3.125 V
  ...
  ```

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
