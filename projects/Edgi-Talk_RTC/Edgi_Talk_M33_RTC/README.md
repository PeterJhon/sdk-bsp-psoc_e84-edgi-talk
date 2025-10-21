# Edgi-Talk_RTC Example Project

## Introduction

This example project is based on the **Edgi-Talk platform** and demonstrates the **RTC (Real-Time Clock) functionality**, running on the **RT-Thread real-time operating system (M33 core)**.
It allows users to quickly experience RTC time setting, reading, and delayed printing, providing a reference for future time management and scheduled task development.

## Software Description

* Developed on the **Edgi-Talk** platform.

* Example features include:

  * RTC device initialization
  * Date and time setting
  * Delayed reading and printing of current time
  * Exporting RTC operations as an `msh` command `rtc_sample`

* The project structure is clear, making it easy to understand how the RTC driver operates on the **M33 core**.

## Usage

### Build and Flash

1. Open the project and complete the build.
2. Connect the board’s **USB interface** to the PC using the **onboard DAP debugger**.
3. Use a programming tool to flash the compiled firmware to the development board.

### Running the Demo

* After flashing, power on the board to run the example.
* On the serial command line, manually enter:

```
rtc_sample
```

* The system will perform the following operations in sequence:

  1. Initialize the RTC device
  2. Set the date to `2025-07-01`
  3. Set the time to `23:59:50`
  4. Print the current time
  5. Delay for 3 seconds
  6. Print the current time again

* Example output:

```
Tue Jul  1 23:59:50 2025
Tue Jul  1 23:59:53 2025
```

## Notes

* Ensure the RTC device is correctly connected and recognized by the system.
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

⚠️ Please strictly follow the above flashing sequence; otherwise, the system may not operate properly.

---

* If the example project does not run correctly, it is recommended to first build and flash the **Edgi-Talk_M33_S_Template** project to ensure proper initialization and core boot sequence before running this demo.
* To enable the M55 core, open the configuration in:

```
RT-Thread Settings --> Hardware --> select SOC Multi Core Mode --> Enable CM55 Core
```
