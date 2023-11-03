#include <ESP8266WebServer.h>
#include <Arduino.h>

class ServerControl
{
public:
	ServerControl()
	{
		server = new ESP8266WebServer(80);
		Serial.println("Server created");
		server->on("/on", [this] {onLight();});
		server->on("/off", [this] {offLight();});
		server->begin();
	}
	void handleClient(){
		server->handleClient();
	}

private:
	unsigned short i = 0;
	ESP8266WebServer *server;
	void onLight()
	{
		Serial.println("ON");
		digitalWrite(LED_BUILTIN, LOW);
		server->send(200, "text/plain", String(i));	
		i++;
	}

	void offLight()
	{
		Serial.println("OFF");
		digitalWrite(LED_BUILTIN, HIGH);
		server->send(200, "text/plain", String(i));
		i++;
	}
};