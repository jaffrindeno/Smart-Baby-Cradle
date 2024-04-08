#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

#define BLYNK_TEMPLATE_ID "TMPL3rUgefeVN"
#define BLYNK_TEMPLATE_NAME "baby cradle"
#define BLYNK_AUTH_TOKEN "wauXkl66JRwzeMUa5Kft_4q26su4lmuy"

#define MOISTURE_SENSOR_PIN 39
#define LED_PIN 2

char auth[] = "wauXkl66JRwzeMUa5Kft_4q26su4lmuy";
char ssid[] = "Redmi Note 10 Lite";
char pass[] = "12341234";

BlynkTimer timer;

Servo myservo;

int sound_sensor=36;

BLYNK_WRITE(V0) // Blynk virtual pin 1 is connected to a switch button in the Blynk app
{
  int switchState = param.asInt(); // Read the state of the switch button
    Serial.print("Switchstate:");
    Serial.println(switchState);

    if(switchState==1){    
        myservo.write(0);
        delay(10);    
    }
    else{
      myservo.write(90);
      Serial.println("Stopped");
      delay(10);
    }
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(sound_sensor,INPUT);
  myservo.attach(5);
  
  myservo.write(90);
  timer.setInterval(100L, soundSensor);
  timer.setInterval(100L, readMoistureSensor);
  
}

void loop() {
  Blynk.run();
  delay(10);
  soundSensor();
  readMoistureSensor();
  delay(10);
  

}

void soundSensor()
{
  // Request temperature to all devices on the data line
  int sound_value=analogRead(sound_sensor);
  Serial.print("Sound sensor data: ");
  Serial.println(sound_value);
  Blynk.virtualWrite(V2, sound_value);
  if (sound_value > 500) { 
    
    Blynk.logEvent("sound");
    myservo.write(0);
    delay(10000);
    myservo.write(90);
  } else { // otherwise, turn off the LED
    digitalWrite(LED_PIN, LOW);
  }
  delay(10);
  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    //Blynk.virtualWrite(V0, sound_value);
    //delay(500);
}
void readMoistureSensor() {
  int moistureValue = analogRead(MOISTURE_SENSOR_PIN); // read the analog value from the moisture sensor
  Serial.print("Moisture value: ");
  Serial.println(moistureValue);
  Blynk.virtualWrite(V1, moistureValue);
  if (moistureValue < 3000) { // if the moisture value is less than 500, turn on the LED
    digitalWrite(LED_PIN, HIGH);
    Blynk.logEvent("humidity");
  } else { // otherwise, turn off the LED
    digitalWrite(LED_PIN, LOW);
  }
  delay(10); // wait for 1 second
}
