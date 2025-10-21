# Edgi-Talk_M33_S_HyperRam Example Project

## Introduction

This example project is based on a **bare-metal architecture** and is primarily used to demonstrate and configure the **Secure M33 HyperRAM** functionality.
Additionally, this project serves as a foundational **template for secondary development or custom projects**, helping users quickly get started and extend functionality as needed.

## Software Description

* The project is developed based on the **Edgi-Talk** platform.

* The example includes the following features:

  * **Secure region configuration**
  * **Basic system startup demonstration**

* The project code is concise and clearly organized, making it easy to understand and port to other applications.

## Usage Instructions

### Build and Flash

1. Open the project and complete the build process.
2. Connect the development board’s **USB interface** to your PC using the **onboard DAP debugger**.
3. Use a programming tool to flash the compiled firmware to the board.

### Running the Demo

* After programming, power on the board to run the example project.
* The system will boot up and transition to the **M33 core**, indicating that the secure configuration has taken effect.

## Notes

* To modify the **graphical configuration** of the project, open the configuration file using the following tool:

  ```
  tools/device-configurator/device-configurator.exe
  libs/TARGET_APP_KIT_PSE84_EVAL_EPC2/config/design.modus
  ```

* After making modifications, save the configuration and regenerate the code.

## Boot Process

The system boot sequence is as follows:

```
+------------------+
|   Secure M33     |
|   (Secure Core)  |
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
