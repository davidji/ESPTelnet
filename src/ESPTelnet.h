/* ------------------------------------------------- */

#pragma once

#ifndef ESPTelnet_h
#define ESPTelnet_h

/* ------------------------------------------------- */

#if defined(ARDUINO_ARCH_ESP32)
  #include <WiFi.h>
  #include <WebServer.h>
#elif defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266WebServer.h>
#endif

/* ------------------------------------------------- */

class ESPTelnet : public Stream {
  typedef void (*CallbackFunction) (String str);

  public:
    ESPTelnet();

    bool begin();
    void loop();
    void stop();

    int available();
    int read();
    int peek();
    void flush();

    size_t write(uint8_t);

    String getIP() const;
    String getLastAttemptIP() const;
    
    void onConnect(CallbackFunction f);
    void onConnectionAttempt(CallbackFunction f);
    void onReconnect(CallbackFunction f);
    void onDisconnect(CallbackFunction f);
    
  protected:
    WiFiServer server = WiFiServer(23);
    WiFiClient client;
    boolean isConnected = false;
    String ip = "";
    String attemptIp;

    bool isClientConnected(WiFiClient client);

    CallbackFunction on_connect = NULL;
    CallbackFunction on_reconnect  = NULL;
    CallbackFunction on_disconnect = NULL;
    CallbackFunction on_connection_attempt = NULL;
};

/* ------------------------------------------------- */

  // << operator
  template<class T> inline ESPTelnet &operator <<(ESPTelnet &obj, T arg) { obj.print(arg); return obj; } 

/* ------------------------------------------------- */
#endif
/* ------------------------------------------------- */