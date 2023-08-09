#include "Particle.h"
#include "EthernetCellularRK.h"

//STARTUP(BLE.selectAntenna(BleAntennaType::EXTERNAL));

//STARTUP(System.enableFeature(FEATURE_DISABLE_LISTENING_MODE));


// serial logger on serial2
// Serial2LogHandler logHandler(115200, LOG_LEVEL_ALL);
SerialLogHandler logHandler(115200, LOG_LEVEL_ALL);

// SYSTEM_THREAD(ENABLED) and SYSTEM_MODE(SEMI_AUTOMATIC) are required
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);

unsigned long next_time;

void setup() {

    // just to test:
    WiFi.clearCredentials();

    delay(2s);

    Log.info("ps-eth-rk");
    Log.info("System version: %s", System.version().c_str());
    Log.info("System deviceID: %s", System.deviceID().c_str());
    uint8_t addr[6];
    Ethernet.macAddress(addr);
    Log.info("Mac address: %02x:%02x:%02x:%02x:%02x:%02x", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
    

  

    if (!System.featureEnabled(FEATURE_ETHERNET_DETECTION)) {

        Log.info("Enabling Ethernet...");
        System.enableFeature(FEATURE_ETHERNET_DETECTION);

/*
        if_wiznet_pin_remap remap = {};
        remap.base.type = IF_WIZNET_DRIVER_SPECIFIC_PIN_REMAP;

        remap.cs_pin = D1;
        remap.reset_pin = D3;
        remap.int_pin = D0;

        auto ret = if_request(nullptr, IF_REQ_DRIVER_SPECIFIC, &remap, sizeof(remap), nullptr);

        if (ret != SYSTEM_ERROR_NONE) {

            Log.error("Ethernet GPIO config error: %d", ret);

        } else {

            delay(500);
            System.reset();
        }
        */
    }

    // You must add this to your setup() function
    EthernetCellular::instance().setup();

    next_time = millis() + 1000;
}

void loop() {
    
    // You must add this to your loop() function
    EthernetCellular::instance().loop();

    unsigned long now = millis();

    if(next_time < now) {

        while(next_time < now) {
        next_time += 1000;
        }

        Log.info("Ethernet: %s, WiFi: %s, Cloud: %s",
            (Ethernet.ready()?"ready":"not ready"),
            (WiFi.ready()?"ready":"not ready"),
            (Particle.connected()?"connected":"not connected"));
    }
}