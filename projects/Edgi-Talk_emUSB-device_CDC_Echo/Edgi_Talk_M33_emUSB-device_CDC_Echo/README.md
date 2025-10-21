# Edgi-Talk_emUSB-device_CDC_Echo Example Project

## Introduction

This example project is based on the **Edgi-Talk Platform** and demonstrates the **USB CDC (Virtual COM Port) echo function** running on the **RT-Thread Real-Time Operating System (M33 core)**.
Through this project, users can quickly experience the USB CDC communication mechanism and verify data echo functionality, providing a reference for further USB communication and multicore application development.

## Software Description

* The project is developed based on the **Edgi-Talk** platform.
* The example includes the following features:

  * USB CDC device initialization
  * Virtual COM port data echo
* The project structure is clear and helps users understand how the USB device driver operates on the **M33 core**.

## Usage

### Build and Download

1. Open the project and complete the build process.
2. Connect the board’s **USB interface** to your PC using the **onboard DAP debugger**.
3. Use a programming tool to flash the generated firmware to the development board.

### Running the Demo

* After programming, power on the board to run the demo.
* In the serial terminal, manually enter the following command:

```
cdc_sample
```

* The system will output the following startup message:

```
 \ | /
- RT -     Thread Operating System
 / | \     5.0.2 build Sep  8 2025 09:57:30
 2006 - 2022 Copyright by RT-Thread team
Hello RT-Thread
This core is cortex-m33
msh >cdc_sample
****************** PSOC Edge MCU: CDC echo using emUSB-device******************
```

* On your PC, use any serial communication tool to connect to the board’s USB virtual COM port.

1. Open a serial terminal tool on your PC and connect to the board’s virtual COM port (baud rate can be any value).
2. Enter a string and **end it with a newline character `\n`** before sending.
3. The board will echo the received string back to the serial terminal.

```
> hello
hello
> 12345
12345
```

## Notes

* **Echo Trigger Condition**:
  The echo is triggered **only when the last character received is a newline (`\n`)**.
  If the input does not include `\n`, the data will be stored in the buffer and will not be echoed immediately.

* To modify the **graphical configuration** of the project, open the configuration file with the following tool:

```
tools/device-configurator/device-configurator.exe
libs/TARGET_APP_KIT_PSE84_EVAL_EPC2/config/design.modus
```

* After modification, save the configuration and regenerate the code.

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
