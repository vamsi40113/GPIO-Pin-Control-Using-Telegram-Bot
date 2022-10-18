#include "CTBot.h"
CTBot myBot;

String ssid = "S1";     // REPLACE mySSID WITH YOUR WIFI SSID
String pass = "1234554321"; // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
String token = "5332764725:AAFLO9HAYZ54QBJoUG0SrRREoqZIAe3uCHM";   // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN
uint8_t led = 2;            // the onboard ESP8266 LED.    
                            // If you have a NodeMCU you can use the BUILTIN_LED pin
                            // (replace 2 with BUILTIN_LED)              

void setup() {
  // initialize the Serial
  Serial.begin(115200);
  Serial.println("Starting TelegramBot...");

  // connect the ESP8266 to the desired access point
  myBot.wifiConnect(ssid, pass);

  // set the telegram bot token
  myBot.setTelegramToken(token);

  // check if all things are ok
  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");

  // set the pin connected to the LED to act as output pin
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH); // turn off the led (inverted logic!)

}

void loop() {
  // a variable to store telegram message data
  TBMessage msg;

  // if there is an incoming message...
  if (myBot.getNewMessage(msg)) {

    if (msg.text.equalsIgnoreCase("ON")) {              // if the received message is "LIGHT ON"...
      digitalWrite(led, HIGH);                               // turn on the LED (inverted logic!)
      myBot.sendMessage(msg.sender.id, "Light is now ON");  // notify the sender
    }
    else if (msg.text.equalsIgnoreCase("OFF")) {        // if the received message is "LIGHT OFF"...
      digitalWrite(led, LOW);                              // turn off the led (inverted logic!)
      myBot.sendMessage(msg.sender.id, "Light is now OFF"); // notify the sender
    }
    else {                                                    // otherwise...
      // generate the message for the sender
      String reply;
      reply = (String)"Welcome " + msg.sender.username + (String)". Message ON to turn on & OFF to turn off the Led .";
      myBot.sendMessage(msg.sender.id, reply);             // and send it
    }
  }
  // wait 500 milliseconds
  delay(500);
}
