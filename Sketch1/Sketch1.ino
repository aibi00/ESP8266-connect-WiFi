/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */

#include "ESP8266WiFi.h"
 // #include "./config.test.h"

#define KEY_ENTER '\n'

char accessoryName[16] = { 0 };
String ssid;
String password;

void setup() {
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);

	WiFi.mode(WIFI_STA);
	WiFi.disconnect();

	// WiFi scan

	{Serial.println("scan start");

	// WiFi.scanNetworks will return the number of networks found
	int n = WiFi.scanNetworks();
	Serial.println("scan done");
	if (n == 0)
		Serial.println("no networks found");
	else
	{
		Serial.print(n);
		Serial.println(" networks found");
		for (int i = 0; i < n; ++i)
		{

			// Print SSID and RSSI for each network found
			Serial.print(i + 1);
			Serial.print(": ");
			Serial.print(WiFi.SSID(i));
			Serial.print(" (");
			Serial.print(WiFi.RSSI(i));
			Serial.print(")");
			Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
			delay(10);


		}
	}
	Serial.println(""); }

	// choose WiFi

	{

		// enter Name of WiFi
		Serial.print("\n Which WiFi do you want to connect to: ");
		Serial.print("\n Confirm with ENTER\n");

		Serial.read(); // exterminate first random byte

		while (Serial.available() == 0) {
			delay(500);
			Serial.print(".");
		}

		ssid = Serial.readStringUntil(KEY_ENTER);

		Serial.println(ssid);

		// enter password of WiFi
		Serial.print("\n Enter the password: ");
		Serial.print("\n Confirm with ENTER\n");
		
		
		while (Serial.available() == 0) {
			delay(500);
			Serial.print(".");
		}

		password = Serial.readStringUntil(KEY_ENTER);

		Serial.println(password);	
	}


	// setup WiFi
	{
		char SSID[100];
		char PASSWORD[100];

		ssid.toCharArray(SSID, 100);
		password.toCharArray(PASSWORD, 100);

		WiFi.reconnect();
		WiFi.mode(WIFI_STA);
		WiFi.hostname("ESP8266");
		WiFi.begin(SSID, PASSWORD);

		Serial.print("Connecting to ");
		Serial.print(ssid);
		Serial.print("  ");

		while (WiFi.status() != WL_CONNECTED) {
			delay(1000);
			Serial.print(" . ");
		}

		Serial.print(" done! ");

		Serial.print(WiFi.localIP());
	}
}

void loop() {
	if (WiFi.status() == WL_CONNECTED) {
		for (int i = 0; i < 4; i++) {
			digitalWrite(LED_BUILTIN, HIGH);
			delay(250);
			digitalWrite(LED_BUILTIN, LOW);
			delay(1000);
		}
	}

}
