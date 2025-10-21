# Edgi-Talk_SDCARD Example Project

## Introduction

This example project is based on the **Edgi-Talk platform** and demonstrates **SD card file operations**, running on the **RT-Thread real-time operating system (M33 core)**.
It allows users to quickly experience SD card mounting, file writing, and reading, and to operate files via the **serial command line**, providing a reference for future storage-related application development.

## Software Description

* Developed on the **Edgi-Talk** platform.

* Example features include:

  * SD card mounting and initialization
  * Writing files using the `echo` command
  * Reading file content using the `cat` command
  * Printing operation results to the serial terminal

* The project structure is clear, making it easy to understand the RT-Thread file system and SD card interface.

## Usage

### Build and Flash

1. Open the project and complete the build.
2. Connect the board’s **USB interface** to the PC using the **onboard DAP debugger**.
3. Use a programming tool to flash the compiled firmware to the development board.
4. Insert an SD card into the corresponding slot on the board.

### Running the Demo

* After flashing, power on the board to run the example.
* The system will automatically mount the SD card and initialize the file system.
* Users can operate files via the **serial terminal** using the following commands:

1. Write to a file `test.txt`:

```sh
echo "Hello RT-Thread SDCARD!" ./test.txt
```

2. Read the file content:

```sh
cat ./test.txt
```

* Example serial output:

```
 \ | /
- RT -     Thread Operating System
 / | \     5.0.2 build Sep  8 2025 11:02:30
 2006 - 2022 Copyright by RT-Thread team
found part[0], begin: 1048576, size: 29.739GB
Hello RT-Thread
This core is cortex-m33
Mount SD card success!

> echo "Hello RT-Thread SDCARD!" ./test.txt
> cat ./test.txt
Hello RT-Thread SDCARD!
```

* The `echo` command can write any string to an SD card file, and the `cat` command can read and display the file content.

## Notes

* Ensure the SD card is properly inserted and formatted with a FAT file system (FAT16/FAT32).
* To modify the project’s **graphical configuration**, open the configuration file using:

```
tools/device-configurator/device-configurator.exe
libs/TARGET_APP_KIT_PSE84_EVAL_EPC2/config/design.modus
```

* After modification, save the configuration and regenerate the code.
* If the SD card cannot be mounted, check the hardware interface and power supply.

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
