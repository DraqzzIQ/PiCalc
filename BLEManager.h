#pragma once
#define PICO
#ifdef PICO
#include <vector>
#include <iostream>
#include "btstack.h"
#include "pico/cyw43_arch.h"
#include "casio_os.h"
#include "Utils.h"

class BLEManager
{
    public:
        BLEManager();
        /// <summary>
        /// Sends the current display frame to the connected device
        /// and splits it into 
        /// </summary>
        void send_display_frame(std::vector<uint8_t> display_bytes, std::vector<uint8_t> symbol_bytes);

    private:
        /// <summary>
        /// Initializes L2CAP, the Security Manager, and configures the ATT Server with the pre-compiled
        /// ATT Database generated from casio_os.gatt. Finally, it configures the advertisements 
        /// and boots the Bluetooth stack. 
        /// </summary>
        void setup();
};
#endif