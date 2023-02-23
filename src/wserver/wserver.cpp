#include "wserver.hpp"
#include "OLED/oled.hpp"
#include <string>

const char *Web::serverName = "http://home.nilus.ink/weather/";

void Web::setup()
{
    Serial.println("connecting to wifi...");

    OLED::u8g2.firstPage();
    OLED::u8g2.setFont(u8g2_font_ncenB10_tr);
    OLED::u8g2.drawStr(10, 28, "Connecting to");
    OLED::u8g2.drawStr(45, 44, "WiFi");
    OLED::u8g2.nextPage();

    WiFi.begin(SSID, PWD);
    int i = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        i++;

        delay(500);
        Serial.print("*");

        std::string dots(i % 4, '.');
        dots = "WiFi " + dots;

        OLED::u8g2.firstPage();
        OLED::u8g2.setFont(u8g2_font_ncenB10_tr);
        OLED::u8g2.drawStr(10, 28, "Connecting to");
        OLED::u8g2.drawStr(45, 44, dots.c_str());
        OLED::u8g2.nextPage();
    }

    Serial.print("The IP Address of ESP8266 Module is: ");
    Serial.print(WiFi.localIP()); // Print the IP address
}

void Web::sendData(Sensor::w_data_t d)
{
    if (!(isnan(d.temperature) || isnan(d.humidity)))
    {
        // sending stuff
        if (WiFi.status() == WL_CONNECTED)
        {
            WiFiClient client;
            HTTPClient http;

            // Your Domain name with URL path or IP address with path
            http.begin(client, serverName);

            // If you need Node-RED/server authentication, insert user and password below
            // http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");

            // Specify content-type header
            http.addHeader("Content-Type", "application/json");
            // Data to send with HTTP POST

            char buff[255];

            /*
            station_id
            station_secret
            temperature
            temperature_index
            humidity
            air_pressure*/

            snprintf(buff, 254, "{\"temperature\": %f, \"humidity\": %f, \"temperature_index\": %f, \"station_id\": %d, \"station_secret\": %s}",
                     d.temperature, d.humidity, d.temperature_index, STATION_ID, STATION_SECRET);

            // Serial.println(buff);

            String httpRequestData = buff;
            // Send HTTP POST request
            int httpResponseCode = http.POST(httpRequestData);

            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);

            // Free resources
            http.end();
        }
        else
        {
            Serial.println("WiFi Disconnected");
        }
    }
    else
    {
        Serial.println("Couldn't read sensor");
    }
}
