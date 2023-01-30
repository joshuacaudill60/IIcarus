#define PIN_SPEC1_VIDEO           A0
#define PIN_SPEC1_START           A1
#define PIN_SPEC1_CLK             5
uint16_t data_1[288];
uint8_t num;

void readSpectrometer(uint8_t SPEC_ST, uint8_t SPEC_CLK, uint8_t SPEC_VIDEO, uint16_t *data)
{ // This is from the spec sheet of the spectrometer
    int delayTime = .5; // delay time

    // Start clock cycle and set start pulse to signal start
    digitalWrite(SPEC_CLK, LOW);
    delayMicroseconds(delayTime);
    digitalWrite(SPEC_CLK, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(SPEC_CLK, LOW);
    digitalWrite(SPEC_ST, HIGH);
    delayMicroseconds(delayTime);

    // Sample for a period of time
    for (int i = 0; i < 7; i++)
    {
        digitalWrite(SPEC_CLK, HIGH);
        delayMicroseconds(delayTime);
        digitalWrite(SPEC_CLK, LOW);
        delayMicroseconds(delayTime);
    }

    // Set SPEC_ST to low
    digitalWrite(SPEC_ST, LOW);

    // Sample for a period of time
    for (int i = 0; i < 87; i++)
    {
        digitalWrite(SPEC_CLK, HIGH);
        delayMicroseconds(delayTime);
        digitalWrite(SPEC_CLK, LOW);
        delayMicroseconds(delayTime);
    }

    // Read from SPEC_VIDEO
    for (int i = 0; i < 288; i++)
    {
        data[i] = analogRead(SPEC_VIDEO);
        digitalWrite(SPEC_CLK, HIGH);
        delayMicroseconds(delayTime);
        digitalWrite(SPEC_CLK, LOW);
        delayMicroseconds(delayTime);
        
    }

    // Set SPEC_ST to high
    //digitalWrite(SPEC_ST, HIGH);

//    // Sample for a small amount of time
//    for (int i = 0; i < 7; i++)
//    {
//        digitalWrite(SPEC_CLK, HIGH);
//        delayMicroseconds(delayTime);
//        digitalWrite(SPEC_CLK, LOW);
//        delayMicroseconds(delayTime);
//    }
    digitalWrite(SPEC_CLK, HIGH);
    delayMicroseconds(delayTime);
}

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  pinMode(PIN_SPEC1_VIDEO, INPUT);
  pinMode(PIN_SPEC1_CLK, OUTPUT);
  pinMode(PIN_SPEC1_START, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  readSpectrometer(PIN_SPEC1_START, PIN_SPEC1_CLK, PIN_SPEC1_VIDEO, data_1);
 for(int i = 0; i < 288; i++) {
  num = (char)data_1[i];
  Serial1.print(num);
  if(i != 287) {
   Serial1.print(", ");
  }
 }
 Serial1.print('\n');
 delay(1000);
}
