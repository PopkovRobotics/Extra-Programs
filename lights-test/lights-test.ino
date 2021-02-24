// Программа реализует поочерёдное включение поворотников на 1 секунду.

// Пин arduino, к которому подключён левый поворотник модели
#define LEFT_TURN_SIGNAL        A1
// Пин arduino, к которому подключён правый поворотник модели
#define RIGHT_TURN_SIGNAL       A3//A2

void setup() {
  // Устанавливаем, то что пины, к которым подключены поворотники являются выходом
  // То есть на пины необходимо подавать напряжение
  pinMode(LEFT_TURN_SIGNAL, OUTPUT);
  pinMode(RIGHT_TURN_SIGNAL, OUTPUT);
}

void loop() {
  // Включаем правый поворотник и выключаем левый поворотник
  digitalWrite(LEFT_TURN_SIGNAL, LOW);
  digitalWrite(RIGHT_TURN_SIGNAL, HIGH);
  // Задержка в 1 секунду
  delay(1000);
  // Включаем левый поворотник и выключаем правый поворотник
  digitalWrite(RIGHT_TURN_SIGNAL, LOW);
  digitalWrite(LEFT_TURN_SIGNAL, HIGH);
  // Задержка в 1 секунду
  delay(1000);
}
