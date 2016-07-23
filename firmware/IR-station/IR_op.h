#ifndef IR_OPERATION
#define IR_OPERATION

#include <ESP8266WiFi.h>
#include "IR-lib.h"

#define IR_STATION_MODE_NULL  0
#define IR_STATION_MODE_STA   1
#define IR_STATION_MODE_AP    2

extern remocon ir[IR_CH_SIZE];

class IR_Station {
  public:
    uint8_t mode;
    String ssid;
    String password;
    String mdns_hostname;

    void modeSetup(void);
    void setMode(uint8_t newMode);
    void reset();

    void setupButtonInterrupt();

    void irSendSignal(int ch);
    int irRecodeSignal(int ch);

    String settingsCrcSerial(void);
    bool irDataBackupToFile(int ch);
    bool irDataRestoreFromFile(void);

    bool settingsRestoreFromFile(void);
    bool settingsBackupToFile(void);

  private:
};

extern IR_Station station;

bool writeStringToFile(String path, String dataString);
bool getStringFromFile(String path, String& dataString);

#endif

