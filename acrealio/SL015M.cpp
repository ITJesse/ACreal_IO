#include "Arduino.h"
#include "SL015M.h"

SL015M::SL015M()
{
  card = 0;
  rfcmdsent = false;
  rf_i = 0;
  pinset = false;
  readcmd = false;
}

void SL015M::setPins(int sensor, HardwareSerial* serialid)
{
    rfSENSOR = sensor;
    rfSerial = serialid;

    pinMode(rfSENSOR,INPUT);                            // Rfid sensor
    rfSerial->begin(RFID_BAUD);

    pinset=true;

}

void SL015M::update()
{
  if(!pinset)
    return;
  if(!readcmd)
    return;

    if(digitalRead(rfSENSOR)==LOW)             // card presence
    {
        uid[0] = 0xE0;
        uid[1] = 0x04;
        uid[2] = 0x01;
        uid[3] = 0x00;
        uid[4] = 0x3C;
        uid[5] = 0x94;
        uid[6] = 0x78;
        uid[7] = 0xFF;
        card = 1;
        readcmd = false;
    }
    else // if no tag in range
    {
        card = 0;
        rfcmdsent = false;
        readcmd = false;//reading finished (no card found)
    }
}

boolean SL015M::isCardPresent()
{
	return card;
}

void SL015M::setCardPresent()
{
    uid[0] = 0xE0;
    uid[1] = 0x04;
    uid[2] = 0x01;
    uid[3] = 0x00;
    uid[4] = 0x3C;
    uid[5] = 0x94;
    uid[6] = 0x78;
    uid[7] = 0xFF;
	card = 1;
}

void SL015M::read()
{
  readcmd=true;
}

void SL015M::getUID(byte* uida)
{
	memcpy(uida,uid,8);
}
