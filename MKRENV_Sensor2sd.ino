#include <Arduino_MKRENV.h>
#include <SD.h>
#include <SPI.h>

//File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
 // myFile = SD.open("data.txt", FILE_WRITE);

  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV Shield!");
    while (1);
  }
}

void loop() {
  // Read all the sensor values
  float temperature = ENV.readTemperature();
  float humidity    = ENV.readHumidity();
  float pressure    = ENV.readPressure();
  float illuminance = ENV.readIlluminance();
  float uva         = ENV.readUVA();
  float uvb         = ENV.readUVB();
  float uvIndex     = ENV.readUVIndex();

  // Save the sensor values to an SD card
  SD_saveData(temperature, humidity, pressure, illuminance, uva, uvb, uvIndex);

  // Print each of the sensor values
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity    = ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Pressure    = ");
  Serial.print(pressure);
  Serial.println(" kPa");

  Serial.print("Illuminance = ");
  Serial.print(illuminance);
  Serial.println(" lx");

  Serial.print("UVA         = ");
  Serial.println(uva);

  Serial.print("UVB         = ");
  Serial.println(uvb);

  Serial.print("UV Index    = ");
  Serial.println(uvIndex);

  // Print an empty line
  Serial.println();

  // Wait 1 second to print again
  delay(1000);
}

// Function to save data to an SD card
void SD_saveData(float temperature, float humidity, float pressure, float illuminance, float uva, float uvb, float uvIndex) {
  // Open a file on the SD card
  File dataFile = SD.open("data.csv", FILE_WRITE);

  // If the file couldn't be opened, print an error message
  if (!dataFile) {
    Serial.println("Error opening data file!");
    return;
  }

  // Write the sensor values to the file
  dataFile.print(temperature);
  dataFile.print(",");
  dataFile.print(humidity);
  dataFile.print(",");
  dataFile.print(pressure);
  dataFile.print(",");
  dataFile.print(illuminance);
  dataFile.print(",");
  dataFile.print(uva);
  dataFile.print(",");
  dataFile.print(uvb);
  dataFile.print(",");
  dataFile.print(uvIndex);
  dataFile.println();

  // Close the file
  dataFile.close();
}
