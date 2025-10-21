# Edgi-Talk_M55_LVGL Example Project

## Introduction

This example project is based on the **Edgi-Talk Platform** and demonstrates the **LVGL Graphics Library Stress Example**, running on the **RT-Thread Real-Time Operating System**.

Through this example, users can quickly verify the board-level **LCD display driver** and the **LVGL graphics framework** porting, providing a reference for subsequent GUI application development.

## Software Description

* Developed on the **Edgi-Talk** platform and runs on the **M55 application core**.
* Example features include:

  * Initialization of the LVGL graphics library
  * Launching the **lv_demo_stress** example
  * Performing performance testing and rendering demonstrations on the LCD
* The project structure is concise, making it easy to understand the **display driver interface** and **LVGL porting process**.

## Usage

### Build and Flash

1. Open the project and complete the build process.
2. Connect the board’s **USB interface** to your PC using the **onboard DAP debugger**.
3. Use a programming tool to flash the compiled firmware to the development board.

### Running the Demo

* After flashing, power on the board to run the example.
* The system will automatically start **lv_demo_stress**, displaying LVGL performance test graphics on the LCD.
* Users can modify the example entry function in `applications/main.c` to switch to other LVGL demos, such as `lv_demo_widgets` or `lv_demo_music`.

## Notes

* To modify the project’s **graphical configuration**, open the configuration file using:

```
tools/device-configurator/device-configurator.exe
libs/TARGET_APP_KIT_PSE84_EVAL_EPC2/config/design.modus
```

* After modification, save the configuration and regenerate the code.
* If the display does not output correctly, check:

  * Whether the LCD hardware connection and power supply are normal
  * Whether the configurations in `lv_port_disp.c` and `lv_port_indev.c` match the actual hardware

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

⚠️ Please strictly follow the above flashing sequence; otherwise, the system may fail to run properly.

---

* If this example does not run correctly, first compile and flash the **Edgi-Talk_M33_S_Template** project to ensure proper initialization and core startup sequence, then run this example.
* To enable the M55 core, open the following configuration in the **M33 project**:

```
RT-Thread Settings --> Hardware --> select SOC Multi Core Mode --> Enable CM55 Core
```
