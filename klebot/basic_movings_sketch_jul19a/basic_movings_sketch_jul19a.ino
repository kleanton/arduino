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

  
  if (BTSerial.available())
    {
      bt_input = char();
      Serial.println(bt_input, HEX);
      BTSerial.read();
      Serial.println(bt_input);
      switch(bt_input) {
      // Вперед
      case 'F':
        forward();
        break;

      // Назад
        case 'B':
        backward();
        break;
      // Влево
        case 'L':
        left();
        break;
      // Вправо
        case 'R':
        right();
        break;
      // Прямо и влево
        case 'G':
        forward_left();
        break;
      // Прямо и вправо
        case 'I':
        forward_right();
        break;
      // Назад и влево
        case 'H':
        backward_left();
        break;
      // Назад и вправо
        case 'J':
        backward_right();
        break;
      // Стоп
        case 'S':
          _stop();
          break;
      // Скорость 0
case '0':
setspeed(0, 0); 
break; 

      // Скорость 10%
        case '1':
        setspeed(25, 25); 
        break; 

      // Скорость 20%
        case '2':
        setspeed(50, 50); 
        break; 
      // Скорость 30%
        case '3':
        setspeed(75, 75); 
        break;
      // Скорость 50%
        case '4':
        setspeed(100, 100); 
        break;

        
        case '5':
        setspeed(125, 125); 
        break;
      // Скорость 60%
      
        case '6':
        setspeed(150, 150); 
        break;
      // Скорость 60%
       case '7':
        setspeed(175, 175); 
        break;
      // Скорость 70%

      
      // Скорость 80%
       case '8':
        setspeed(200, 200); 
        break;
      // Скорость 90%
        case '9':
        setspeed(225, 225); 
        break;
      // Скорость 100%
      
        case 'q':
        setspeed(255, 255); 
        break;
        

        case 'X':
        //switch_rejim = 1;  
        break;

        
        case 'x':
        //switch_rejim = 0; 
        break;

        
        case 'D':
        _stop(); 
        break;
        
        }
      }
      }

 // ===================================================
 // ==================================================
 // Пример движения робота задан жестко в программе 
 //и повторяется в цикле. 
 // setspeed(255, 255); // устанавливает макс, скорость колес, 
 // forward(); // едет вперед 1 секунду. 
 // delay(1000);
 // forward_left(); // поворачивает налево 0,5 секунд, 
 // delay(500); 
 // forward(); // едет вперед 0,5 секунд, 
 // delay(500); 
 // forward_right(); // поворачивает направо 0,5 секунд, 
 // delay(500); 
 // _stop(); 
 // delay(500); 
 // backward(); // движется назад 0,8 секунд, 
 // delay(800); 
 // =======================================================
 // =======================================================




