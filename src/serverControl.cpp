#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <serviceData.h>
#include <PubSubClient.h>

class ServerControl
{
public:
	ServerControl()
	{
		connect();
	}
	void handleClient()
	{
		client.loop();
		if (!client.connected())
		{
			connect();
		}
	}

private:
	WiFiClient wclient;
	PubSubClient client;
	ESP8266WebServer *server;

	void connect()
	{
		client.setServer(ServiceData::Mqtt::Server.c_str(), ServiceData::Mqtt::Port);
		client.setClient(wclient);
		client.setCallback([this](char *topic, byte* payload, unsigned int length) {callback(topic, payload, length);});
		while (!client.connected())
		{
			// Attempt to connect
			Serial.println("Attempt to connect to MQTT broker");
			client.connect("ESP8266LIGHT_57876987", ServiceData::Mqtt::User.c_str(), ServiceData::Mqtt::Password.c_str());
			// Wait some time to space out connection requests
			delay(3000);
		}
		Serial.println("MQTT Connected!");
		client.subscribe(ServiceData::Commands::Branch.c_str(), 0);
	}

	void callback(char *topic, byte *payload, unsigned int length) {
		String data = "";
		for(int i = 0; i < length; i++){
		 	data+=(char)payload[i];
		}
		Serial.print("Recieved on topic");
		Serial.print(topic);
		Serial.print(": ");
		Serial.println(data);
		if(data == "ON"){
		 	onLight();
		}
		if(data == "OFF"){
			offLight();
		}
	}
	void onLight()
	{
		digitalWrite(D0, HIGH);
		sendData(ServiceData::Mqtt::Branch, "ON");
	}

	void offLight()
	{
		digitalWrite(D0, LOW);
		sendData(ServiceData::Mqtt::Branch, "OFF");
	}
	void sendData(String branch, String data){
		Serial.print("Send data to ");
		Serial.print(ServiceData::Mqtt::Branch);
		Serial.print(": ");
		Serial.println(data);
		client.publish(branch.c_str(), data.c_str());	
	}
};