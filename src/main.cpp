#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <serviceData.h>
#include "serverControl.cpp"

ServerControl *control;

void connectToAP()
{
	digitalWrite(LED_BUILTIN, LOW);
	digitalWrite(D0, HIGH);
	Serial.print("Connecting to \"");
	Serial.print(ServiceData::SSID);
	Serial.print("\"");
	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(100);
	}
	digitalWrite(D0, LOW);
	Serial.println();

	Serial.print("Connected to \"");
	Serial.print(ServiceData::SSID);
	Serial.print("\"");
	Serial.println();

	digitalWrite(LED_BUILTIN, HIGH);
}

void setupServices()
{
	connectToAP();
	delay(200);
	digitalWrite(LED_BUILTIN, LOW);
	delay(200);
	digitalWrite(LED_BUILTIN, HIGH);
	delay(200);
	control = new ServerControl();
}

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(D0, OUTPUT);
	digitalWrite(D0, LOW);
	WiFi.begin(ServiceData::SSID, ServiceData::Password);
	Serial.begin(115200);
	setupServices();
}

void loop()
{
	if (WiFi.status() != WL_CONNECTED)
	{
		connectToAP();
	}
	control->handleClient();
}