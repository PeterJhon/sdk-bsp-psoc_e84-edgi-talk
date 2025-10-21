# Edgi-Talk_Key_Irq Example Project

## Introduction

This example project is based on the **Edgi-Talk Platform** and runs on the **RT-Thread Real-Time Operating System**, demonstrating the usage of **Key Interrupts (Key IRQs)**.
Through this project, users can learn how to configure GPIO interrupts in RT-Thread and implement event response logic triggered by button presses, providing a reference for human-machine interaction applications.

## Software Description

* The project is developed based on the **Edgi-Talk** platform.
* **RT-Thread** is used as the operating system kernel.
* The example includes the following features:

  * Configuring button GPIOs as interrupt inputs
  * Triggering an interrupt callback when the button is pressed
  * Blinking the blue LED every 500ms to indicate the system is running normally

## Usage

### Build and Flash

1. Open the project and complete the build process.
2. Connect the board’s **USB interface** to your PC using the **onboard DAP debugger**.
3. Use a programming tool to flash the compiled firmware to the development board.

### Running the Demo

* After programming, power on the board to run the example project.
* The **blue LED** will blink every 500ms, indicating that the system scheduler is functioning properly.
* When the user presses the button, the interrupt callback is triggered, and the following message is printed in the serial terminal:

```
The button is pressed
```

## Notes

* To modify the **graphical configuration** of the project, open the configuration file using the following tool:

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
