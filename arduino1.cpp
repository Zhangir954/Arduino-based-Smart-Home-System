const int ldrPin  = A0;
const int soilPin = A1;
const int gasPin  = A2;
const int tempPin = A3;
const int pirPin  = 3;


const int lightbulb = 9;
const int waterLED  = 10;
const int alertLED  = 11;
const int buzzerPin = 12;
const int tempLED   = 8;


const int lightThreshold = 400;
const int soilThreshold  = 500;
const int gasThreshold   = 600;
const float tempMin = 20.0;
const float tempMax = 30.0;

void setup() {
  Wire.begin(); // Master I2C

  pinMode(lightbulb, OUTPUT);
  pinMode(waterLED, OUTPUT);
  pinMode(alertLED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(tempLED, OUTPUT);
  pinMode(pirPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  
  int lightLevel = analogRead(ldrPin);
  int soilLevel  = analogRead(soilPin);
  int gasLevel   = analogRead(gasPin);
  int pirState   = digitalRead(pirPin);

  float voltage = analogRead(tempPin) * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100;

  

  
  if (lightLevel < lightThreshold && pirState == HIGH) {
    digitalWrite(lightbulb, HIGH);
  } else {
    digitalWrite(lightbulb, LOW);
  }


  if (soilLevel < soilThreshold) {
    digitalWrite(waterLED, HIGH);
  } else {
    digitalWrite(waterLED, LOW);
  }


  if (gasLevel > gasThreshold) {
    digitalWrite(alertLED, HIGH);
    tone(buzzerPin, 1000);
  } else {
    digitalWrite(alertLED, LOW);
    noTone(buzzerPin);
  }

  
  if (temperature < tempMin || temperature > tempMax) {
    digitalWrite(tempLED, HIGH);
  } else {
    digitalWrite(tempLED, LOW);
  }

  
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write((int)temperature);      
  Wire.write(lightLevel / 4);         
  Wire.write(gasLevel / 4);          
  Wire.write(soilLevel / 4);          
  Wire.endTransmission();


  Serial.print("Temp: "); Serial.print(temperature);
  Serial.print(" | Light: "); Serial.print(lightLevel);
  Serial.print(" | Gas: "); Serial.print(gasLevel);
  Serial.print(" | Soil: "); Serial.println(soilLevel);

  delay(1000);
}