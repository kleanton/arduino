#define SENSOR_PIN0 0
#define SENSOR_PIN1 1
#define SENSOR_PIN2 2
#define SENSOR_PIN3 3
#define SENSOR_PIN4 4

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  int analogValue1 = analogRead(SENSOR_PIN0);
  int analogValue2 = analogRead(SENSOR_PIN1);
  int analogValue3 = analogRead(SENSOR_PIN2);
  int analogValue4 = analogRead(SENSOR_PIN3);
  int analogValue5 = analogRead(SENSOR_PIN4);
  
  Serial.println(analogValue1);
  Serial.println(analogValue2);
  Serial.println(analogValue3);
  Serial.println(analogValue4);
  Serial.println(analogValue5);

}

void loop() {
  // put your main code here, to run repeatedly:

    }
 

