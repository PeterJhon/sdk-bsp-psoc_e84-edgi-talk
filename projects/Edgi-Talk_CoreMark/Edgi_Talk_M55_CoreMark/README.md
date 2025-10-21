# Edgi-Talk_M55_CoreMark Example Project

## Introduction

This example project is based on the **Edgi-Talk Platform** and demonstrates the **CoreMark benchmark test running on the M55 core** under the **RT-Thread real-time operating system**.
Through this project, users can quickly evaluate the performance of the M55 core and understand how multi-core coprocessors operate under an RTOS environment.

## Software Description

* The project is developed on the **Edgi-Talk** platform.
* The example includes the following features:

  * CoreMark benchmark running on the M55 core
  * Printing benchmark results via UART
* The project structure is simple and easy to understand, helping users learn the M55 core startup process and performance testing method.

## Usage

### Build and Download

1. Open the project and complete the build process.
2. Connect the board’s **USB interface** to your PC using the **onboard DAP debugger**.
3. Use a programming tool to flash the generated firmware to the development board.

### Running the Demo

* After programming, power on the board to start RT-Thread.
* If the system starts successfully, the following message appears on the serial terminal:

```
 \ | /
- RT -     Thread Operating System
 / | \     5.0.2 build Sep  5 2025 15:19:27
 2006 - 2022 Copyright by RT-Thread team
msh >Hello RT-Thread
It's cortex-m55
```

* Enter the following command in the serial console:

```
core_mark
```

* The system will start the CoreMark test and print the benchmark results, for example:

```
Benchmark started, please make sure it runs for at least 10s.

2K performance run parameters for coremark.
CoreMark Size    : 666
Total ticks      : 30218
Total time (secs): 30
Iterations/Sec   : 1200
Iterations       : 36000
Compiler version : GCC10.2.1 20201103 (release)
Compiler flags   :
Memory location  : STACK
seedcrc          : 0xe9f5
[0]crclist       : 0xe714
[0]crcmatrix     : 0x1fd7
[0]crcstate      : 0x8e3a
[0]crcfinal      : 0xcc42
Correct operation validated. See README.md for run and reporting rules.
CoreMark 1.0 : 1200 / GCC10.2.1 20201103 (release)  / STACK
```

## Notes

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

⚠️ Please strictly follow the above sequence when flashing firmware, otherwise the system may fail to run properly.

---

* If this example does not run correctly, compile and flash the **Edgi-Talk_M33_S_Template** project first to ensure proper initialization and core startup sequence, then re-run this example.
* To enable the M55 core, open the following configuration in the **M33 project**:

```
RT-Thread Settings --> Hardware --> select SOC Multi Core Mode --> Enable CM55 Core
```
