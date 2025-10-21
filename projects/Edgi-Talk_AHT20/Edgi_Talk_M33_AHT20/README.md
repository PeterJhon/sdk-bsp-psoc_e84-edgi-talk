# Edgi-Talk_M33_AHT20 Example Project

## Introduction

This example project is based on the **Edgi-Talk platform** and demonstrates how to drive and use the **AHT20 temperature and humidity sensor**.
Through this project, users can quickly experience AHT20 data acquisition and processing, and view the sampled results via the serial terminal on the development board.

## Software Description

* The project is developed based on the **Edgi-Talk** platform.

* The example includes the following features:

  * AHT20 initialization and communication via I²C
  * Temperature and humidity data reading and parsing
  * Serial printing of sampled data

* The project structure is clear, making it easy for users to understand I²C driver implementation and sensor interfacing.

## Usage Instructions

### Compilation and Download

1. Open the project and complete the build process.
2. Connect the development board to the PC via the **onboard DAP downloader (USB interface)**.
3. Use a programming tool to flash the generated firmware onto the development board.

### Running Results

* After flashing, power on the development board to run the example project.
* The system will initialize the AHT20 and start sampling temperature and humidity data.
* The sampling results will be printed through the serial terminal, as shown below:

```
 \ | /
- RT -     Thread Operating System
 / | \     5.0.2 build Sep  5 2025 14:13:02
 2006 - 2022 Copyright by RT-Thread team
Hello RT-Thread
This core is cortex-m33
msh >[I/aht10] AHT10 has been initialized!
[D/aht10] Humidity   : 44.4 %
[D/aht10] Temperature: 29.7
[D/aht10] Humidity   : 44.4 %
[D/aht10] Temperature: 29.7
```

## Notes

* To modify the project’s **graphical configuration**, open the configuration file using the following tool:

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

* If the example project does not run properly, it is recommended to first build and flash the **Edgi-Talk_M33_S_Template** project to ensure the initialization and core startup process works correctly before running this example.
* To enable the M55 core, open the configuration in the **M33 project**:

  ```
  RT-Thread Settings --> Hardware --> select SOC Multi Core Mode --> Enable CM55 Core
  ```
