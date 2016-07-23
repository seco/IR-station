#include "httpClient.h"

#include <ArduinoJson.h>
#include "config.h"
#include "time_op.h"
#include "IR_op.h"

#define SERVER_HOSTNAME   "ir-station.kerikeri.top"
#define SERVER_PORT       8080

bool notifyIP() {
  WiFiClient client;
  if (!client.connect(SERVER_HOSTNAME, SERVER_PORT)) {
    println_dbg("Error: Connection Failed");
    return false;
  }
  String postData = "{\"device_name\":\"" + station.mdns_hostname + "\",\"local_ip\":\"" + String(WiFi.localIP()[0], DEC) + "." + String(WiFi.localIP()[1], DEC) + "." + String(WiFi.localIP()[2], DEC) + "." + String(WiFi.localIP()[3], DEC) + "\"}";
  println_dbg("Post data: " + postData);
  client.println("POST / HTTP/1.1");
  client.println("Host: "SERVER_HOSTNAME);
  client.println("Content-Length: " + String(postData.length(), DEC));
  client.println("Connection: Close");
  client.println("");
  client.println(postData);

  uint32_t timestamp = millis();
  uint32_t timeout = 2000;
  /* サーバーからの返答を待つ */
  while (true) {
    wdt_reset();

    /* サーバーから返答が来たら離脱 */
    if (client.available()) break;

    /* タイムアウト処理 */
    if (millis() - timestamp > timeout) {
      println_dbg("Timeout: Read Server");
      return "";
    }
  }
  client.setTimeout(10);
  String resp = client.readString();
  resp.replace("\r", "");
  resp.replace("\n", " ");
  print_dbg("Response: ");
  println_dbg(resp);
  client.stop();
}

void notifyIPTask() {
  static uint32_t prev_sec;
  uint32_t now_sec = now();
  if (now_sec > prev_sec + 300) {
    prev_sec = now_sec;
    notifyIP();
  }
}
