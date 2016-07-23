/*
   IR-station Ver.1.0.0
   Infrared Remote Controller with ESP8266 WiFi Module

   Author:  kerikun11 (Github: kerikun11)
   Date:    2016.01.22
*/

#include <ESP8266WiFi.h>
#include <FS.h>
#include "config.h"
#include "IR_op.h"
#include "OTA_op.h"
#include "server_op.h"
#include "httpClient.h"
#include "led_op.h"

void setup() {
  // Prepare Serial debug
  Serial.begin(115200);
  println_dbg("");
  println_dbg("Hello, I'm ESP-WROOM-02");

  // prepare GPIO
  pinMode(PIN_IR_IN, INPUT);
  pinMode(PIN_IR_OUT, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  digitalWrite(PIN_IR_OUT, LOW);

  // Setup Start
  indicator.green(1023);

  // IR-station setup
  station.modeSetup();

  // Setup Completed
  indicator.green(0);
  println_dbg("Setup Completed");
}

void loop() {
  OTATask();
  serverTask();

  switch (station.mode) {
    case IR_STATION_MODE_STA:
      indicator.blue(1023);
      if ((WiFi.status() != WL_CONNECTED)) {
        indicator.red(1023);
      } else {
        indicator.red(0);
      }
      notifyIPTask();
      break;
    case IR_STATION_MODE_AP:
    case IR_STATION_MODE_NULL:
      indicator.blue(1023);
      break;
  }
}

