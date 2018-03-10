//
// Created by Marcin Zawada on 07.12.2017.
//

#include "ADNS_5050.h"
#include <iostream>
#include <wiringPi.h>

/**
 * Constructor with user predefined pins
 * @param pin_sdio SDIO pin
 * @param pin_sclk SCLK pin
 * @param pin_ncs  NCS  pin
 */
ADNS_5050::ADNS_5050 (unsigned char pin_sdio, unsigned char pin_sclk, unsigned char pin_ncs) {
    this->pin_sdio =  pin_sdio;
    this->pin_sclk =  pin_sclk;
    this->pin_ncs  =  pin_ncs ;

    wiringPiSetup () ;

    pinMode (this->pin_sdio, OUTPUT) ;
    pinMode (this->pin_sclk, OUTPUT) ;
    pinMode (this->pin_ncs,  OUTPUT) ;

    this->sync();

    this->transmit(ADNS_5050::REG_CHIP_RESET, 0x5a);
    this->ns_delay(ADNS_5050::T_WAKEUP);

    std::cout << "running ADNS_5050..." << std::endl;
}

/**
 * Reads and returns product ID
 * @return hex number with product ID read from sensor
 */
unsigned char ADNS_5050::get_product_id () {
    return this->receive (ADNS_5050::REG_PRODUCT_ID) ;
}

/**
 * Tests if device work properly
 * Check if device product_id is correct
 * @return true if fine, false if something wrong
 */
bool ADNS_5050::self_test () {
    return (ADNS_5050::DEFAULT_REG_VAL_PRODUCT_ID
            && this->receive(ADNS_5050::REG_PRODUCT_ID));
}

/**
 * Synchronize sensor, enable - wait - disable
 */
void ADNS_5050::sync () {
    digitalWrite(this->pin_ncs, LOW);
    this->ns_delay(2000);
    digitalWrite(this->pin_ncs, HIGH);
}

/**
 * Transmit data to sensor
 * @param addr Register address
 * @param data Data to write
 */
void ADNS_5050::transmit (unsigned char addr, unsigned char data) {
    this->write(addr);
    this->write(data);
}

/**
 * Receive data from sensor
 * @param addr addres of byte that will be read
 * @return read byte
 */
unsigned char ADNS_5050::receive (unsigned char addr) {
    this->write(addr);
    return this->read();
}

/**
 * Write data to SDIO pin
 * @param data
 */
void ADNS_5050::write (unsigned char data) {
    data |= 0x8;

    pinMode(this->pin_sdio, OUTPUT);
    digitalWrite(this->pin_sclk, HIGH);
    digitalWrite(this->pin_sdio, LOW);

    digitalWrite(this->pin_ncs, LOW);
    this->ns_delay(ADNS_5050::T_NCS_SDIO);

    for (char counter = 0; counter < 8; counter++) {
        digitalWrite(this->pin_sclk, LOW);

        if (data & 0x80)
            digitalWrite(this->pin_sdio, HIGH);
        else
            digitalWrite(this->pin_sdio, LOW);

        data = (data << 1);

        digitalWrite(this->pin_sclk, HIGH);
        this->ns_delay(ADNS_5050::T_HOLD_SDIO);
    }

    digitalWrite(this->pin_ncs, HIGH);
}

/**
 * Read data from SDIO pin
 * @return
 */
unsigned char ADNS_5050::read () {
    unsigned char data = 0x00;

    pinMode(this->pin_sdio, INPUT);
    digitalWrite(this->pin_sclk, HIGH);

    digitalWrite(this->pin_ncs, LOW);
    this->ns_delay(ADNS_5050::T_NCS_SDIO);

    for (char counter = 0; counter < 8; counter++) {
        digitalWrite(this->pin_sclk, LOW);

        if (digitalRead(this->pin_sdio))
            data |= 0x1;

        //If not last bit then shift
        if (counter != 7)
            data = (data << 1);

        this->ns_delay(ADNS_5050::T_HOLD_SDIO);
        digitalWrite(this->pin_sclk, HIGH);
    }

    digitalWrite(this->pin_ncs, HIGH);
    return data;
}

/**
 * Measure time in nanoseconds (truly not)
 * There is no possibility to make better precission then us.
 * @param nanoseconds
 */
void ADNS_5050::ns_delay (int nanoseconds) {
    if((float) nanoseconds / 1000 < 0) {
        delayMicroseconds(1);
    } else {
        delayMicroseconds((unsigned int) (nanoseconds / 100));
    }
}