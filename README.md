# Chat GPT
### v1
```cpp
#include <IRremote.h>
#include <FastLED.h>

#define LED_PIN 3       
#define NUM_LEDS 60     
#define MAX_BRIGHTNESS 255  

const int IR_PIN = 0;  
IRrecv irrecv(IR_PIN);
decode_results results;

CRGB leds[NUM_LEDS];

// Переменные для управления эффектами
int currentEffect = 0;  // Текущий эффект (0 - нет эффекта)
unsigned long lastUpdate = 0;
int effectIndex = 0;

// IR BUTTON CODES
const int one = 69;
const int two = 70;
const int three = 71;
const int four = 68;
const int five = 64;
const int six = 67;
const int seven = 7;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(MAX_BRIGHTNESS);
  setColor(CRGB::Black); // По умолчанию выключаем
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.command);
    switch (IrReceiver.decodedIRData.command) {
      case one: currentEffect = 1; break;  // Breathing Light
      case two: currentEffect = 2; break;  // Color Flow
      case three: currentEffect = 3; break; // Sunset Glow
      case four: currentEffect = 4; break;  // Ambient Waves
      case five: currentEffect = 5; break;  // Midnight Glow
      case six: currentEffect = 6; break;  // Candle Flicker
      case seven: currentEffect = 7; break;  // Aurora Mode
    }
    IrReceiver.resume();
  }

  // Вызываем текущий эффект
  switch (currentEffect) {
    case 1: breathingLight(); break;
    case 2: colorFlow(); break;
    case 3: sunsetGlow(); break;
    case 4: ambientWaves(); break;
    case 5: midnightGlow(); break;
    case 6: candleFlicker(); break;
    case 7: auroraMode(); break;
  }
}

// Устанавливает один цвет на всю ленту
void setColor(CRGB color) {
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
}

// 1️⃣ Спокойная пульсация (Breathing Light)
void breathingLight() {
  unsigned long time = millis() / 10;
  int brightness = (sin(time * 0.02) + 1) * 127;
  FastLED.setBrightness(brightness);
  setColor(CRGB::White);
}

// 2️⃣ Градиентная заливка (Color Flow)
void colorFlow() {
  unsigned long time = millis() / 50;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV((time + i * 5) % 255, 255, 255);
  }
  FastLED.show();
}

// 3️⃣ Эффект свечения заката (Sunset Glow)
void sunsetGlow() {
  unsigned long time = millis() / 100;
  int phase = time % 3;
  if (phase == 0) setColor(CRGB(255, 100, 0)); // Оранжевый
  if (phase == 1) setColor(CRGB(255, 50, 0));  // Красно-оранжевый
  if (phase == 2) setColor(CRGB(200, 0, 50));  // Розоватый
}

// 4️⃣ Спокойные волны (Ambient Waves)
void ambientWaves() {
  unsigned long time = millis() / 30;
  for (int i = 0; i < NUM_LEDS; i++) {
    int brightness = (sin(time * 0.1 + i * 0.2) + 1) * 127;
    leds[i] = CHSV(160, 255, brightness);
  }
  FastLED.show();
}

// 5️⃣ Полуночный эффект (Midnight Glow)
void midnightGlow() {
  unsigned long time = millis() / 50;
  int phase = time % 3;
  if (phase == 0) setColor(CRGB(0, 0, 50));  // Темно-синий
  if (phase == 1) setColor(CRGB(10, 0, 70)); // Индиго
  if (phase == 2) setColor(CRGB(20, 0, 90)); // Фиолетовый
}

// 6️⃣ Эффект пламени (Candle Flicker)
void candleFlicker() {
  unsigned long time = millis();
  if (time - lastUpdate > 100) {
    lastUpdate = time;
    leds[random(NUM_LEDS)] = CRGB(255, 100 + random(50), 0);
    FastLED.show();
  }
}

// 7️⃣ Небесное сияние (Aurora Mode)
void auroraMode() {
  unsigned long time = millis() / 50;
  for (int i = 0; i < NUM_LEDS; i++) {
    int shift = (sin(time * 0.02 + i * 0.1) + 1) * 127;
    leds[i] = CHSV(shift, 200, 255);
  }
  FastLED.show();
}
```

