/* 

  HC-SR04 Basic Demonstration 

  HC-SR04-Basic-Demo.ino 

  Demonstrates functions of HC-SR04 Ultrasonic Range Finder 

  Displays results on Serial Monitor 

 
 

  DroneBot Workshop 2017 

  http://dronebotworkshop.com 

*/ 

 
 

// This uses Serial Monitor to display Range Finder distance readings 

 
 

// Hook up HC-SR04 with Trig to Arduino Pin 10, Echo to Arduino pin 13 

 
 

#define trigPin 10 

#define echoPin 13 

 
 

float duration, distance; 
 
 #include <Adafruit_Sensor.h>  

 
 

#include <DHT.h>  

 
 

#include <DHT_U.h>  

#define DHTPIN 2     // Digital pin connected to the DHT sensor   

 
 

// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --  

 
 

// Pin 15 can work but DHT must be disconnected during program upload.  

 
 
 


//define DHTTYPE    DHT11     // DHT 11  

 
 

#define DHTTYPE    DHT11     // DHT 22 (AM2302)  

 
 

//#define DHTTYPE    DHT21     // DHT 21 (AM2301)  

 
 

  

  

 
 

// See guide for details on sensor wiring and usage:  

 
 

//   https://learn.adafruit.com/dht/overview  

 
 

  

  

 
 

DHT_Unified dht(DHTPIN, DHTTYPE);  

 
 

  

  

 
 

uint32_t delayMS;  
 
 

void setup() { 

 
 

  Serial.begin(9600);  

pinMode(trigPin, OUTPUT); 

  pinMode(echoPin, INPUT); 

 
 

  // Initialize device.  

 
 

  dht.begin();  

 
 

  Serial.println(F("DHTxx Unified Sensor Example"));  

 
 

  // Print temperature sensor details.  

 
 

  sensor_t sensor;  

 
 

  dht.temperature().getSensor(&sensor);  

 
 

  Serial.println(F("------------------------------------"));  

 
 

  Serial.println(F("Temperature Sensor"));  

 
 

  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);  

 
 

  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);  

 
 

  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);  

 
 

  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));  

 
 

  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));  

 
 

  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));  

 
 

  Serial.println(F("------------------------------------"));  

 
 

  // Print humidity sensor details.  

 
 

  dht.humidity().getSensor(&sensor);  

 
 

  Serial.println(F("Humidity Sensor"));  

 
 

  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);  

 
 

  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);  

 
 

  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);  

 
 

  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));  

 
 

  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));  

 
 

  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));  

 
 

  Serial.println(F("------------------------------------"));  

 
 

  // Set delay between sensor readings based on sensor details.  

 
 

  delayMS = sensor.min_delay / 1000;  

 
 

}  

 
 

  




 
 

void loop() { 
  // Delay between measurements.  

 
 

  delay(delayMS);  

 
 

  // Get temperature event and print its value.  

 
 

  sensors_event_t event;  

 
 

  dht.temperature().getEvent(&event);  

 
 

  if (isnan(event.temperature)) {  

 
 

    Serial.println(F("Error reading temperature!"));  

 
 

  }  

 
 

  else {  

 
 

    Serial.print(F("Temperature: "));  

 
 

    Serial.print(event.temperature);  

 
 

    Serial.println(F("°C"));  

 
 

  }  

 
 

  // Get humidity event and print its value.  

 
 

  dht.humidity().getEvent(&event);  

 
 

  if (isnan(event.relative_humidity)) {  

 
 

    Serial.println(F("Error reading humidity!"));  

 
 

  }  

 
 

  else {  

 
 

    Serial.print(F("Humidity: "));  

 
 

    Serial.print(event.relative_humidity);  

 
 

    Serial.println(F("%"));  

 
 

  }  
    

  // Write a pulse to the HC-SR04 Trigger Pin 

   

  digitalWrite(trigPin, LOW); 

  delayMicroseconds(2); 

  digitalWrite(trigPin, HIGH); 

  delayMicroseconds(10); 

  digitalWrite(trigPin, LOW); 

   

  // Measure the response from the HC-SR04 Echo Pin 

  

  duration = pulseIn(echoPin, HIGH); 

   

  // Determine distance from duration 

  // Use 343 metres per second as speed of sound 

   

  distance = (duration / 2) * 0.0343; 

   

  // Send results to Serial Monitor 

 
 

  Serial.print("Distance = "); 

  if (distance >= 400 || distance <= 2) { 

     Serial.println("Out of range"); 

  } 

  else { 

    Serial.print(distance); 

    Serial.println(" cm"); 

    delay(500); 

  } 

  delay(500); 

} 