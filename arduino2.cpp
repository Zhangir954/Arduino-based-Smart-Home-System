LiquidCrystal lcd1(2, 3, 4, 5, 6, 7);
LiquidCrystal lcd2(8, 9, 4, 5, 6, 7);
LiquidCrystal lcd3(10, 11, 4, 5, 6, 7);
LiquidCrystal lcd4(12, 13, 4, 5, 6, 7);

int temperature, lightLevel, gasLevel, soilLevel;

void setup() {
  Wire.begin(8); 
  Wire.onReceive(receiveData);

  lcd1.begin(16, 2);
  lcd2.begin(16, 2);
  lcd3.begin(16, 2);
  lcd4.begin(16, 2);

  lcd1.print("TEMP");
  lcd2.print("LIGHT");
  lcd3.print("GAS");
  lcd4.print("SOIL");
}

void loop() {
  lcd1.setCursor(0, 1);
  lcd1.print(temperature);
  lcd1.print(" C   ");

  lcd2.setCursor(0, 1);
  lcd2.print(lightLevel < 100 ? "Dark   " : "Bright ");

  lcd3.setCursor(0, 1);
  lcd3.print("Gas Lvl:");
  lcd3.print(gasLevel < 150 ? "Okay   " : "Danger ");

  lcd4.setCursor(0, 1);
  lcd4.print(soilLevel < 100 ? "Dry   " : "Wet   ");

  delay(500);
}

void receiveData(int bytes) {
  if (bytes >= 4) {
    temperature = Wire.read();
    lightLevel = Wire.read();
    gasLevel = Wire.read();
    soilLevel = Wire.read();
  }
}