# CubeSat System prototype project
------

#### Our CubeSat prototype
![](.gitimg/photo.png)
------
#### View live satellite data at our [website.](https://cube-sat.000webhostapp.com/)


------

If you are interested to learn more about this topic feel free to check out our NASA Space Apps [project page.](https://2021.spaceappschallenge.org/challenges/statements/drones-and-satellites-for-urban-development/teams/space-sense/project)

## CubeSat & Ground Station

### Arduino setup for ESP32

1. Go to `Preferences/Aditional Boards Manager URLs`:
2. Paste the json link there
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
3. Install latest version of `esp32` boards from `Tools/Board:*/Boards Manager.../`

### Run Projects

1. Open `cubesat_prototype/cubesat_prototype.ino`
2. Go to `Tools/Manage Libraries../`
3. Install or have installed libraries
    * `RF24`(v1.4.1)
    * `Adafruit GPS` (v1.5.4)
    * `MPU6050_light` (v1.2.1)
    * `OneWire` (v2.3.5)
    * `DallasTemperature` (v3.9.1)
> Note: In brackets - Library version tested with
4. Compile

----


1. Open `ground_station_prototype/ground_station_prototype.ino`
2. Go to `Tools/Manage Libraries../`
3. Install or have installed libraries
    * `RF24`(v1.4.1)
> Note: In brackets - Library version tested with
4. Compile

### Select board and upload settings

- Board: 'ESP32-Wrower Module'
- Upload Speed: '921600'
- Flash Frequency: '80mHz'
- Flash Mode: 'QIO'
- Partition scheme: 'NO OTA (2MB APP/2MB SPIFFS)'
- Debug level: None
- Port: Select ESP32 Board COM/ttyUSB

> Recommended: Arduino v1.8.13+

### Wiring schematics

- Check wiring of [Electrical Power System](schematics/wiring/eps.pdf)
- Check wiring of [CubeSat](schematics/wiring/satellites_and_gs.pdf)

## Web App Setup

### Install

```bash
npm install
```

### Start development server

```bash
npm run dev
```

### Build for production

```bash
npm run build
```

### Webhosting

Copy `/dist` to your root.

> Requirements: Node.js v14+

