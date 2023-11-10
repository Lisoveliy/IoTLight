#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <serviceData.h>
#include "serverControl.cpp"

ServerControl *control;

void setupWiFi()
{
	Serial.println("Running AP...");
	ESP8266WebServer server(80);

	WiFi.softAP(ServiceData::ApSSID, ServiceData::ApPassword);
	WiFi.softAPConfig(ServiceData::local_ip, ServiceData::gateway, ServiceData::subnet);
}
int connectToAP()
{
	int counter = 0;
	digitalWrite(LED_BUILTIN, LOW);
	while (WiFi.status() != WL_CONNECTED)
	{
		if (counter > 100)
		{
			return 1;
		}
		Serial.println(WiFi.status());
		delay(100);
		counter++;
	}

	Serial.print("Connected to ");
	Serial.println(ServiceData::SSID);
	digitalWrite(LED_BUILTIN, HIGH);
	return 0;
}
void setupServices()
{
	if (connectToAP() == 0)
	{
		delay(200);
		digitalWrite(LED_BUILTIN, LOW);
		delay(200);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(200);
		control = new ServerControl();
	}
	else
	{
		setupWiFi();
	}
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