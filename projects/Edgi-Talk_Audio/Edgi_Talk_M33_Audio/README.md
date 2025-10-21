# Edgi-Talk_Audio Example Project

## Introduction

This example project is based on the **Edgi-Talk platform** and demonstrates **audio recording and playback** functionality running on the **RT-Thread real-time operating system**.
Through this project, users can experience how audio data is captured from the microphone and played back through the speaker.
The playback/stop state can be controlled by a button, and the LED indicator reflects the current playback status.

## Software Description

* The project is developed based on the **Edgi-Talk M33** platform.

* The example includes the following features:

  * Audio capture via microphone
  * Audio playback through speaker
  * Button control for playback/stop
  * LED indicator for playback status

* The project structure is clear, making it easy to understand RT-Thread’s audio device driver and event handling mechanisms.

## Usage Instructions

### Compilation and Download

1. Open the project and complete the build process.
2. Connect the development board to the PC via the **onboard DAP downloader (USB interface)**.
3. Use a programming tool to flash the generated firmware onto the development board.

   * The project can automatically invoke the signing tool (e.g., `tools/edgeprotecttools/bin/edgeprotecttools.exe`) to merge and flash the firmware (e.g., `proj_cm33_s_signed.hex`).

### Running Results

* After flashing, power on the development board to run the example project.

* The LED is **ON by default**, indicating that audio playback is enabled.

* Press the button to **toggle the playback state**:

  * **Play**: LED is ON, and the microphone-captured audio is played through the speaker.
  * **Stop**: LED is OFF, and audio playback is paused.

* The system continuously captures and plays back audio data, achieving real-time audio loopback functionality.

## Notes

* To modify the project’s **graphical configuration**, open the configuration file with the following tool:

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
