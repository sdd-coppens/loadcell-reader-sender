#ifndef LOAD_CELL_HPP
#define LOAD_CELL_HPP

#include "HX711.h"
#include "structs.hpp"
#include "Arduino.h"

class LoadCell {
    private:
        int DOUT_X1 = 11;
        int CLK_X1 =  12;

        int DOUT_X2 = 9;
        int CLK_X2 =  10;

        int DOUT_Y1 = 3;
        int CLK_Y1  = 4;

        int DOUT_Y2 = 5;
        int CLK_Y2  = 6;

        HX711 sens_X1;
        HX711 sens_X2;
        HX711 sens_Y1;
        HX711 sens_Y2;
    public:
    LoadCell(int calibFactor_x, int calibFactor_y) {
        sens_X1.begin(DOUT_X1, CLK_X1);
        sens_X2.begin(DOUT_X2, CLK_X2);
        sens_Y1.begin(DOUT_Y1, CLK_Y1);
        sens_Y2.begin(DOUT_Y2, CLK_Y2);
        delay(500);
        sens_X1.set_scale(calibFactor_x);
        sens_X2.set_scale(calibFactor_x);
        sens_Y1.set_scale(calibFactor_y);
        sens_Y2.set_scale(calibFactor_y);
        delay(500);
        sens_X1.tare();
        sens_X2.tare();
        sens_Y1.tare();
        sens_Y2.tare();
        delay(1000);
    }

    void readLoadCell(PacketBufferLoadCell& packet) {
        // Serial.println("-----------------------");
        // Serial.println(sens_X1.get_units(), 5);
        // Serial.println(sens_X2.get_units(), 5);
        // Serial.println(sens_Y1.get_units(), 5);
        // Serial.println(sens_Y2.get_units(), 5);
        packet.packet.timestamp = micros();
        packet.packet.values[0] = sens_X1.get_units();
        packet.packet.values[1] = sens_X2.get_units();
        packet.packet.values[2] = sens_Y1.get_units();
        packet.packet.values[3] = sens_Y2.get_units();
    }
};

#endif