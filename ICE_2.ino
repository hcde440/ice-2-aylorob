#include <AdafruitIO.h>
#include <ArduinoHttpClient.h>

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"0

/************************ Example Starts Here *******************************/

// digital pin
#define BUTTON_PIN A0

// Resistor state
int light = 0;
int last = -1;

// set up the 'digital' feed
AdafruitIO_Feed *analog = io.feed("range");

void setup() {

  // set button pin as an input
  //pinMode(BUTTON_PIN, INPUT_PULLUP);

  // start the serial connection
  Serial.begin(115200);
  Serial.print("This board is running: ");
  Serial.println(F(__FILE__));
  Serial.print("Compiled: ");
  Serial.println(F(__DATE__ " " __TIME__));
   
  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.println(io.statusText());
    delay(500);
  }

  // we are connected
  Serial.println("IT IS DONE");
  Serial.println(io.statusText());

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  
  io.run();
  
  //Serial.println("beginning of loop");
  // grab the current state of the button.
  // we have to flip the logic because we are
  // using a pullup resistor.
  
  light = analogRead(BUTTON_PIN);
  if (light == last) {
    return;
  }


  // save the current state to the 'digital' feed on adafruit io
  Serial.print("sending button -> ");
  Serial.println(light);
  analog->save(light);

  // store last button state
  last = light;

}
