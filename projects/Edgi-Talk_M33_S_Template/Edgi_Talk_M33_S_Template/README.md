# Edgi-Talk_M33_S_Template Example Project

## Introduction

This example project is based on a **Bare Metal** architecture and is primarily designed to demonstrate and configure features of the **Secure M33 core**.
Additionally, this project can serve as a foundation template for further development or project creation, helping users quickly get started and extend functionality.

## Software Description

* Developed on the **Edgi-Talk** platform.
* The example covers:

  * **Secure region configuration**
  * **Basic boot process demonstration**
* The project code structure is simple and clear, making it easy to understand and port.

## Usage

### Build and Flash

1. Open the project and complete the build process.
2. Connect the board’s **USB interface** to your PC using the **onboard DAP debugger**.
3. Use a programming tool to flash the compiled firmware to the development board.

### Running the Demo

* After flashing, power on the board to run the example project.
* The system will boot normally and transition smoothly to the **M33 core**, indicating that the secure configuration is active.

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

⚠️ Please strictly follow the above flashing sequence; otherwise, the system may not run properly.
