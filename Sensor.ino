#include <SoftwareSerial.h>

SoftwareSerial portSensor(10, 18);
SoftwareSerial portSensor2(11, 16);
                         

void setup() 
{
  Serial.begin(115200); // Open serial port to the PC

  portSensor.begin(9600); // Sensor serial baud = 9600
  portSensor2.begin(9600); // Sensor serial baud = 9600
}

byte buffer[13];
unsigned short dist[2];

void loop() 
{
  //delay(10000);
  portSensor.flush();
  portSensor.listen(); // Start listening on sensor port
  delay(200); // Waiting for 2 series of data
  if(portSensor.available() >= 13)
  {
    for (int i = 0; i < 13; i++)
    { 
      buffer[i] = portSensor.read();
    }
    
    for (int i = 0; i < 12; i++)
    {
      if (buffer[i] == 0x59 && buffer [i+1] == 0x59) // Looking for header data
      {
        dist[1] = (buffer[i+3]<<8) | (buffer[i+2]); // Distance data
        break;
      }
    }
  }
  else
  {
    dist[1] = 10000;
  }
  portSensor2.flush();
  portSensor2.listen();
  delay(200); // Waiting for 2 series of data
  if(portSensor2.available() >= 13)
  {
    for (int i = 0; i < 13; i++)
    { 
      buffer[i] = portSensor2.read();
    }
    
    for (int i = 0; i < 12; i++)
    {
      if (buffer[i] == 0x59 && buffer [i+1] == 0x59) // Looking for header data
      {
        dist[2] = (buffer[i+3]<<8) | (buffer[i+2]); // Distance data
        break;
      }
    }
  }
  else
  {
    dist[2] = 10000;
  }

  Serial.println(dist[1]); // Print distance in cm
  Serial.println(dist[2]); // Print distance in cm
  
}
