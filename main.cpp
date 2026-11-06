#include <LiquidCrystal.h>

#define BUTTON 5

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

bool pressed;
int pressedTime = 0;
int unPressedTime = 0;
String morse = "";
String result = "";

struct keyValuePair {
  String code;
  String letter; 
};

keyValuePair morseConversions[] = {
  {"*-", "a"},
  {"-***", "b"},
  {"-*-*", "c"},
  {"-**", "d"},
  {"*", "e"},
  {"**-*", "f"},
  {"--*", "g"},
  {"****", "h"},
  {"**", "i"},
  {"*---", "j"},
  {"-*-", "k"},
  {"*-**", "l"},
  {"--", "m"},
  {"-*", "n"},
  {"---", "o"},
  {"*--*", "p"},
  {"--*-", "q"},
  {"*-*", "r"},
  {"***", "s"},
  {"-", "t"},
  {"**-", "u"},
  {"***-", "v"},
  {"*--", "w"},
  {"-**-", "x"},
  {"-*--", "y"},
  {"--**", "z"}
};

const int morseConSize = sizeof(morseConversions);

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  lcd.begin(16, 2);
}

void loop() {
  pressed = (digitalRead(BUTTON) == LOW);

  if (pressed) {

    // Register letter
    if (unPressedTime > 20) {
      result += search(morse);
      morse = "";
    }

    // Track time button is held
    while (pressed) {
      pressedTime++; // Counts 20ths of a second
      delay(50);
      pressed = (digitalRead(BUTTON) == LOW);
    }

    // Check if dot or dash
    if (pressedTime > 15) {
      morse = "";
      result += " ";
    } else if (pressedTime > 5) {
      morse += "-";
    } else {
      morse += "*";
    }

    printResults();
    
  }

  // Track time button is not held
  unPressedTime++;
  delay(50);

}

// Search for corresponding letter in morse key
String search(String morse) {
  for (int i = 0; i < morseConSize; i++) {
    if (morseConversions[i].code == morse) {
      return morseConversions[i].letter;
    }
  }
}

void printResults() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(morse);
  lcd.setCursor(0, 1);
  lcd.print(result);
  pressedTime = 0;
  unPressedTime = 0;
  delay(100);
}
