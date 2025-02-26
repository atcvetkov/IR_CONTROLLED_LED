#include <IRremote.h>
#include <FastLED.h>

#define LED_PIN 3       // Пин подключения LED ленты
#define NUM_LEDS 60     // Количество светодиодов
#define MAX_BRIGHTNESS 255  // Максимальная яркость (0-255)
#define BRIGHTNESS_STEP 10   // Шаг изменения яркости
#define BRIGHTNESS_INTERVAL 10  // Интервал между шагами изменения яркости (мс)

// IR BUTTON CODES
const int zero = 25;
const int one = 69;
const int two = 70;
const int three = 71;
const int four = 68;
const int five = 64;
const int six = 67;
const int seven = 7;
const int eight = 21;
const int nine = 9;
const int star = 22;
const int up = 24;
const int down = 82; 
const int ok = 28;
const int hash = 13;

// Настройки для эффектов
#define CYCLE_SPEED 20     // Скорость циклических эффектов
#define BREATH_SPEED 10    // Скорость "дыхания"
#define FADE_SPEED 5       // Скорость плавного перехода
#define WAVE_SPEED 8       // Скорость волны
#define METEOR_SPEED 10    // Скорость метеора
#define TWINKLE_CHANCE 10  // Шанс мерцания (из 100)
#define GRADIENT_SPEED 15  // Скорость изменения градиента
#define BOUNCE_SPEED 8     // Скорость отскока

const int IR_PIN = 0;  // Пин ИК-приемника
IRrecv irrecv(IR_PIN);
decode_results results;

CRGB leds[NUM_LEDS];

// Общие цвета
CRGB red = CRGB(255, 0, 0);
CRGB green = CRGB(0, 255, 0);
CRGB blue = CRGB(0, 0, 255);
CRGB white = CRGB(255, 255, 255);
CRGB black = CRGB(0, 0, 0);
CRGB yellow = CRGB(255, 255, 0);
CRGB magenta = CRGB(255, 0, 255);
CRGB cyan = CRGB(0, 255, 255);
CRGB orange = CRGB(255, 165, 0);
CRGB pink = CRGB(255, 192, 203);
CRGB purple = CRGB(128, 0, 128);
CRGB teal = CRGB(0, 128, 128);
CRGB violet = CRGB(238, 130, 238);
CRGB lavender = CRGB(230, 230, 250);
CRGB indigo = CRGB(75, 0, 130);
CRGB brown = CRGB(139, 69, 19);

// Палитры для эффектов
CRGBPalette16 purpleBluePalette = CRGBPalette16(
  CRGB::Purple, CRGB::Blue, CRGB::DarkBlue, CRGB::Purple
);

CRGBPalette16 oceanPalette = CRGBPalette16(
  CRGB::DarkBlue, CRGB::Blue, CRGB::Teal, CRGB::Aqua
);

CRGBPalette16 forestPalette = CRGBPalette16(
  CRGB::DarkGreen, CRGB::Green, CRGB::ForestGreen, CRGB::LimeGreen
);

CRGBPalette16 sunsetPalette = CRGBPalette16(
  CRGB::DarkRed, CRGB::OrangeRed, CRGB::Orange, CRGB::Gold
);

byte currentEffect = 0;    // Текущий эффект
int brightness = 128;      // Начальная яркость
unsigned long lastUpdate = 0;  // Для отслеживания времени обновления эффектов

// Переменные для эффектов
uint8_t hue = 0;           // Для изменения цвета
uint8_t pos = 0;           // Для позиции в эффектах
uint8_t startPos = 0;      // Начальная позиция волн
bool direction = true;     // Направление движения
uint8_t breathBrightness = 128; // Яркость для эффекта дыхания
bool breathDirection = true;    // Направление дыхания
int meteorPos = 0;         // Позиция метеора
uint8_t colorIndex = 0;    // Индекс цвета для палитр

void setup() {
  delay(1000);
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR Receiver Ready");

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
  
  // Начальный эффект
  fill_solid(leds, NUM_LEDS, CRGB(32, 32, 32));
  FastLED.show();
}

