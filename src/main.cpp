#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <serverControl.h>

const String SSID = "IoT-1986";
const String Password = "IoTPassword228";

ServerControl* control;
void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(D0, OUTPUT);
	digitalWrite(D0, LOW);
	digitalWrite(LED_BUILTIN, LOW);
	WiFi.begin(SSID, Password);
	Serial.begin(115200);
	while (WiFi.status() != WL_CONNECTED )
	{
		Serial.println(WiFi.status());
		delay(100);
	}
	Serial.println("Connected");
	digitalWrite(LED_BUILTIN, HIGH);
	control = new ServerControl();;
}
void loop(){
	control->handleClient();
}