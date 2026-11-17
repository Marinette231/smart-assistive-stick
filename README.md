# 🦯 Smart Assistive Stick

An Arduino-based assistive device designed to help visually impaired individuals and elderly people navigate their surroundings more safely.

The project uses ultrasonic sensors to detect nearby obstacles and provides audio feedback through a buzzer. It also integrates GPS and GSM modules to send an emergency SMS containing the user's location when the emergency button is pressed.

## ✨ Features

- **Obstacle Detection:** Two ultrasonic sensors detect obstacles in the user's surroundings.
- **Audio Alerts:** A buzzer alerts the user when an obstacle is detected within the predefined range.
- **GPS Location:** A GPS module obtains the user's geographical coordinates.
- **Emergency SMS:** A GSM module sends an emergency message with a Google Maps location link.
- **Emergency Button:** Allows the user to trigger an emergency alert manually.

## 🛠️ Hardware Components

| Component | Purpose |
|---|---|
| Arduino Nano | Main controller |
| 2 × HC-SR04 Ultrasonic Sensors | Obstacle detection |
| NEO-6M GPS Module | Location tracking |
| SIM800L GSM Module | Emergency SMS communication |
| Buzzer | Audio feedback |
| Push Button | Emergency alert activation |
| LM2596 Buck Converter | Voltage regulation |
| Battery | Power supply |

## 💻 Technologies & Libraries

- Arduino C/C++
- Arduino IDE
- SoftwareSerial Library
- TinyGPS++ Library

## 🔌 Pin Configuration

| Component | Arduino Nano Pin |
|---|---|
| Ultrasonic Sensor 1 - TRIG | A0 |
| Ultrasonic Sensor 1 - ECHO | A1 |
| Ultrasonic Sensor 2 - TRIG | A2 |
| Ultrasonic Sensor 2 - ECHO | A3 |
| Buzzer | D8 |
| Emergency Button | D9 |
| GPS RX (Arduino) | D4 |
| GPS TX (Arduino) | D3 |
| GSM RX (Arduino) | D7 |
| GSM TX (Arduino) | D6 |

## ⚙️ How It Works

1. The ultrasonic sensors continuously measure the distance to nearby obstacles.
2. The Arduino Nano processes the sensor readings.
3. When an obstacle is detected within the configured range, the buzzer alerts the user.
4. The GPS module obtains the geographical coordinates.
5. When the emergency button is pressed, the GSM module sends an SMS containing an emergency message and the available GPS location.
6. The recipient can open the Google Maps link to view the shared location.

## 🚀 Getting Started

### Prerequisites

- Arduino IDE
- Arduino Nano
- Required hardware components
- TinyGPS++ library

### Setup Instructions

1. Clone or download this repository.
2. Open the Arduino sketch in Arduino IDE.
3. Install the TinyGPS++ library.
4. Connect the hardware components according to the pin configuration.
5. Update the emergency contact number in the code.
6. Select Arduino Nano as the target board and choose the correct COM port.
7. Upload the sketch to the Arduino Nano.

## 🔋 Power Supply Notes

- The SIM800L requires a separate, stable power supply capable of handling its current peaks.
- Ensure the Arduino and GSM module share a common ground.
- Use an appropriate regulated supply for the Arduino and other components.

## 🔮 Future Improvements

- Vibration-based alerts for improved accessibility.
- More advanced obstacle detection.
- Improved GPS and GSM communication reliability.
- Internet-based location monitoring.
- Compact enclosure and improved hardware design.

## ⚠️ Project Limitations

- GPS accuracy depends on satellite availability and signal conditions.
- GSM communication depends on network coverage and compatible 2G service.
- The current implementation sends location through an emergency SMS rather than providing continuous live tracking.
- Ultrasonic sensors may have difficulty detecting certain angled or soft surfaces.

## 🎯 Project Objective

The objective of this project is to develop a low-cost assistive device that combines obstacle detection with emergency location communication to improve mobility support and personal safety.

---

**Built with curiosity, code, and a little bit of Arduino magic. Tested multiple times like hell :skull:**

</> 
