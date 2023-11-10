#include <Arduino.h>
#include <defines.h>
// Use defines.h.example to create your config
#pragma once

namespace ServiceData
{
	const String SSID = WiFiSSID;
	const String Password = WiFiPass;
	namespace Mqtt
	{
		const String Server = ServerIP;
		const short Port = 1883;
		const String User = "esp8266dev";
		const String Password = MQTTPass;
		const String Branch = "esp8266light/state";
	}
	namespace Commands
	{
		const String Branch = "esp8266light/state/set";
		const String On = "ON";
		const String Off = "OFF";
	}
	const String ApSSID = "NodeMCU";	// Enter SSID here
	const String ApPassword = "12345678"; // Enter Password here

	const IPAddress local_ip(192, 168, 1, 1);
	const IPAddress gateway(192, 168, 1, 1);
	const IPAddress subnet(255, 255, 255, 0);
};
