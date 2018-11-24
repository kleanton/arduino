const uint8_t R1=4;
const uint8_t R2=5;
const uint8_t Rspeed_pin=7;

const uint8_t L4=9;
const uint8_t L3=8;
const uint8_t Lspeed_pin=11;
const uint8_t speed_value=25;

void setspeed(int LeftSpeed, int RightSpeed) 
{ 
  // Задает ширину положительного фронта от 0 до 255. 
  digitalWrite(Lspeed_pin, LeftSpeed); 
  digitalWrite(Rspeed_pin, RightSpeed); 
  // Чем больше, тем интенсивнее работает мотор. 
} 

void setup_motor(){
  pinMode(L4,OUTPUT);
  pinMode(L3,OUTPUT);
  pinMode(Lspeed_pin,OUTPUT);
  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
  pinMode(Rspeed_pin,OUTPUT);
}

void setup() {
  // put your setup code here, to run once:
  setup_motor(); //назначили пины на выходы
  stop_all(); // двигатели остановлены
  setspeed(125,125); // двигатели под напряжением
  forward(); // вперед всеми колесами
  delay(1000); 
  stop_all(); 
  delay(1000);
  setspeed(175,175);
  right(); // поворот левыми колесами. Едет вправо
  delay(1000);
  setspeed(255,255);
  left(); // поворот правыми колесами. Едет влево
  delay(3000);
  stop_all();
 
}



void forward() {
  // put your main code here, to run repeatedly:
  digitalWrite(L4,HIGH);
  digitalWrite(L3,LOW);
  digitalWrite(R1,LOW);
  digitalWrite(R2,HIGH);
}



void right() {
  // put your main code here, to run repeatedly:
  digitalWrite(L4,HIGH);
  digitalWrite(L3,LOW);
  digitalWrite(R1,HIGH);
  digitalWrite(R2,LOW);
}


void left() {
  // put your main code here, to run repeatedly:
  digitalWrite(L4,LOW);
  digitalWrite(L3,HIGH);
  digitalWrite(R1,LOW);
  digitalWrite(R2,HIGH);
}
void stop_all(){
 setspeed(0,0);
  }

void loop(){
  
  }
