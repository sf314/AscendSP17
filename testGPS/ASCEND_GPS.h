
#include <Arduino.h>
#include "SoftwareSerial.h"

SoftwareSerial gpsSerial(9, 8); // RX, TX (TX not used)
const int sentenceSize = 50;
char sentence[sentenceSize];

void GPS_begin() {
    Serial.println("GPS: initializing");
    gpsSerial.begin(9600);
    Serial.println("GPS: initialized!");
}


void getField(char* buffer, int index) {
  int sentencePos = 0;
  int fieldPos = 0;
  int commaCount = 0;
  while (sentencePos < sentenceSize)
  {
    if (sentence[sentencePos] == ',')
    {
      commaCount ++;
      sentencePos ++;
    }
    if (commaCount == index)
    {
      buffer[fieldPos] = sentence[sentencePos];
      fieldPos ++;
    }
    sentencePos ++;
  }
  buffer[fieldPos] = '\0';
}



String GPS_getSentence() {
    Serial.println("GPS: gettingSentence");
    static int i = 0;

    if (gpsSerial.available()) {
        char ch = gpsSerial.read();

        while (ch != '\n' && i < sentenceSize) {
            sentence[i] = ch;
            //Serial.println("Hey1");
            ch = gpsSerial.read();
            //Serial.println("Hey2");
            i++;
        }

        sentence[i] = '\0';
        i = 0;
        //displayGPS();
    }
    // else {
    //     Serial.println("Nuthin");
    // }

    char field[20];
    getField(field, 0);

    if (strcmp(field, "$GPRMC") == 0) {

    } else { // Else fill with rubbish
        for (int i = 0; i < 80; i++) {
            // fill with rubbish
            sentence[i] = '0';
            if (i % 20 == 0 && i != 0 && i != 80) {
                sentence[i] = ',';
            }
        }
    }

    return (String)sentence;
}