### v2
```cpp
#include <IRremote.h>
#include <FastLED.h>

#define LED_PIN 3       
#define NUM_LEDS 60     
#define MAX_BRIGHTNESS 255  

const int IR_PIN = 0;  
IRrecv irrecv(IR_PIN);
decode_results results;

CRGB leds[NUM_LEDS];

// Переменные для управления эффектами
int currentEffect = 0;  // Текущий эффект (0 - нет эффекта)
unsigned long lastUpdate = 0;
int effectIndex = 0;

// IR BUTTON CODES
const int one = 69;
const int two = 70;
const int three = 71;
const int four = 68;
const int five = 64;
const int six = 67;
const int seven = 7;
const int eight = 21;
const int nine = 9;
const int ten = 25;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(MAX_BRIGHTNESS);
  setColor(CRGB::Black); // Выключаем ленту по умолчанию
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.command);
    switch (IrReceiver.decodedIRData.command) {
      case one: currentEffect = 1; break;  // Breathing Light
      case two: currentEffect = 2; break;  // Smooth Color Fade
      case three: currentEffect = 3; break; // Fire Effect
      case four: currentEffect = 4; break;  // Aurora Borealis
      case five: currentEffect = 5; break;  // Ocean Wave
      case six: currentEffect = 6; break;  // Sunset Glow
      case seven: currentEffect = 7; break;  // Star Twinkle
      case eight: currentEffect = 8; break;  // Neon Outline
      case nine: currentEffect = 9; break;  // Rainbow Cycle
      case ten: currentEffect = 10; break;  // Night Light
    }
    IrReceiver.resume();
  }

  // Вызываем текущий эффект
  switch (currentEffect) {
    case 1: breathingLight(); break;
    case 2: smoothColorFade(); break;
    case 3: fireEffect(); break;
    case 4: auroraBorealis(); break;
    case 5: oceanWave(); break;
    case 6: sunsetGlow(); break;
    case 7: starTwinkle(); break;
    case 8: neonOutline(); break;
    case 9: rainbowCycle(); break;
    case 10: nightLight(); break;
  }
}

// Устанавливает один цвет на всю ленту
void setColor(CRGB color) {
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
}

// 1️⃣ Мягкое дыхание (Breathing Light)
void breathingLight() {
  unsigned long time = millis() / 10;
  int brightness = (sin(time * 0.02) + 1) * 127;
  FastLED.setBrightness(brightness);
  setColor(CRGB::White);
}

// 2️⃣ Плавное переливание (Smooth Color Fade)
void smoothColorFade() {
  unsigned long time = millis() / 50;
  setColor(CHSV(time % 255, 255, 255));
}

// 3️⃣ Огонь (Fire Effect)
void fireEffect() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, random(50, 150), 0);  // Оранжево-красные оттенки
  }
  FastLED.show();
  delay(30);
}

// 4️⃣ Северное сияние (Aurora Borealis)
void auroraBorealis() {
  unsigned long time = millis() / 50;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV((time + i * 5) % 128, 255, 255);  // Зеленые и синие тона
  }
  FastLED.show();
}

// 5️⃣ Океанская волна (Ocean Wave)
void oceanWave() {
  unsigned long time = millis() / 30;
  setColor(CHSV(160 + sin(time * 0.02) * 20, 255, 255));  // От бирюзового к синему
}

// 6️⃣ Закат (Sunset Glow)
void sunsetGlow() {
  unsigned long time = millis() / 100;
  int phase = time % 3;
  if (phase == 0) setColor(CRGB(255, 100, 0)); // Оранжевый
  if (phase == 1) setColor(CRGB(255, 50, 0));  // Красно-оранжевый
  if (phase == 2) setColor(CRGB(200, 0, 50));  // Розоватый
}

// 7️⃣ Звездное мерцание (Star Twinkle)
void starTwinkle() {
  unsigned long time = millis();
  if (time - lastUpdate > 100) {
    lastUpdate = time;
    leds[random(NUM_LEDS)] = CRGB::White;
    FastLED.show();
  }
}

// 8️⃣ Неоновый контур (Neon Outline)
void neonOutline() {
  unsigned long time = millis() / 50;
  int center = NUM_LEDS / 2;
  int range = (sin(time * 0.02) + 1) * (NUM_LEDS / 2);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  for (int i = center - range; i < center + range; i++) {
    if (i >= 0 && i < NUM_LEDS) {
      leds[i] = CRGB::Cyan;
    }
  }
  FastLED.show();
}

// 9️⃣ Радужный цикл (Rainbow Cycle)
void rainbowCycle() {
  unsigned long time = millis() / 50;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV((time + i * 5) % 255, 255, 255);
  }
  FastLED.show();
}

// 🔟 Ночная подсветка (Night Light)
void nightLight() {
  setColor(CRGB(255, 150, 50));  // Теплый белый свет
}
```


