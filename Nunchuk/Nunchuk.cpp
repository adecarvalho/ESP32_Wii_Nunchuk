#include "Nunchuk.h"
//
Nunchuk *Nunchuk::myInstance = nullptr;
//
Nunchuk::Nunchuk()
{
    _isvalidate = false;

    for (int i = 0; i < 6; i++)
    {
        _tab[i] = 0;
    }
    //
    _btnC = -1;
    _btnZ = -1;
    _accX = 0;
    _accY = 0;
    _accZ = 0;
}
//
Nunchuk::~Nunchuk() {}
//
bool Nunchuk::begin(uint8_t sdaPin, uint8_t sclPin)
{
    if (Wire.begin(sdaPin, sclPin, 100000L) == false)
    {
        _isvalidate = false;
        return false;
    }
    else
    {
        _isvalidate = true;
        _init_nunchuk();
        update();
        delay(200);
    }
    //
    return true;
}
//
int16_t Nunchuk::getAccX() const
{
    return _accX;
}
//
int16_t Nunchuk::getAccY() const
{
    return _accY;
}
//
int16_t Nunchuk::getAccZ() const
{
    return _accZ;
}
//
int8_t Nunchuk::getJoyX() const
{
    return _tab[0];
}
//
int8_t Nunchuk::getJoyY() const
{
    return _tab[1];
}
//
int8_t Nunchuk::getBtnC() const
{
    return _btnC;
}
//
int8_t Nunchuk::getBtnZ() const
{
    return _btnZ;
}
//
bool Nunchuk::isValidate() const
{
    return _isvalidate;
}
//
void Nunchuk::printToSerial()
{
    Serial.print(_tab[0]);
    Serial.print('\t');
    //
    Serial.print(_tab[1]);
    Serial.print('\t');
    //
    Serial.print(_accX);
    Serial.print('\t');
    //
    Serial.print(_accY);
    Serial.print('\t');
    //
    Serial.print(_accZ);
    Serial.print('\t');
    //
    Serial.print(_btnC);
    Serial.print('\t');
    //
    Serial.print(_btnZ);
    Serial.print('\t');

    Serial.println();
}
//
void Nunchuk::_init_nunchuk()
{
    Wire.beginTransmission(NUNCHUK_ADRESS);
    Wire.write(0xF0);
    Wire.write(0x55);
    Wire.endTransmission();
}
//
void Nunchuk::_process_datas()
{
    // joyX
    if (_tab[0] > 200)
    {
        _tab[0] = 1;
    }
    else if (_tab[0] < 80)
    {
        _tab[0] = -1;
    }
    else
    {
        _tab[0] = 0;
    }
    //***************
    // joyY
    if (_tab[1] > 200)
    {
        _tab[1] = 1;
    }
    else if (_tab[1] < 80)
    {
        _tab[1] = -1;
    }
    else
    {
        _tab[1] = 0;
    }
    //******************
    // btnZ
    if (_tab[5] & 0b00000001)
    {
        _btnZ = -1;
    }
    else
    {
        _btnZ = 1;
    }
    //****************
    // btnC
    if (_tab[5] & 0b00000010)
    {
        _btnC = -1;
    }
    else
    {
        _btnC = 1;
    }
    //*******************
    // accX
    _accX = _tab[2];
    _accX = _accX << 2;
    //
    if ((_tab[5] >> 2) & 0x01)
    {
        _accX += 1;
    }
    //
    if ((_tab[5] >> 3) & 0x01)
    {
        _accX += 2;
    }
    //
    // accY
    _accY = _tab[3];
    _accY = _accY << 2;
    //
    if ((_tab[5] >> 4) & 0x01)
    {
        _accY += 1;
    }
    //
    if ((_tab[5] >> 5) & 0x01)
    {
        _accY += 2;
    }
    // accZ
    _accZ = _tab[4];
    _accZ = _accZ << 2;
    //
    if ((_tab[5] >> 6) & 0x01)
    {
        _accZ += 1;
    }
    //
    if ((_tab[5] >> 7) & 0x01)
    {
        _accZ += 2;
    }
}
//
void Nunchuk::update()
{
    Wire.requestFrom(NUNCHUK_ADRESS, 6);
    //
    for (int i = 0; i < 6; i++)
    {
        _tab[i] = Wire.read();
    }
    //
    Wire.endTransmission();
    //
    _process_datas();
    //
    _request_datas();
}
//
void Nunchuk::_request_datas()
{
    Wire.beginTransmission(NUNCHUK_ADRESS);
    Wire.write(0x00);
    Wire.endTransmission();
}