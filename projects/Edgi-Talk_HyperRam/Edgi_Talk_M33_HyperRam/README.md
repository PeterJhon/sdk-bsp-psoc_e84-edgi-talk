# Edgi-Talk_M33_HyperRam Example Project

## Introduction

This example project is based on the **Edgi-Talk Platform** and demonstrates the functionality of **HyperRAM**, running on the **RT-Thread Real-Time Operating System**.
Through this project, users can quickly verify HyperRAM operation, providing a solid foundation for further hardware control and application development.

## Software Description

* The project is developed based on the **Edgi-Talk** platform.

* The example includes the following features:

  * HyperRAM initialization and operation test

* The project structure is simple and easy to understand, helping users learn the HyperRAM control logic and hardware driver interface.

## Usage

### Build and Download

1. Open the project and complete the build process.
2. Connect the board’s **USB interface** to your PC using the **onboard DAP debugger**.
3. Use a programming tool to flash the generated firmware to the development board.

### Running the Demo

* After programming, power on the board to automatically run the demo.
* The program will initialize and test HyperRAM, verifying correct operation through log outputs.

## Notes

* To modify the **graphical configuration** of the project, open the configuration file with the following tool:

```
tools/device-configurator/device-configurator.exe
libs/TARGET_APP_KIT_PSE84_EVAL_EPC2/config/design.modus
```

* After making changes, save the configuration and regenerate the code.

## Startup Sequence

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

* If this example project does not run correctly, compile and flash the **Edgi-Talk_M33_S_Template** project first to ensure proper initialization and core startup sequence, then re-run this example.
* To enable the M55 core, open the following configuration in the **M33 project**:

```
RT-Thread Settings --> Hardware --> select SOC Multi Core Mode --> Enable CM55 Core
```
