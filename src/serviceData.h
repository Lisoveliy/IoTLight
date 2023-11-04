#include <Arduino.h>
#pragma once

namespace ServiceData
{
	const String SSID = "IoT-1986";
	const String Password = "12345678";
	namespace Mqtt{
		const String Server = "homeassistant.local";
		const short Port = 1883;
		const String User = "esp8266dev";
		const String Password = "12345678"; 
		const String Branch = "esp8266light/state";
	}
	namespace Commands
	{
		const String Branch = "esp8266light/state/set";
		const String On = "ON";
		const String Off = "OFF";
	}
};
