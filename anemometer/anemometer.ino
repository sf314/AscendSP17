#include "DHT.h"
//#include "DHT_U.h"

//Setup Variables

double x = 0;
double y = 0;
const int sensorPin = A1; //Defines the pin that the anemometer output is connected to
int sensorValue = 0; //Variable stores the value direct from the analog pin
float sensorVoltage = 0; //Variable that stores the voltage (in Volts) from the anemometer being sent to the analog pin
float windSpeed = 0; // Wind speed in meters per second (m/s)

double x2 = 0;
double y2 = 0;
const int sensorPin2 = A0; //Defines the pin that the anemometer output is connected to
int sensorValue2 = 0; //Variable stores the value direct from the analog pin
float sensorVoltage2 = 0; //Variable that stores the voltage (in Volts) from the anemometer being sent to the analog pin
float windSpeed2 = 0; // Wind speed in meters per second (m/s)

float voltageConversionConstant = .004882814; //This constant maps the value provided from the analog read function, which ranges from 0 to 1023, to actual voltage, which ranges from 0V to 5V
int sensorDelay = 2000; //Delay between sensor readings, measured in milliseconds (ms)

//Anemometer Technical Variables
//The following variables correspond to the anemometer sold by Adafruit, but could be modified to fit other anemometers.

float voltageMin = .4; // Mininum output voltage from anemometer in mV.
float windSpeedMin = 0; // Wind speed in meters/sec corresponding to minimum voltage

float voltageMax = 2.0; // Maximum output voltage from anemometer in mV.
float windSpeedMax = 32; // Wind speed in meters/sec corresponding to maximum voltage

#define DHTPIN 2     // what digital pin we're connected to
#define DHTPIN2 3     // what digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

void setup()
{

  Serial.begin(9600);  //Start the serial connection
  Serial.println("DHTxx test!");

  dht.begin();
  dht2.begin();

  Serial.println("DHTxx test 2!");

}

//Anemometer calculations

void loop()
{

  // Wait a few seconds between measurements.


  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);



  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
    }

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h2 = dht2.readHumidity();
  // Read temperature as Celsius (the default)
  float t2 = dht2.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f2 = dht2.readTemperature(true);



  // Check if any reads failed and exit early (to try again).
  if (isnan(h2) || isnan(t2) || isnan(f2)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
sensorValue = analogRead(sensorPin); //Get a value between 0 and 1023 from the analog pin connected to the anemometer

sensorValue2 = analogRead(sensorPin2); //Get a value between 0 and 1023 from the analog pin connected to the anemometer

sensorVoltage = sensorValue * voltageConversionConstant; //Convert sensor value to actual voltage

sensorVoltage2 = sensorValue2 * voltageConversionConstant; //Convert sensor value to actual voltage

  Serial.println("test4");
//Convert voltage value to wind speed using range of max and min voltages and wind speed for the anemometer
if (sensorVoltage <= voltageMin){ windSpeed = 0; //Check if voltage is below minimum value. If so, set wind speed to zero.

}else { windSpeed = ((sensorVoltage - voltageMin)*windSpeedMax/(voltageMax - voltageMin)*2.23694);}

if (sensorVoltage2 <= voltageMin){ windSpeed2 = 0; //Check if voltage is below minimum value. If so, set wind speed to zero.

}else { windSpeed2 = ((sensorVoltage2 - voltageMin)*windSpeedMax/(voltageMax - voltageMin)*2.23694);}

//Max wind speed calculation

x = windSpeed; if (x >= y){
 y = x;
}else {
  y = y;
}

x2 = windSpeed2; if (x2 >= y2){
 y2 = x2;
}else {
  y2 = y2;
}

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");

  // Compute heat index in Fahrenheit (the default)
  float hif2 = dht2.computeHeatIndex(f2, h2);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic2 = dht2.computeHeatIndex(t2, h2, false);

  Serial.print("Humidity2: ");
  Serial.print(h2);
  Serial.print(" %\t2");
  Serial.print("Temperature2: ");
  Serial.print(t2);
  Serial.print(" *C ");
  Serial.print(f2);
  Serial.print(" *F\t2");
  Serial.print("Heat index2: ");
  Serial.print(hic2);
  Serial.print(" *C ");
  Serial.print(hif2);
  Serial.println(" *F");

//Print voltage and windspeed to serial

  Serial.print("Voltage: ");
  Serial.print(sensorVoltage);
  Serial.print("\t");
  Serial.print("Wind speed: ");
  Serial.println(windSpeed);

  Serial.print("Voltage2: ");
  Serial.print(sensorVoltage2);
  Serial.print("\t");
  Serial.print("Wind speed2: ");
  Serial.println(windSpeed2);

 delay(sensorDelay);
 }
