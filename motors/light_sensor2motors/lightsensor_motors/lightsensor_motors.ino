//датчик линии
const uint8_t        pinSensorL1  = A1;                             // Вывод к которому подключен датчик находящийся слева         (по направлению движения)
const uint8_t        pinSensorL2  = A2;   
const uint8_t        pinSensorC   = A3;                             // Вывод к которому подключен датчик находящийся по центру     (по направлению движения)
const uint8_t        pinSensorR1  = A4;                             // Вывод к которому подключен датчик находящийся справа        (по направлению движения)
const uint8_t        pinSensorR2  = A5;   

//двигатели справа
const uint8_t R1=4;
const uint8_t R2=5;
const uint8_t Rspeed_pin=7;

//двигатели слева

const uint8_t L4=9;
const uint8_t L3=8;
const uint8_t Lspeed_pin=11;
const uint8_t speed_value=25;

//константы

const uint16_t       valSensor1   = 130;                            // Показание датчика находящегося на линии                     (указывается для конкретной трассы)
const uint16_t       valSensor0   = 40;                            // Показание датчика находящегося вне линии                    (указывается для конкретной трассы)
const uint8_t        valSpeed     = 255;                            // Максимальная скорость                                       (число от 1 до 255)
const uint32_t       tmrDelay     = 2000;                           // Время в течении которого требуется остановиться             (если в течении этого времени состояние остаётся неопределённым (линия не обнаружена), то требуется остановиться)
const uint8_t        valTurning   = 10;                             // Крутизна поворотов (скорость реакции)                       (число от 1 до 255)
// const uint8_t        valDistance  = 10;                             // Минимально допустимое расстояние до объекта в сантиметрах   (если расстояние будет меньше, то требуется остановитьтся)
// const bool           arrRoute[2]  = {1,1};                          // Направление движения для каждого мотора                     (зависит от полярности,  нулевой элемент - правый мотор, первый элемент - левый мотор)




//рассчитываемые значения

uint16_t Sensor_M;

uint16_t Sensor_LM;

uint16_t Sensor_RM;

uint16_t Sensor_C;

      uint8_t        arrSpeed[2];                                   // Рассчитываемая скорость для каждого мотора                  (число от 1 до valSpeed, нулевой элемент - правый мотор, первый элемент - левый мотор)
      uint16_t       valSensorM;                                    // Рассчитываемое среднее значение датчика                     (значение между цветом линии и цветом вне линии)
      uint8_t        valSensor;                                     // Биты рассчитываемых логических уровней всех датчиков        (0bxxxxxLCR)
      bool           flgLine;                                       // Флаг указывающий на то, что используется светлая линия      (0 - тёмная линия, 1 - светлая линия)
      int8_t         flgTurning;                                    // Флаг наличия и направления поворота                         (0 - не поворачиваем, -1 - поворачиваем налево, +1 - поворачиваем направо)
      bool           flgPWM;                                        // Флаг указывающий на то, что требуется изменить ШИМ моторов  (0 - тёмная линия, 1 - светлая линия)
      bool           flgStop;                                       // Флаг указывающий на необходимость остановиться              (0 - без остановки, 1 - требуется остановиться)
  //    bool           flgDistance;                                   // Флаг обнаружения препятствия                                (0 - не обнаружено, 1 - обнаружено)
      uint32_t       tmrMillis;                                     // Время совершения последней операции                         (в миллисекундах)



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

void setup_line_sensor(){
  pinMode(pinSensorL1,INPUT);
  pinMode(pinSensorL2,INPUT);
  pinMode(pinSensorC,INPUT);
  pinMode(pinSensorR1,INPUT);
  pinMode(pinSensorR2,INPUT);
}

void setup() {
  // put your setup code here, to run once:
  setup_line_sensor();
  setup_motor(); //назначили пины на выходы
  stop_all(); // двигатели остановлены
 
 ///////////////////////////////////////////////

//  Узнаём цвет линии используемой на трассе, если он светлый, то устанавливаем флаг lineColor тёмный
analogRead(pinSensorC);
    flgLine = (valSensor0<valSensor1);                              // Если условие (valSensor0>valSensor1) выполняется значит линия светлая и флаг flgLine установится в 1, иначе он сбросится в 0
//  Вычисляем среднее значение между показаниями датчиков на линии и все линии
    if(flgLine){valSensorM=valSensor1+(valSensor0-valSensor1)/2;}   // Если на трассе используется светлая линия
    else       {valSensorM=valSensor0+(valSensor1-valSensor0)/2;}   // Если на трассе используется тёмная линия
//  Устанавливаем значение скорости обоих моторов
    arrSpeed[1]=valSpeed;                                           // Максимальная скорость на левом моторе
    arrSpeed[0]=valSpeed;                                           // Максимальная скорость на правом моторе
//  Устанавливаем флаг ШИМ, сбрасываем флаг наличия поворота, флаг остановки и флаг обнаружения припятствий
    flgPWM=1; flgTurning=0; flgStop=0; // flgDistance=0;
        
 //  Выводим показания центрального датчика линии
    Serial.begin(9600); while(!Serial){}                            // Инициируем передачу данных по последовательному порту       (на скорости 9600 бит/сек)
    Serial.println(analogRead(pinSensorC));                         // Выводим показания центрального датчика линии                (для указания значений константам valSensor0 и valSensor1)
    Serial.println(flgLine);
//  Устанавливаем задержку и обновляем время совершения последней операции
    delay(2000);
    tmrMillis = millis();


 ///////////////////////////////////////////////
}



void forward() {
  // put your main code here, to run repeatedly:
  digitalWrite(L4,HIGH);
  digitalWrite(L3,LOW);
  digitalWrite(R1,LOW);
  digitalWrite(R2,HIGH);
}


void backward() {
  // put your main code here, to run repeatedly:
  digitalWrite(L4,LOW);
  digitalWrite(L3,HIGH);
  digitalWrite(R1,HIGH);
  digitalWrite(R2,LOW);
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
