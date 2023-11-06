#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <serviceData.h>
#include "serverControl.cpp"

ServerControl *control;

void connectToAP()
{
	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.println(WiFi.status());
		delay(100);
	}

	Serial.print("Connected to ");
	Serial.println(ServiceData::SSID);
}
void setupServices()
{
	connectToAP();
	digitalWrite(LED_BUILTIN, HIGH);
	delay(200);
	digitalWrite(LED_BUILTIN, LOW);
	delay(200);
	digitalWrite(LED_BUILTIN, HIGH);
	delay(200);
	digitalWrite(LED_BUILTIN, LOW);
	control = new ServerControl();
	digitalWrite(LED_BUILTIN, HIGH);
}

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(D0, OUTPUT);
	digitalWrite(D0, LOW);
	digitalWrite(LED_BUILTIN, LOW);
	WiFi.begin(ServiceData::SSID, ServiceData::Password);
	Serial.begin(115200);
	setupServices();
}

void loop()
{
	if(WiFi.status() != WL_CONNECTED){
		connectToAP();
	}
	control->handleClient();
}