#include <SoftwareSerial.h>
SoftwareSerial BTSerial(13,6); //RX, TX
char bt_input;

// Объявляем переменные для хранения состояния двух моторов. 
int motor_L1, motor_L2, input_L; 
int motor_Rl, motor_R2, input_R; 

void setup() 
{ 
  // Переменные - номера контактов (пинов) Arduino. 
  // Для левых и правых моторов машинки. 
  setup_motor_system(9, 8, 11, 5, 4, 7); 
  // Двигатели запущены 
  setspeed(255, 255);  
  BTSerial.begin(9600);
  pinMode(16, OUTPUT);
  Serial.begin(9600);
  digitalWrite(16,0);
} 

// Движение вперед, 
void forward() 
{ 
  // Если двигатель будет работать не в ту сторону, 
  // поменять на нем контакты местами. 
  digitalWrite(motor_L1,HIGH); 
  digitalWrite(motor_L2,LOW); 
  digitalWrite(motor_Rl,HIGH); 
  digitalWrite (motor_R2,LOW) ; 
} 
// Поворот налево с блокировкой левых колес, 
void forward_left() 
{ 
  // блокировка вращения левых колес. 
  digitalWrite(motor_L1, LOW); 
  digitalWrite(motor_L2, LOW); 
  // правые колеса вращаются. 
  digitalWrite(motor_Rl, HIGH); 
  digitalWrite(motor_R2, LOW); 
} 
// Поворот направо с блокировкой правых колес, 
void forward_right() 
{ 
  // левые колеса вращаются. 
  digitalWrite(motor_L1, HIGH);  
  digitalWrite(motor_L2, LOW); 
  // блокировка вращения правых колес. 
  digitalWrite(motor_Rl, LOW); 
  digitalWrite(motor_R2, LOW); 
} 



// Поворот налево с блокировкой левых колес, 
void backward_left() 
{ 
  // блокировка вращения левых колес. 
  digitalWrite(motor_L1, LOW); 
  digitalWrite(motor_L2, LOW); 
  // правые колеса вращаются. 
  digitalWrite(motor_Rl, LOW); 
  digitalWrite(motor_R2, HIGH); 
} 
// Поворот направо с блокировкой правых колес, 
void backward_right() 
{ 
  // левые колеса вращаются. 
  digitalWrite(motor_L1, LOW);  
  digitalWrite(motor_L2, HIGH); 
  // блокировка вращения правых колес. 
  digitalWrite(motor_Rl, LOW); 
  digitalWrite(motor_R2, LOW); 
} 


// Включаем движение назад, 
void backward() 
{ 
// Смена направления вращения двигателей. 
  digitalWrite(motor_L2, HIGH); 
  digitalWrite(motor_L1,LOW); 
  digitalWrite(motor_R2, HIGH); 
  digitalWrite(motor_Rl,LOW); 
}


void left() 
{ 
  // блокировка вращения левых колес. 
  digitalWrite(motor_L1, HIGH); 
  digitalWrite(motor_L2, HIGH); 
  // правые колеса вращаются. 
  digitalWrite(motor_Rl, LOW); 
  digitalWrite(motor_R2, LOW); 
} 
// Поворот направо с блокировкой правых колес, 
void right() 
{ 
  // левые колеса вращаются. 
  digitalWrite(motor_L1, LOW);  
  digitalWrite(motor_L2, LOW); 
  // блокировка вращения правых колес. 
  digitalWrite(motor_Rl, HIGH); 
  digitalWrite(motor_R2, HIGH); 
} 

void _stop() 
{ 
  // Блокировка всех колес. 
  digitalWrite(motor_L2, LOW); 
  digitalWrite(motor_L1,LOW); 
  digitalWrite(motor_R2, LOW); 
  digitalWrite(motor_Rl,LOW); 
}


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

// Основная программа, 
void loop () 
{   
      bt_input = char();
      BTSerial.read();
      Serial.println(bt_input);
      switch(bt_input) {
      // Вперед
      case 'F':
        forward();
       }
     
}



