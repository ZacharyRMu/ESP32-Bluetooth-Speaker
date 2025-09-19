# ESP32 Bluetooth Speaker with Controls

A DIY Bluetooth speaker project using an ESP32 microcontroller, a MAX98357A I²S DAC amplifier, and control buttons. Stream audio via Bluetooth A2DP, and control playback, track navigation, and volume directly from buttons.

---

## Table of Contents

- [Features](#features)  
- [Hardware Requirements](#hardware-requirements)  
- [Circuit / Wiring](#circuit--wiring)  
- [Software & Libraries](#software--libraries)  
- [Usage](#usage)  
- [Troubleshooting](#troubleshooting)  
- [Optional Enhancements](#optional-enhancements)  
- [Project Structure](#project-structure)  
- [License](#license)

---

## Features

- Bluetooth A2DP audio streaming from any compatible device (phone, computer, etc.)  
- Physical controls: play/pause, next/previous track, volume up/down  
- Uses I²S interface with MAX98357A amplifier for better audio quality  
- Configurable and extensible (add LEDs, battery, enclosures, etc.)

---

## Hardware Requirements

| Component | Description / Notes |
|---|---|
| ESP32 board | Any variant that supports Bluetooth + I²S; power via USB or external supply |
| MAX98357A I²S amplifier module | To convert digital audio to analog and drive the speaker |
| Speaker | 4 Ω or 8 Ω, approx. 3 W recommended |
| Push-buttons (×5) | For Play/Pause, Next Track, Previous Track, Volume Up, Volume Down |
| Jumper wires | For connections between ESP32, amplifier, buttons |
| Capacitor (10 µF, optional) | Between VIN and GND of amplifier to smooth power & reduce noise |
| Micro-USB cable | To program and power the ESP32 |
| Enclosure (optional) | To house the electronics nicely and safely |

---

## Circuit / Wiring

**Connections:**

- **Power**  
  - VIN on ESP32 → VIN on MAX98357A  
  - GND → GND (common ground)

- **I²S Audio Signals**  
  - I²S_BCLK (bit clock) → GPIO 27  
  - I²S_LRC (word select / left-right clock) → GPIO 14  
  - I²S_DIN (audio data) → GPIO 26  

- **Buttons** (one side of each button to GND; the other to the ESP32 GPIO pins)  
  - Play/Pause → GPIO 5  
  - Previous Track → GPIO 18  
  - Next Track → GPIO 19  
  - Volume Up → GPIO 21  
  - Volume Down → GPIO 22  

- **Optional components**  
  - 10 µF capacitor between VIN & GND at the amplifier module (reduces noise)  
  - If using amplifier shutdown / gain pins, connect per the datasheet or leave floating if unused

---

## Software & Libraries

- **Arduino IDE / PlatformIO**  
- Required libraries:  
  - [ESP32-A2DP](https://github.com/pschatzmann/ESP32-A2DP) — for Bluetooth audio sink  
  - [Arduino-Audio-Tools](https://github.com/pschatzmann/arduino-audio-tools) — for I²S & audio stream handling  

**Basic flow:**  
1. Initialize I²S stream with the given pins  
2. Start Bluetooth A2DP sink (set device name, default volume)  
3. In main loop, poll buttons with debounce logic  
4. On button presses, issue commands: play/pause, next, previous, volume up/down  

---

## Usage

1. Clone this repository.  
2. Install required libraries (Arduino IDE library manager / PlatformIO, or clone directly).  
3. Connect hardware per wiring instructions.  
4. Upload the code to the ESP32.  
5. Power it up.  
6. On your phone/computer, pair with Bluetooth device named **“ESPEAKER”** (default).  
7. Play audio and use the buttons to control playback and volume.  

---

## Troubleshooting

| Issue | Possible Cause | Solution |
|---|---|---|
| No audio / speaker silent | Wiring error; amplifier VIN not powered; ground not common | Double-check wiring; ensure amplifier module is powered; verify I²S pins match code |
| Distorted or noisy audio | Voltage supply noisy; missing capacitor; gain too high | Add the 10 µF capacitor; check amplifier gain settings; use a clean power supply |
| Buttons not responding | Wrong pins; no pull-ups; bouncing | Make sure button pins match code; use `INPUT_PULLUP` mode; implement debounce |
| BLE not pairing / not visible | Device name wrong; Bluetooth not started; power issues | Confirm `a2dp_sink.start("ESPEAKER")` runs; check ESP32’s Bluetooth functionality |

---

## Optional Enhancements

- Add battery power (for portability), e.g. LiPo + charging circuit (e.g., TP4056)  
- Enclosure: 3D-printed, wooden box, repurposed case  
- Status LEDs: indicate pairing, connected, playing state  
- RGB LEDs synced to music for visual effects  
---

## License

Specify your license here. For example: MIT License — see [LICENSE](LICENSE) file.  

