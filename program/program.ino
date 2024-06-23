#include <DHT.h>

#define FLAME_PIN 6
#define BUZZER_PIN 4
#define RELAY_PIN 7 //waterpump
#define DHTPIN 5
#define DHTTYPE DHT22
#define SPRINKLER_START_DELAY 5000  //5 seconds 
#define SPRINKLER_ON_TIME 3000      //3 seconds Sprinkler on time

DHT dht(DHTPIN, DHTTYPE);

unsigned long previousTime = millis();

//Variables
float hum; //Stores humidity value
float temp; //Stores temperature value

void setup() 
{
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(FLAME_PIN, INPUT); 
  pinMode(BUZZER_PIN, OUTPUT);   
  dht.begin();
}

void loop() 
{
  //Read data and store it to variable humidity and temperature
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  //Print temp and hum values to serial monitor
  Serial.print("Humidity : ");
  Serial.print(hum);
  Serial.println(" %");
  Serial.print("Temperature : ");
  Serial.print(temp);
  Serial.println(" Celcius");
  delay(2000);

  //If there is fire then the sensor value will be LOW else the value will be HIGH
  int sensorValue = digitalRead(FLAME_PIN);

  //There is fire
  if (sensorValue == LOW)
  {
    analogWrite(BUZZER_PIN, 50);                          //Turn on buzzer

    if (millis() - previousTime > SPRINKLER_START_DELAY)  //We will wait for few seconds before sprinkler can be started once fire is detected.
    {
      digitalWrite(RELAY_PIN, LOW);                       //Relay is low level triggered relay so we need to write LOW to switch on the light 
      delay(SPRINKLER_ON_TIME);                           //Keep sprinkler on for sometime.
    }
  }
  else
  {
    analogWrite(BUZZER_PIN, 0);    
    digitalWrite(RELAY_PIN, HIGH); 
    previousTime = millis();  
  }
  

}
