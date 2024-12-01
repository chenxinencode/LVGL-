#include"humtem.h"
float temperature;
float humidity;
AHT20 humiditySensor;
void humtem_setup()
{
  Wire.begin(SDAPin,SCLPin); 

  if (humiditySensor.begin() == false)
  {
      Serial.println("AHT20 not detected. Please check wiring. Freezing.");
      while (1);
  }
  Serial.println("AHT20 acknowledged.");
}

void humtem_loop()
{
  
  temperature = humiditySensor.getTemperature();
  humidity = humiditySensor.getHumidity();
  //If a new measurement is available
  // if (humiditySensor.available() == true)
  // {
  //     //Get the new temperature and humidity value
  //   float temperature = humiditySensor.getTemperature();
  //   float humidity = humiditySensor.getHumidity();
  //       //Print the results
  //   Serial.print("Temperature: ");
  //   Serial.print(temperature, 2);
  //   Serial.print(" C\t");
  //   Serial.print("Humidity: ");
  //   Serial.print(humidity, 2);
  //   Serial.print("% RH");
  //   Serial.println();
  // }
  // delay(2000);
}