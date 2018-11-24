
int pinI1=8;//define I1 port
int pinI2=9;//define I2 port
int speedpin=11;//define EA(PWM speed regulation)port
void setup()
{
pinMode(pinI1,OUTPUT);//define this port as output
pinMode(pinI2,OUTPUT);
pinMode(speedpin,OUTPUT);
}
void loop()
{ 
analogWrite(speedpin,100);//input a value to set the speed
delay(2000);
digitalWrite(pinI1,LOW);//DC motorrotates clockwise
digitalWrite(pinI2,HIGH);
analogWrite(speedpin,100);
delay(2000);
digitalWrite(pinI1,HIGH);//DC motor rotates anticlockwise
digitalWrite(pinI2,LOW);
analogWrite(speedpin,100);
delay(2000);
digitalWrite(pinI1,HIGH);//DC motor stop rotating
digitalWrite(pinI2,HIGH);
delay(2000);
}
