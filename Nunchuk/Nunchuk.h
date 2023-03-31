#ifndef NUNCHUNK_H
#define NUNCHUNK_H

#include <Arduino.h>
#include <Wire.h>

// #define I2C_SDA 23
// #define I2C_SCL 22
#define NUNCHUK_ADRESS 0x52
//
class Nunchuk
{
public:
    static Nunchuk *getInstance()
    {
        if (myInstance == nullptr)
        {
            myInstance = new Nunchuk();
        }
        //
        return myInstance;
    }

    bool isValidate() const;

    int8_t getJoyX() const;

    int8_t getJoyY() const;

    int8_t getBtnC() const;

    int8_t getBtnZ() const;

    int16_t getAccX() const;
    int16_t getAccY() const;
    int16_t getAccZ() const;

    bool begin(uint8_t sdaPin = 23, uint8_t sclPin = 22);

    void update();

    void printToSerial();

private:
    Nunchuk();
    ~Nunchuk();

    void _init_nunchuk();
    void _process_datas();
    void _request_datas();
    //
    static Nunchuk *myInstance;
    //
    bool _isvalidate;

    int _tab[6];
    int8_t _btnC;
    int8_t _btnZ;
    int _accX, _accY, _accZ;
};
#endif