# Grok
```cpp
#include <IRremote.h>
#include <FastLED.h>

#define LED_PIN 3       // Пин для LED ленты
#define NUM_LEDS 60     // Количество светодиодов
#define MAX_BRIGHTNESS 128 // Максимальная яркость (половина от 255 для мягкости)
#define BRIGHTNESS_STEP 10
#define FADE_SPEED 20   // Скорость изменения эффектов (мс)

// Переменные для эффектов
int brightness = MAX_BRIGHTNESS;
int activeEffect = 0; // 0 - выключено, 1-5 - эффекты
unsigned long previousMillis = 0;

// Переменные для эффектов
uint8_t fadeValue = 0;      // Для дыхания и пульсации
bool fadingIn = true;       // Направление изменения яркости
uint8_t wavePos = 0;        // Позиция волны
uint8_t colorIndex = 0;     // Индекс цвета для градиента
uint8_t sunsetHue = 0;      // Оттенок для заката

// Цвета для эффектов
CRGB currentColor = CRGB(0, 255, 0); // Начальный цвет - зеленый
CRGB gradientColors[] = {CRGB(0, 0, 255), CRGB(0, 255, 0), CRGB(128, 0, 128), CRGB(255, 255, 200)}; // Синий, зеленый, фиолетовый, теплый белый
CRGB black = CRGB(0, 0, 0);

// Коды кнопок ИК пульта
const int one = 69;
const int two = 70;
const int three = 71;
const int four = 68;
const int five = 64;
const int up = 24;
const int down = 82;
const int star = 22;

const int IR_PIN = 0; // ИК-приемник на пине 0
IRrecv irrecv(IR_PIN);
decode_results results;

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR Receiver Ready");

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
  fill_solid(leds, NUM_LEDS, currentColor);
  FastLED.show();
}

// Обработка ИК сигналов
void handleIRInput(int command) {
  Serial.print("Received command: ");
  Serial.println(command);

  switch (command) {
    case one:
      activeEffect = 1; // Плавное дыхание
      currentColor = gradientColors[0]; // Синий
      fadeValue = 0;
      fadingIn = true;
      break;

    case two:
      activeEffect = 2; // Градиентный переход
      colorIndex = 0;
      fadeValue = 0;
      break;

    case three:
      activeEffect = 3; // Волна по контуру
      wavePos = 0;
      currentColor = gradientColors[1]; // Зеленый
      break;

    case four:
      activeEffect = 4; // Статичный градиент с пульсацией
      fadeValue = 255; // Начальная яркость максимальная
      fadingIn = false;
      break;

    case five:
      activeEffect = 5; // Имитация заката
      sunsetHue = 0;
      fadeValue = 0;
      break;

    case star:
      activeEffect = 0; // Выключить
      fill_solid(leds, NUM_LEDS, black);
      FastLED.show();
      break;

    case up:
      if (brightness + BRIGHTNESS_STEP <= MAX_BRIGHTNESS) {
        brightness += BRIGHTNESS_STEP;
        FastLED.setBrightness(brightness);
        FastLED.show();
      }
      break;

    case down:
      if (brightness - BRIGHTNESS_STEP >= 0) {
        brightness -= BRIGHTNESS_STEP;
        FastLED.setBrightness(brightness);
        FastLED.show();
      }
      break;
  }
}

// Эффект 1: Плавное дыхание
void breathingEffect() {
  if (millis() - previousMillis >= FADE_SPEED) {
    previousMillis = millis();
    fill_solid(leds, NUM_LEDS, currentColor);
    if (fadingIn) {
      fadeValue = min(fadeValue + 5, 255);
      if (fadeValue == 255) fadingIn = false;
    } else {
      fadeValue = max(fadeValue - 5, 0);
      if (fadeValue == 0) fadingIn = true;
    }
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].fadeToBlackBy(255 - fadeValue);
    }
    FastLED.show();
  }
}

// Эффект 2: Градиентный переход
void gradientFadeEffect() {
  if (millis() - previousMillis >= FADE_SPEED) {
    previousMillis = millis();
    fadeValue += 1;
    if (fadeValue == 255) {
      fadeValue = 0;
      colorIndex = (colorIndex + 1) % 4; // Переход к следующему цвету
    }
    CRGB targetColor = gradientColors[(colorIndex + 1) % 4];
    CRGB startColor = gradientColors[colorIndex];
    fill_solid(leds, NUM_LEDS, blend(startColor, targetColor, fadeValue));
    FastLED.show();
  }
}

// Эффект 3: Волна по контуру
void waveEffect() {
  if (millis() - previousMillis >= FADE_SPEED) {
    previousMillis = millis();
    fill_solid(leds, NUM_LEDS, black);
    for (int i = 0; i < NUM_LEDS; i++) {
      uint8_t brightness = sin8(wavePos + i * 8); // Синусоидальная волна
      leds[i] = currentColor;
      leds[i].fadeToBlackBy(255 - brightness);
    }
    wavePos += 2; // Медленное движение волны
    FastLED.show();
  }
}

// Эффект 4: Статичный градиент с пульсацией
void gradientPulseEffect() {
  if (millis() - previousMillis >= FADE_SPEED) {
    previousMillis = millis();
    fill_gradient_RGB(leds, 0, CRGB(0, 0, 255), NUM_LEDS - 1, CRGB(255, 255, 200)); // От синего к теплому белому
    if (fadingIn) {
      fadeValue = min(fadeValue + 5, 255);
      if (fadeValue == 255) fadingIn = false;
    } else {
      fadeValue = max(fadeValue - 5, 200); // Минимум 200 для слабой пульсации
      if (fadeValue == 200) fadingIn = true;
    }
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].fadeToBlackBy(255 - fadeValue);
    }
    FastLED.show();
  }
}

// Эффект 5: Имитация заката
void sunsetEffect() {
  if (millis() - previousMillis >= FADE_SPEED) {
    previousMillis = millis();
    sunsetHue += 1;
    fill_solid(leds, NUM_LEDS, CHSV(sunsetHue % 40 + 10, 255, 255)); // От красного к оранжевому
    FastLED.show();
  }
}

void loop() {
  if (IrReceiver.decode()) {
    handleIRInput(IrReceiver.decodedIRData.command);
    IrReceiver.resume();
  }

  switch (activeEffect) {
    case 1: breathingEffect(); break;
    case 2: gradientFadeEffect(); break;
    case 3: waveEffect(); break;
    case 4: gradientPulseEffect(); break;
    case 5: sunsetEffect(); break;
  }
}
```

