// Line Ride - езда вдоль линии
// 1. Объявление констант: показания датчиков, пины входов/выходов
// библиотеки для работы с датчиком линии и датчиком расстояния
// переменные, для использования в программе
#include <iarduino_HC_SR04_int.h>

const uint8_t pinSensorL1 = 1;
const uint8_t pinSensorL2 = 2;
const uint8_t pinSensorC =3;
const uint8_t pinSensorR1 = 4;
const uint8_t pinSensorR2 = 5;
const uint8_t LE = 6;
const uint8_t LH = 7;
const uint8_t RE = 8;
const uint8_t RH = 9;
const uint8_t pinSens_TRIG = 10;
const uint8_t pinSens_ECHO = 11;

iarduino_HC_SR04_int hcsr(pinSens_TRIG, pinSens_ECHO);              // Объект hcsr для работы с библиотекой iarduino_HC_SR04       (вывод TRIG, вывод ECHO)

const uint16_t speed = 255;

uint16_t valSensorM;
uint16_t valSensorLM;
uint16_t valSensorRM;
uint16_t valSensorC;

// Функция инициализации управления моторами. 
void setup_motor_system(int L1, int L2, int iL, int Rl, int R2, int iR) 
{ 
  // Заносятся в переменные номера контактов (пинов) Arduino. 
  motor_L1=L1; 
  motor_L2=L2;
  input_L=iL; 
  
  // Для левых и правых моторов робота. 
  motor_Rl=Rl; motor_R2=R2; input_R=iR; 
  
  // Переводятся указанные порты в состояние вывода данных. 
  pinMode(motor_L1, OUTPUT); 
  pinMode(motor_L2, OUTPUT); 
  pinMode(input_L, OUTPUT); 
  pinMode(motor_Rl, OUTPUT); 
  pinMode(motor_R2, OUTPUT); 
  pinMode(input_R, OUTPUT); 
} 

// Функция задает скорость двигателя, 
void setspeed(int LeftSpeed, int RightSpeed) 
{ 
  // Задает ширину положительного фронта от 0 до 255. 
  analogWrite(input_L, LeftSpeed); 
  analogWrite(input_R, RightSpeed); 
  // Чем больше, тем интенсивнее работает мотор. 
} 

void left_turn(){
  // блокировка вращения левых колес. 
  digitalWrite(motor_L1, LOW); 
  digitalWrite(motor_L2, LOW); 
  // правые колеса вращаются. 
  digitalWrite(motor_Rl, HIGH); 
  digitalWrite(motor_R2, LOW); 
}

void right_turn(){
	// левые колеса вращаются. 
  digitalWrite(motor_L1, HIGH);  
  digitalWrite(motor_L2, LOW); 
  // блокировка вращения правых колес. 
  digitalWrite(motor_Rl, LOW); 
  digitalWrite(motor_R2, LOW); 
}


void forward(){
	// Если двигатель будет работать не в ту сторону, 
  // поменять на нем контакты местами. 
  digitalWrite(motor_L1,HIGH); 
  digitalWrite(motor_L2,LOW); 
  digitalWrite(motor_Rl,HIGH); 
  digitalWrite (motor_R2,LOW) ; 
}


void stop(){
	// левые колеса вращаются. 
  setspeed(0,0)
  digitalWrite(motor_L1, LOW);  
  digitalWrite(motor_L2, LOW); 
  // блокировка вращения правых колес. 
  digitalWrite(motor_Rl, LOW); 
  digitalWrite(motor_R2, LOW); 
}

void setup(){
	// Установка скорости на моторах
	// Установка режима работы выводов и входов
	setup_motor_system(9, 8, 11, 5, 4, 7); 
 
}

void loop(){
	//1. Чтение показателей датчиков и движение в направлении линии
	// 10000 | 11000 Линия слева, поворот налево
	// 00100 | 01110 Линия в центре, ехать прямо
	// 00001 | 00011 Линия справа, ехать направо


}