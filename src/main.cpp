//I, Aniket Chopra, student number 000814313, certify that this material is my original work. No other person's work has been used without due acknowledgment and I have not made my work available to anyone else.


// ****************************************************************** 
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program 
// COMP-10184 
// Mohawk College 
 
// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 
 
DeviceAddress sensorsAddress;

// To Convert the address of sensor into a valid address
void showAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
  }
}

void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 

int noOfDevices = DS18B20.getDeviceCount();
  for(int i=0;i<noOfDevices; i++) {
    // Fetch the address from the wire
    if(DS18B20.getAddress(sensorsAddress, i)){
      Serial.println(""); 
      Serial.println("Temperature Application"); 
      Serial.print("Found DS18B20 sensor address with: ");
      showAddress(sensorsAddress);
      Serial.println(" ");
    }
    // Error statement when no address is found
    else{
      Serial.println(""); 
      Serial.println("Temperature Application"); 
      Serial.println("NO DS18B20 sensors are installed");
    }
  }

} 
 
void loop() { 
  float fTemp; 
  String judgement;
  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures(); 
 
  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  fTemp = DS18B20.getTempCByIndex(0); 
 
  if(fTemp > 0){
    if(fTemp<10){
        judgement = "Cold!";
    }
    else if(fTemp <15){
      judgement = "Cool";

    }
    else if(fTemp<25){
      judgement = "Perfect";
    }
    else if(fTemp<30){
      judgement = "Warm";
    }
    else if(fTemp<35){
      judgement = "Hot";
    }
    else{
      judgement = "Too Hot!";
    }
  // print the temp to the USB serial monitor 
  Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or "+judgement); 
  }
  else{
    Serial.println(""); 
    Serial.println("Temperature Application");
    Serial.println("No DS18B20 sensors are installed");
  }
  // wait 5s (5000ms) before doing this again 
  delay(5000); 
} 