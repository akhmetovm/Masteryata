#include <LiquidCrystal.h>
#define _key_pin A0

// создание объекта дисплея
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// переменныt времени
unsigned long current_hours = 0;
unsigned long current_minutes = 0;
unsigned long long set_time = 0;

// создаём символы часов
byte full[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

byte up_line[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

byte down_line[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b11111, 
  0b00000,
  0b00000,
  0b11111,
  0b11111
};

byte two_lines[8] = {
  0b11111,
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111
};

byte point[8] = {
  0b00000,
  0b00000,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b00000,
  0b00000
};

// вывод символа
void print_number(int value, int number_position) {
  switch(value) {
    case 0:
      lcd.setCursor(number_position, 0);
      lcd.write(1);
      lcd.write(2);
      lcd.write(1);
      lcd.setCursor(number_position, 1);
      lcd.write(1);
      lcd.write(3);
      lcd.write(1);
      break;
    case 1:
      lcd.setCursor(number_position, 0);
      lcd.write(2);
      lcd.write(1);
      lcd.write(" ");
      lcd.setCursor(number_position, 1);
      lcd.write(3);
      lcd.write(1);
      lcd.write(3);
      break;
    case 2:
      lcd.setCursor(number_position, 0);
      lcd.write(4);
      lcd.write(4);
      lcd.write(1);
      lcd.setCursor(number_position, 1);
      lcd.write(1);
      lcd.write(3);
      lcd.write(3);
      break;
    case 3:
      lcd.setCursor(number_position, 0);
      lcd.write(2);
      lcd.write(4);
      lcd.write(1);
      lcd.setCursor(number_position, 1);
      lcd.write(3);
      lcd.write(4);
      lcd.write(1);
      break;
    case 4:
      lcd.setCursor(number_position, 0);
      lcd.write(1);
      lcd.write(" ");
      lcd.write(1);
      lcd.setCursor(number_position, 1);
      lcd.write(2);
      lcd.write(2);
      lcd.write(1);
      break;
    case 5:
      lcd.setCursor(number_position, 0);
      lcd.write(1);
      lcd.write(4);
      lcd.write(4);
      lcd.setCursor(number_position, 1);
      lcd.write(3);
      lcd.write(3);
      lcd.write(1);
      break;
    case 6:
      lcd.setCursor(number_position, 0);
      lcd.write(1);
      lcd.write(4);
      lcd.write(4);
      lcd.setCursor(number_position, 1);
      lcd.write(1);
      lcd.write(3);
      lcd.write(1);
      break;
    case 7:
      lcd.setCursor(number_position, 0);
      lcd.write(2);
      lcd.write(2);
      lcd.write(1);
      lcd.setCursor(number_position, 1);
      lcd.write(' ');
      lcd.write(2);
      lcd.write(1);
      break;
    case 8:
      lcd.setCursor(number_position, 0);
      lcd.write(1);
      lcd.write(4);
      lcd.write(1);
      lcd.setCursor(number_position, 1);
      lcd.write(1);
      lcd.write(3);
      lcd.write(1);
      //break; 
    case 9:
      lcd.setCursor(number_position, 0);
      lcd.write(1);
      lcd.write(4);
      lcd.write(1);
      lcd.setCursor(number_position, 1);
      lcd.write(3);
      lcd.write(3);
      lcd.write(1);
      break;
  }
}

// печатаем начальный текст
void print_start_text() {
  String txt = "MastIryata 2024";
  bool flag = 1;

  while (flag) {
    //выводим текс из-за экрана
    for (int i = 14; i >= 0; i--) {
      int button = analogRead(_key_pin);
      lcd.setCursor(0, 0);
      for (int k = i; k <= 14; k++) lcd.print(txt[k]);
      delay(400);
      if (button > 700 && button < 800) {flag = 0; break;}
    }
    
    // если не была нажата кнопка
    if (flag != 0) { 
      // просто листаем экран
      for (int i = 15; i >= 0; i--) {
        int button = analogRead(_key_pin);
        button = 750;
        lcd.scrollDisplayRight();
        delay(400);
        if (button > 700 && button < 800) {flag = 0; break;}
      }
    }
    lcd.clear();
  }

  set_time = millis();
}

// выводим время
void print_current_time(int hours, int minutes) {
  print_number(hours%10, 0);
  print_number(hours%10, 4);  
  print_number(minutes/10, 8);
  print_number(minutes%10, 12);
}


// вывод времени с миганием символа
void print_time_blink(int hours, int minutes, int position, bool on) {
  // если символ не горит
  if (on != 1) {
    lcd.setCursor(position*4, 0);
    lcd.write("   ");
    lcd.setCursor(position*4, 1);
    lcd.write("   ");  
  }

  // если это не выбранный символ или он должен гореть
  if (position == 0 && on == 1 || position != 0) print_number(hours/10, 0); 
  if (position == 1 && on == 1 || position != 1) print_number(hours%10, 4);
  lcd.setCursor(7, 0);
  lcd.write(5);
  lcd.setCursor(7, 1);
  lcd.write(5);  
  if (position == 2 && on == 1 || position != 2) print_number(minutes/10, 8);
  if (position == 3 && on == 1 || position != 3) print_number(minutes%10, 12);
}

void settings_time() {
  int button = 0;
  int change_digit = 0;
  delay(200);

  // цикл чтения кнопок
  while (!(button > 700 && button < 800)) {
    int change = 0;
    static int looper = 0;
    button = analogRead(_key_pin);
    
    // различаем кнопки по значениям
    if (button >= 0 && button < 100) { 
      change_digit++; 
      if (change_digit > 3) { 
        change_digit = 0;
      }
      looper = 0;
    } 
    else if (button > 400 && button < 600) { 
      change_digit--; 
      if (change_digit < 0) {
        change_digit = 3;
      }
      looper = 0;
    }
    else if (button > 100 && button < 400) { 
      change = 1;
    }
    else if (button > 300 && button < 400) { 
      change = -1;
    }

    // изменяем выбранный символ на значение
    switch(change_digit) {
      case 0:
        current_hours += change; 
        break;
      case 1:
        current_hours += change;
        break;
      case 2:
        current_minutes += change*10;
        break;
      case 3:
        current_minutes += change;
        break;
    }

    // проверяем выходил ли значение за пределы
    if (current_hours < 0) current_hours = 24;
    else if (current_hours > 23) current_hours = 0;
    if (current_minutes < 0) current_minutes = 60;
    else if (current_minutes >= 60) current_minutes = 0;

    // выводим символы с миганием    
    print_time_blink(current_hours, current_minutes, change_digit, looper > 3);
    if (looper == 6) {looper = 0; }
    looper++;
    delay(150);
  }

  set_time = millis();
}

void setup() {
  // инициализируем дисплей
  lcd.begin(16, 2);

  // инициализируем символы
  lcd.createChar(1, full);
  lcd.createChar(2, up_line);
  lcd.createChar(3, down_line);
  lcd.createChar(4, two_lines);
  lcd.createChar(5, point);
  
  lcd.setCursor(0, 0);

  // выводим бегущую строку
  print_start_text();
}

void loop() {
  // получаем время с учётов настроенного времени
  unsigned long long seconds = ((millis() - set_time) / 1000ul) + current_hours*3600 + current_minutes*60;
  static unsigned long long blink_point_time = 0;
  unsigned int minutes = (seconds % 3600ul) / 60ul;
  unsigned int hours = (seconds / 3600ul) % 24;
  
  // читаем кнопку
  int button = analogRead(_key_pin);
  if (button > 700 && button < 800) {
    current_hours = hours;
    current_minutes = minutes;
    lcd.clear(); 
    settings_time(); 
  }

  // выводим время  
  print_current_time (hours, minutes);

  // мигаем точками раз в полсекунды
  if (millis() - blink_point_time >= 1000) {  
    lcd.setCursor(7, 0);
    lcd.write(5);
    lcd.setCursor(7, 1);
    lcd.write(5);
    if (millis() - blink_point_time >= 1000) {blink_point_time = millis();}
  } else {
    lcd.setCursor(7, 0);
    lcd.write(" ");
    lcd.setCursor(7, 1);
    lcd.write(" ");    
  }
}
