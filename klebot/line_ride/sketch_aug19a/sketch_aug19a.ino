//                   БИБЛИОТЕКИ:
#include             <iarduino_HC_SR04_int.h>                       // подключаем библиотеку для работы с датчиком
//                   НОМЕРА ВЫВОДОВ:
const uint8_t        pinSensorL1   = A1;                             // Вывод к которому подключен датчик находящийся слева         (по направлению движения)
const uint8_t        pinSensorL2   = A2;                             // Вывод к которому подключен датчик находящийся слева         (по направлению движения)
const uint8_t        pinSensorC   = A3;                             // Вывод к которому подключен датчик находящийся по центру     (по направлению движения)
const uint8_t        pinSensorR1   = A4;                             // Вывод к которому подключен датчик находящийся справа        (по направлению движения)
const uint8_t        pinSensorR2   = A5;                             // Вывод к которому подключен датчик находящийся справа        (по направлению движения)


const uint16_t       valSensor1   = 48;                            // Показание датчика находящегося на линии                     (указывается для конкретной трассы)
const uint16_t       valSensor0   = 209;                            // Показание датчика находящегося вне линии                    (указывается для конкретной трассы)
const uint8_t        valSpeed     = 255;                            // Максимальная скорость                                       (число от 1 до 255)
const uint32_t       tmrDelay     = 2000;                           // Время в течении которого требуется остановиться             (если в течении этого времени состояние остаётся неопределённым (линия не обнаружена), то требуется остановиться)
const uint8_t        valTurning   = 10;                             // Крутизна поворотов (скорость реакции)                       (число от 1 до 255)
const uint8_t        valDistance  = 10;                             // Минимально допустимое расстояние до объекта в сантиметрах   (если расстояние будет меньше, то требуется остановитьтся)



// Объявляем переменные для хранения состояния двух моторов 
int motor_L1, motor_L2, input_L; 
int motor_Rl, motor_R2, input_R; 


//                   РАССЧИТЫВАЕМЫЕ ЗНАЧЕНИЯ:
      uint8_t        arrSpeed[2];                                   // Рассчитываемая скорость для каждого мотора                  (число от 1 до valSpeed, нулевой элемент - правый мотор, первый элемент - левый мотор)
      uint16_t       valSensorM;                                    // Рассчитываемое среднее значение датчика                     (значение между цветом линии и цветом вне линии)
      uint8_t        valSensor;                                     // Биты рассчитываемых логических уровней всех датчиков        (0bxxxxxLCR)
      bool           flgLine;                                       // Флаг указывающий на то, что используется светлая линия      (0 - тёмная линия, 1 - светлая линия)
      int8_t         flgTurning;                                    // Флаг наличия и направления поворота                         (0 - не поворачиваем, -1 - поворачиваем налево, +1 - поворачиваем направо)
      bool           flgPWM;                                        // Флаг указывающий на то, что требуется изменить ШИМ моторов  (0 - тёмная линия, 1 - светлая линия)
      bool           flgStop;                                       // Флаг указывающий на необходимость остановиться              (0 - без остановки, 1 - требуется остановиться)
      bool           flgDistance;                                   // Флаг обнаружения препятствия                                (0 - не обнаружено, 1 - обнаружено)
      uint32_t       tmrMillis;                                     // Время совершения последней операции                         (в миллисекундах)


 
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


void setup() {
  // put your setup code here, to run once:
    setspeed(55,55);
    setup_motor_system(9, 8, 11, 5, 4, 7); 
  
}

void loop() {
  // put your main code here, to run repeatedly:

  forward();
  delay(2000);
  forward_left();
  delay(2000);
  forward();
  delay(2000);
  forward_right();
  delay(2000);
}