# DeepSeek
```cpp
#include <IRremote.h>
#include <FastLED.h>

#define LED_PIN 3       // Пин, к которому подключена лента
#define NUM_LEDS 60     // Количество светодиодов в ленте
#define MAX_BRIGHTNESS 255  // Максимальная яркость
#define BRIGHTNESS_STEP 10  // Шаг изменения яркости
#define BRIGHTNESS_INTERVAL 10  // Интервал для эффектов
#define PERIOD 2000      // Период для некоторых эффектов

// Цвета
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

// Коды кнопок пульта
const int one = 69;
const int two = 70;
const int three = 71;
const int four = 68;
const int five = 64;
const int six = 67;
const int seven = 7;
const int eight = 21;
const int nine = 9;
const int ten = 25; // Предположим, что 10 — это кнопка "0"

const int IR_PIN = 0;  // Пин для IR-приемника
IRrecv irrecv(IR_PIN);
decode_results results;

CRGB leds[NUM_LEDS];
CRGB currentColor = black; // Текущий цвет
int brightness = 128;      // Текущая яркость
int currentMode = 0;       // Текущий режим (0 — выключено)

void setup() {
  delay(1000);
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR Receiver Ready");

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
}

void loop() {
  if (IrReceiver.decode()) {
    uint16_t code = IrReceiver.decodedIRData.command;
    if (code != 0 && code != 47492) { // Игнорируем некорректные коды
      Serial.print("Received code: ");
      Serial.println(code);

      switch (code) {
        case one:
          currentMode = 1; // Плавное изменение цвета
          break;
        case two:
          currentMode = 2; // Мягкое мерцание
          break;
        case three:
          currentMode = 3; // Дыхание
          break;
        case four:
          currentMode = 4; // Бегущая волна
          break;
        case five:
          currentMode = 5; // Цветовые зоны
          break;
        case six:
          currentMode = 6; // Огненный эффект
          break;
        case seven:
          currentMode = 7; // Статичный градиент
          break;
        case eight:
          currentMode = 8; // Радуга
          break;
        case nine:
          currentMode = 9; // Свечение контуров
          break;
        case ten:
          currentMode = 10; // Пульс
          break;
        default:
          currentMode = 0; // Выключить
          break;
      }
    }
    IrReceiver.resume();
  }

  // Выполнение текущего эффекта
  switch (currentMode) {
    case 1:
      colorFadeEffect();
      break;
    case 2:
      twinkleEffect();
      break;
    case 3:
      breathingEffect();
      break;
    case 4:
      waveEffect();
      break;
    case 5:
      colorZonesEffect();
      break;
    case 6:
      fireEffect();
      break;
    case 7:
      gradientEffect();
      break;
    case 8:
      rainbowEffect();
      break;
    case 9:
      edgeGlowEffect();
      break;
    case 10:
      pulseEffect();
      break;
    default:
      fill_solid(leds, NUM_LEDS, black); // Выключить ленту
      FastLED.show();
      break;
  }
}

// Эффект 1: Плавное изменение цвета
void colorFadeEffect() {
  static uint8_t hue = 0;
  fill_solid(leds, NUM_LEDS, CHSV(hue, 255, 255));
  hue++;
  FastLED.show();
  delay(20);
}

// Эффект 2: Мягкое мерцание
void twinkleEffect() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (random(10) == 0) {
      leds[i] = currentColor;
      leds[i].fadeToBlackBy(random(128, 255));
    }
  }
  FastLED.show();
  delay(50);
}

// Эффект 3: Дыхание
void breathingEffect() {
  static int breathBrightness = 0;
  static int breathStep = 1;
  breathBrightness += breathStep;
  if (breathBrightness >= 255 || breathBrightness <= 0) {
    breathStep = -breathStep;
  }
  FastLED.setBrightness(breathBrightness);
  FastLED.show();
  delay(10);
}

// Эффект 4: Бегущая волна
void waveEffect() {
  static uint8_t wavePosition = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    int brightness = sin8(i * 32 + wavePosition);
    leds[i] = currentColor;
    leds[i].fadeToBlackBy(255 - brightness);
  }
  wavePosition += 5;
  FastLED.show();
  delay(30);
}

// Эффект 5: Цветовые зоны
void colorZonesEffect() {
  int zoneSize = NUM_LEDS / 3;
  fill_solid(leds, zoneSize, red);
  fill_solid(leds + zoneSize, zoneSize, green);
  fill_solid(leds + 2 * zoneSize, NUM_LEDS - 2 * zoneSize, blue);
  FastLED.show();
}

// Эффект 6: Огненный эффект
void fireEffect() {
  static uint16_t firePosition = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    int brightness = inoise8(i * 30, firePosition);
    leds[i] = ColorFromPalette(HeatColors_p, brightness);
  }
  firePosition += 30;
  FastLED.show();
  delay(50);
}

// Эффект 7: Статичный градиент
void gradientEffect() {
  fill_gradient(leds, NUM_LEDS, CHSV(160, 255, 255), CHSV(200, 255, 255), FORWARD_HUES);
  FastLED.show();
}

// Эффект 8: Радуга
void rainbowEffect() {
  static uint8_t hue = 0;
  fill_rainbow(leds, NUM_LEDS, hue);
  hue++;
  FastLED.show();
  delay(20);
}

// Эффект 9: Свечение контуров
void edgeGlowEffect() {
  fill_solid(leds, NUM_LEDS, black);
  leds[0] = currentColor;
  leds[NUM_LEDS - 1] = currentColor;
  FastLED.show();
}

// Эффект 10: Пульс
void pulseEffect() {
  static uint8_t pulseValue = 0;
  pulseValue += 5;
  int brightness = sin8(pulseValue);
  FastLED.setBrightness(brightness);
  FastLED.show();
  delay(20);
}
```

# Claude
```cpp
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
```
