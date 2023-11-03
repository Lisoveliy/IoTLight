#include <ESP8266WebServer.h>
#include <Arduino.h>

class ServerControl
{
public:
	ServerControl()
	{
		server = new ESP8266WebServer(80);
		Serial.println("Server created");
		server->on("/on", [this]() {this->onLight();});
		server->on("/off", [this]() {this->offLight();});
		server->begin();
	}
	ESP8266WebServer *getServer()
	{
		return server;
	}

private:
	ESP8266WebServer *server;
	void onLight()
	{
		Serial.println("ON");
		digitalWrite(LED_BUILTIN, LOW);
		this->getServer()->send(200, "text/plain", "DONE");
	}

	void offLight()
	{
		Serial.println("OFF");
		digitalWrite(LED_BUILTIN, HIGH);
		this->getServer()->send(200, "text/plain", "DONE");
	}
};