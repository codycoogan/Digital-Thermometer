#include <map>

#define tempPin A0 //the thermistor attach to 

#define D3 1
#define D4 13
#define A 5
#define F 4
#define B 2
#define E 14
#define D 12
#define C 0
#define G 16

int currDisp = 0;

int onOff;
double tempReading;
double tempK;
float tempC;
float tempF;

uint8_t val;
uint8_t readsCount = 0;

std::map<int, uint8_t> numberVals = {
  {1, 0x28},
  {2, 0x75},
  {3, 0x79},
  {4, 0x2B},
  {5, 0x5B},
  {6, 0x5F},
  {7, 0x68},
  {8, 0xFF},
  {9, 0x6B},
  {0, 0x7E},

};

void setup() {

  Serial.begin(9600);
  pinMode(D3, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(G, OUTPUT);

  // reset seven segment
  turnOffDisplays();
}


void turnOffDisplays() {
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);

  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void showTemp(int temp) {

  if (currDisp == 0) {
    // tens place
    val = numberVals[temp / 10];
  }
  else {
    // ones place
    val = numberVals[temp % 10];
  }

  turnOffDisplays();

  for (int i = 1; i < 8; i++) {
    onOff = val & (0x80 >> i);
    switch (i) {
      case 1:
        if (onOff)
          digitalWrite(A, HIGH);
        else
          digitalWrite(A, LOW);
        break;
      case 2:
        if (onOff)
          digitalWrite(B, HIGH);
        else
          digitalWrite(B, LOW);
        break;
      case 3:
        if (onOff)
          digitalWrite(C, HIGH);
        else
          digitalWrite(C, LOW);
        break;
      case 4:
        if (onOff)
          digitalWrite(D, HIGH);
        else
          digitalWrite(D, LOW);
        break;
      case 5:
        if (onOff)
          digitalWrite(E, HIGH);
        else
          digitalWrite(E, LOW);
        break;

      case 6:
        if (onOff)
          digitalWrite(F, HIGH);
        else
          digitalWrite(F, LOW);
        break;
      case 7:
        if (onOff)
          digitalWrite(G, HIGH);
        else
          digitalWrite(G, LOW);
        break;
    }
  }

  if (currDisp == 0) {
    // show ones place
    digitalWrite(D4, LOW);
    currDisp = 1;
  }
  else {
    digitalWrite(D3, LOW);
    currDisp = 0;
  }
}

void loop() {

  if (readsCount % 200 == 0) {

    // Reading conversion from manufacturer
    tempReading = analogRead(tempPin);

    tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
    tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
    tempC = tempK - 273.15;            // Convert Kelvin to Celcius
    tempF = (tempC * 9.0) / 5.0 + 32.0; // Convert Celcius to Fahrenheit
  }

  //  Serial.print("TempC: ");
  //  Serial.print(tempC);
  //  Serial.print("  C");
  //
  //  Serial.println();
  //
  //  Serial.print("TempF: ");
  //  Serial.print(tempF);
  //  Serial.print("  F");


  showTemp(tempF);
  delay(7);
  readsCount++;

}