void loop() {
  // Обработка ИК команд
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.command);

    // Обработка команд пульта
    switch (IrReceiver.decodedIRData.command) {
      case zero:  // Кнопка 0
        currentEffect = 0;  // Мягкое свечение
        break;
      case one:   // Кнопка 1
        currentEffect = 1;  // Дыхание
        break;
      case two:   // Кнопка 2
        currentEffect = 2;  // Градиент океана
        break;
      case three: // Кнопка 3
        currentEffect = 3;  // Радуга
        break;
      case four:  // Кнопка 4
        currentEffect = 4;  // Мягкая волна
        break;
      case five:  // Кнопка 5
        currentEffect = 5;  // Мерцающие звезды
        break;
      case six:   // Кнопка 6
        currentEffect = 6;  // Метеор
        break;
      case seven: // Кнопка 7
        currentEffect = 7;  // Пульс
        break;
      case eight: // Кнопка 8
        currentEffect = 8;  // Лесной градиент
        break;
      case nine:  // Кнопка 9
        currentEffect = 9;  // Закат
        break;
      case star:  // Кнопка *
        fill_solid(leds, NUM_LEDS, black);  // Выключить
        FastLED.show();
        break;
      case up:    // Кнопка Up
        if (brightness + BRIGHTNESS_STEP <= MAX_BRIGHTNESS) {
          brightness += BRIGHTNESS_STEP;
          FastLED.setBrightness(brightness);
        }
        break;
      case down:  // Кнопка Down
        if (brightness - BRIGHTNESS_STEP >= 0) {
          brightness -= BRIGHTNESS_STEP;
          FastLED.setBrightness(brightness);
        }
        break;
    }
    
    IrReceiver.resume();
  }

  // Обновление эффекта основано на времени
  unsigned long currentMillis = millis();
  
  // Запускаем текущий эффект
  switch (currentEffect) {
    case 0:
      // Эффект 0: Мягкое статичное свечение
      if (currentMillis - lastUpdate > 500) {
        fill_solid(leds, NUM_LEDS, CRGB(32, 32, 64)); // Мягкий синий
        FastLED.show();
        lastUpdate = currentMillis;
      }
      break;
      
    case 1:
      // Эффект 1: Мягкое дыхание
      if (currentMillis - lastUpdate > BREATH_SPEED) {
        breathingEffect();
        lastUpdate = currentMillis;
      }
      break;
      
    case 2:
      // Эффект 2: Градиент океана
      if (currentMillis - lastUpdate > GRADIENT_SPEED) {
        paletteEffect(oceanPalette);
        lastUpdate = currentMillis;
      }
      break;
      
    case 3:
      // Эффект 3: Плавная радуга
      if (currentMillis - lastUpdate > CYCLE_SPEED) {
        rainbowEffect();
        lastUpdate = currentMillis;
      }
      break;
      
    case 4:
      // Эффект 4: Мягкая волна
      if (currentMillis - lastUpdate > WAVE_SPEED) {
        waveEffect();
        lastUpdate = currentMillis;
      }
      break;
      
    case 5:
      // Эффект 5: Мерцающие звезды
      if (currentMillis - lastUpdate > 50) {
        twinkleEffect();
        lastUpdate = currentMillis;
      }
      break;
      
    case 6:
      // Эффект 6: Метеор
      if (currentMillis - lastUpdate > METEOR_SPEED) {
        meteorEffect();
        lastUpdate = currentMillis;
      }
      break;
      
    case 7:
      // Эффект 7: Пульс
      if (currentMillis - lastUpdate > 15) {
        pulseEffect();
        lastUpdate = currentMillis;
      }
      break;
      
    case 8:
      // Эффект 8: Лесной градиент
      if (currentMillis - lastUpdate > GRADIENT_SPEED) {
        paletteEffect(forestPalette);
        lastUpdate = currentMillis;
      }
      break;
      
    case 9:
      // Эффект 9: Закат
      if (currentMillis - lastUpdate > GRADIENT_SPEED) {
        paletteEffect(sunsetPalette);
        lastUpdate = currentMillis;
      }
      break;
  }
}

