//
// Created by Marcin Zawada on 07.12.2017.
//

#ifndef ADNS_5050_H
#define ADNS_5050_H

class ADNS_5050 {

public:
    static const char REG_PRODUCT_ID      = 0x00;
    static const char REG_REVISION_ID     = 0x01;
    static const char REG_MOTION          = 0x02;
    static const char REG_DELTA_X         = 0x03;
    static const char REG_DELAT_Y         = 0x04;
    static const char REG_SQUAL           = 0x05;
    static const char REG_SHUTTER_UPPER   = 0x06;
    static const char REG_SHUTTER_LOWER   = 0x07;
    static const char REG_MAXIMUM_PIXEL   = 0x08;
    static const char REG_PIXEL_SUM       = 0x09;
    static const char REG_MINIMUM_PIXEL   = 0x0a;
    static const char REG_PIXEL_GRAB      = 0x0b;
    //Reserved 0x0c
    static const char REG_MOUSE_CONTROL   = 0x0d;
    //Reserved 0x0e - 0x18
    static const char REG_MOUSE_CONTROL_2 = 0x19;
    //Reserved 0x1a - 0x21
    static const char REG_LED_DC_MODE     = 0x22;
    //Reserved 0x23 - 0x39
    static const char REG_CHIP_RESET      = 0x3a;
    //Reserved 0x3b - 0x3d
    static const char REG_PRODUCT_ID_2    = 0x3e;
    static const char REG_INV_REV_ID      = 0x3f;
    //Reserved 0x40 - 0x62
    static const char REG_MOTION_BURST    = 0x63;

    static const char DEFAULT_REG_VAL_PRODUCT_ID      = 0x12;
    static const char DEFAULT_REG_VAL_REVISION_ID     = 0x01;
    static const char DEFAULT_REG_VAL_MOTION          = 0x00;
    static const char DEFAULT_REG_VAL_MOUSE_CONTROL   = 0x00;
    static const char DEFAULT_REG_VAL_MOUSE_CONTROL_2 = 0x08;
    static const char DEFAULT_REG_VAL_LED_DC_MODE     = 0x00;
    static const char DEFAULT_REG_VAL_PRODUCT_ID_2    = 0x26;
    static const char DEFAULT_REG_VAL_INV_REV_ID      = 0xFE;
    static const char DEFAULT_REG_VAL_MOTION_BURST    = 0x00;

    static const int T_PD         = 50000000;
    static const int T_WAKEUP     = 55000000;
    static const int T_RESET      =      250;
    static const int T_MOT_RST    = 50000000;
    static const int T_R_SDIO     =      300;
    static const int T_F_SDIO     =      300;
    static const int T_DLY_SDIO   =      120;
    static const int T_HOLD_SDIO  =      100;
    static const int T_SETUP_SDIO =      120;
    static const int T_SWW        =    30000;
    static const int T_SWR        =    20000;
    static const int T_SRW        =      500;
    static const int T_SRR        =      500;
    static const int T_SRAD       =     4000;
    static const int T_BEXIT      =      250;
    static const int T_NCS_SCLK   =      120;
    static const int T_SCLK_NCS_R =      120;
    static const int T_SCLK_NCS_W =    20000;
    static const int T_NCS_SDIO   =      500;

    unsigned char pin_sdio;
    unsigned char pin_sclk;
    unsigned char pin_ncs;

    static const int NUM_PIXELS = 360;

    ADNS_5050 () : ADNS_5050 (1, 15, 16) {}
    ADNS_5050 (unsigned char pin_sdio, unsigned char pin_sclk, unsigned char pin_ncs);

    bool          self_test      ();
    void          transmit       (unsigned char addr, unsigned char data);
    unsigned char receive        (unsigned char addr);
    unsigned char get_product_id ();

private:
    void          sync     ();
    void          write    (unsigned char data);
    unsigned char read     ();
    void          ns_delay (int nanoseconds);

};

#endif //ADNS_5050_H
