#define LOAD_CELL_BOOL true
#define NETWORK_HOST false

#include <WiFiNINA.h>
#include "src/libraries/Arduino_LSM6DSOX/src/Arduino_LSM6DSOX.h"
#include "lib/wifi.hpp"
#include "lib/led.hpp"
#include "lib/structs.hpp"
#include "lib/load_cell.hpp"
#include "arduino_secrets.h"

#define CMD_CHECK_INTERVAL (1000000) // The interval in microseconds in which the program checks if it has received new commands over UDP.

LedController LED;
WifiController * wifi;

#if LOAD_CELL_BOOL
// #define CALIBRATION_FACTOR 2995000
#define CALIBRATION_FACTOR_X 10000000
#define CALIBRATION_FACTOR_Y  1000000
PacketBufferLoadCell packetBufferLoadCell;
LoadCell* loadCell;
#else
PacketBuffer packetBuffer;
#endif

long now;

void setup() {
    Serial.begin(115200); // Start Serial connection if any.
    LED.init(); // Initialise the LEDs
    LED.set(ledColor::BLUE);
    #if NETWORK_HOST
    wifi = new WifiController(); // Initialize 
    wifi->waitUntilConnectionToAP();
    #else
    wifi = new WifiController(SECRET_SSID, SECRET_PASS); // Initialize 
    wifi->waitUntilConnectedToAP();
    #endif
    wifi->waitForFirstReceivedPacket();
    LED.clear(ledColor::BLUE);
    LED.set(ledColor::RED);
    #if LOAD_CELL_BOOL
    loadCell = new LoadCell(CALIBRATION_FACTOR_X, CALIBRATION_FACTOR_Y);
    #else
    IMU.begin();
    Wire.setClock(3000000); // Set I2C clock to max of 400kHz (Currently 3 MHz)
    delay(1000);
    IMU.calibrateSensors();
    #endif
    LED.clear(ledColor::RED);
    LED.set(ledColor::GREEN);

    now = millis();
}

void loop() {
    // long now_loop = millis();
    // Serial.println(now_loop - now);
    // now = now_loop;
    #if LOAD_CELL_BOOL
    loadCell->readLoadCell(packetBufferLoadCell);
    wifi->sendSensorData(packetBufferLoadCell);
    #else
    IMU.readSensors(packetBuffer);
    wifi->sendSensorData(packetBuffer);
    #endif
    // delay(1000);
}
