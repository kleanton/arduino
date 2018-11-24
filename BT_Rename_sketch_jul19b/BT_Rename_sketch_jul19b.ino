// Подключаем библиотеку для работы с Serial через дискретные порты 
#include <SoftwareSerial.h> 
// Создаем последовательный порт на пинах 12 и 2 
SoftwareSerial BTSerial(13, 6); // RX, TX 
// Переменная для приема данных по Bluetooth 
char bt_input; 
// Настройка 
void setup () 
{ 
// Устанавливаем скорость передачи данных по Bluetooth 
BTSerial.begin(9600); 
// Переключаем АО в двоичный режим работы, на передачу 
pinMode(14, OUTPUT); 
// Переводим НС-05 в режим АТ-команд 
digitalWrite(14,1); 
// Присваиваем НС-05 новое имя - MaxiBot 
BTSerial.println("AT+NAME=MaxiBot"); 
// Устанавливаем скорость передачи данных по кабелю 
Serial.begin(9600); 
// Переводим НС-05 в нормальный режим работы 
digitalWrite(14, 0); 
} 
void loop() 
{ 
  // Если пришли данные по Bluetooth 
  if (BTSerial.available()) 
  { 
    // Записываем, что пришло по Bluetooth в переменную bt_input 
    bt_input = (char)BTSerial.read(); 
    Serial.println(bt_input); 
  }

}
