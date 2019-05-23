#define VCC 3.3
#define VOLTAGE_DIVIDER_PIN 34

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  analogReadResolution(13);
  pinMode(VOLTAGE_DIVIDER_PIN, INPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  float voltage = map(analogRead(VOLTAGE_DIVIDER_PIN), 0, 8192, 0, int(VCC*1000))/1000.;
  Serial.println(voltage);
  delay(100);
}