// 1: Эффект дыхания - плавное изменение яркости
void breathingEffect() {
  if (breathDirection) {
    breathBrightness += 1;
    if (breathBrightness >= 170) {
      breathDirection = false;
    }
  } else {
    breathBrightness -= 1;
    if (breathBrightness <= 50) {
      breathDirection = true;
    }
  }
  
  // Используем мягкий синий цвет
  fill_solid(leds, NUM_LEDS, CRGB(20, 20, breathBrightness));
  FastLED.show();
}

// 2 и 8, 9: Эффект палитры - плавное движение по заданной палитре
void paletteEffect(CRGBPalette16 palette) {
  colorIndex += 1;
  for (int i = 0; i < NUM_LEDS; i++) {
    // Смещение для каждого LED для создания движущегося эффекта
    uint8_t colorPos = colorIndex + (i * 2);
    leds[i] = ColorFromPalette(palette, colorPos, brightness, LINEARBLEND);
  }
  FastLED.show();
}

// 3: Эффект радуги - плавное изменение цвета по всей ленте
void rainbowEffect() {
  hue++;
  fill_rainbow(leds, NUM_LEDS, hue, 3);
  // Снижаем насыщенность для большей мягкости
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].fadeToBlackBy(180);
  }
  FastLED.show();
}

// 4: Эффект волны - волна перемещается по ленте
void waveEffect() {
  fadeToBlackBy(leds, NUM_LEDS, 20);
  
  int pos = startPos;
  // Создаем волну с несколькими светодиодами
  for (int i = 0; i < 10; i++) {
    int currentPos = (pos + i) % NUM_LEDS;
    // Интенсивность зависит от расстояния от центра волны
    int intensity = 255 - abs((i - 5) * 40);
    if (intensity < 0) intensity = 0;
    leds[currentPos] += CHSV(150, 200, intensity); // Бирюзовый
  }
  
  startPos = (startPos + 1) % NUM_LEDS;
  FastLED.show();
}

// 5: Эффект мерцающих звезд
void twinkleEffect() {
  // Медленно затухаем
  fadeToBlackBy(leds, NUM_LEDS, 10);
  
  // Случайно добавляем "звезды"
  for (int i = 0; i < NUM_LEDS; i++) {
    if (random8() < TWINKLE_CHANCE) {
      leds[i] = CHSV(random8(150, 200), 200, random8(50, 150));
    }
  }
  FastLED.show();
}

// 6: Эффект метеора - яркая точка с хвостом
void meteorEffect() {
  // Затухание для создания эффекта хвоста
  fadeToBlackBy(leds, NUM_LEDS, 64);
  
  // Метеор с хвостом
  int meteorSize = 3;
  for (int i = 0; i < meteorSize; i++) {
    int pos = (meteorPos - i + NUM_LEDS) % NUM_LEDS;
    if (i == 0) {
      leds[pos] = CHSV(200, 255, 255); // Голова метеора
    } else {
      // Хвост метеора тускнеет
      leds[pos] = CHSV(220, 255, 255 / (i + 1));
    }
  }
  
  meteorPos = (meteorPos + 1) % NUM_LEDS;
  FastLED.show();
}

// 7: Эффект пульса - синхронное пульсирование с изменением цвета
void pulseEffect() {
  static int pulseStep = 0;
  static bool pulseDirection = true;
  static uint8_t hueShift = 0;
  
  // Изменение направления пульса
  if (pulseDirection) {
    pulseStep++;
    if (pulseStep >= 100) pulseDirection = false;
  } else {
    pulseStep--;
    if (pulseStep <= 5) {
      pulseDirection = true;
      hueShift += 20; // Меняем цвет при каждом новом пульсе
    }
  }
  
  // Применяем пульс с плавным изменением яркости
  uint8_t brightness = map(pulseStep, 0, 100, 10, 150);
  fill_solid(leds, NUM_LEDS, CHSV(hueShift, 200, brightness));
  FastLED.show();
}