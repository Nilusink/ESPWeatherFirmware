/**
 * @file wserver.hpp
 * @author Nilusink
 * @brief Connects to the API server and publishes the data (http://home.nilus.ink/redoc)
 * @version 1.0
 * @date 2023-02-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Arduino.h>
#include "sensor/sensor.hpp"
#include "secrets.h"


// DHT stuff
#define DHTPIN D3
#define DHTTYPE DHT22


namespace Web
{
    // DHT dht(DHTPIN, DHTTYPE);
    extern const char* serverName;

    /**
     * @brief initialize the internet connection
     * 
     */
    void setup();

    /**
     * @brief send the weather data
     * 
     * @param d weather data
     */
    void sendData(Sensor::w_data_t d);
}
