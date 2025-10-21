# Edgi-Talk_WavPlayer Example Project

## Introduction

This example project is based on the **Edgi-Talk platform** and demonstrates **WAV audio playback**, running on the **RT-Thread real-time operating system (M33 core)**.
It allows users to quickly experience WAV audio file playback, verify audio decoding and driver interfaces, and provides a reference for future audio application development.

## Software Description

* Developed on the **Edgi-Talk** platform.

* Example features include:

  * WAV file parsing and playback
  * Audio output through onboard DAC or audio peripherals
  * Supports PCM16 WAV files
  * Supports sample rates of **16 kHz, 24 kHz, and 48 kHz**
  * Supports **stereo output**
  * Playback status information printed to the serial terminal

* The project structure is clear, making it easy to understand the interaction between audio playback drivers and the RT-Thread file system.

## Usage

### Build and Flash

1. Open the project and complete the build.
2. Connect the board’s **USB interface** to the PC using the **onboard DAP debugger**.
3. Use a programming tool to flash the compiled firmware to the development board.
4. Copy WAV audio files to the root directory of the SD card or external storage device, e.g., `16000.wav`.

### Running the Demo

* After flashing, power on the board to run the example.
* The system will automatically initialize I2C and I2S audio devices and mount the storage device.
* Users can start playback via the **serial terminal** using the following command:

```
wavplay -s 16000.wav
```

* Example serial output:

```
 \ | /
- RT -     Thread Operating System
 / | \     5.0.2 build Sep  8 2025 11:21:16
 2006 - 2022 Copyright by RT-Thread team
[I/I2C] I2C bus [i2c0] registered
[I/i2s] ES8388 init success.
[I/drv.mic] audio pdm registered.
[I/drv.mic] !!!Note: pdm depends on i2s0, they share clock.
found part[0], begin: 1048576, size: 29.739GB
Hello RT-Thread
This core is cortex-m33
msh />wavplay -s 16000.wav
[D/WAV_PLAYER] EVENT:PLAYSTOPPAUSERESUME, STATE:STOPPED -> PLAYING
[D/WAV_PLAYER] open wavplayer, device sound0
[D/WAV_PLAYER] Information:
[D/WAV_PLAYER] samplerate 16000
[D/WAV_PLAYER] channels 2
[D/WAV_PLAYER] sample bits width 16
[I/WAV_PLAYER] play start, uri=16000.wav
[I/i2s] Ready for I2S output
msh />
```

* During playback, the serial terminal will display the WAV file’s sample rate, number of channels, bit width, and playback status information.

## Notes

* WAV files must be **PCM16 format**, with sample rates of **16 kHz, 24 kHz, or 48 kHz**, and output must be **stereo**.
* To modify the project’s **graphical configuration**, open the configuration file using:

```
tools/device-configurator/device-configurator.exe
libs/TARGET_APP_KIT_PSE84_EVAL_EPC2/config/design.modus
```

* After modification, save the configuration and regenerate the code.
* Ensure that the storage device is correctly inserted and mounted; otherwise, audio playback will fail.

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
