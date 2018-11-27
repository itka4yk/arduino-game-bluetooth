#include <SoftwareSerial.h>
//SoftwareSerial Bluetooth(0, 1); // RX, TX
//int LED = LED_BUILTIN; // the on-board LED
//char data = 0; // the data received

const int PROBABILITY = 850;
const int LEVEL_LENGTH = 400;
int playerPos = 0;
char level[2][LEVEL_LENGTH];
int speed = 300;
bool isGameOver = false;

char player = '@';
char car = '#';
char nothing = ' ';
int pos = 0;

void setup() {
  //  Bluetooth.begin(9600);
  //  Bluetooth.println("Send 1 to turn on the LED. Send 0 to turn Off");
  //  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  randomise();
}

void printLine(char* lvl, int start, int line) {
  Serial.print(line == playerPos ? player : lvl[0]);
  for (int i = 1; i < 16; i++) {
    Serial.print(lvl[i + start]);
  }
  Serial.print('\n');
}

void randomise() {
  randomSeed(analogRead(0));
  for (int i = 0; i < LEVEL_LENGTH; i++) {
    level[0][i] = nothing;
    level[1][i] = nothing;
    if (random(1000) < PROBABILITY) continue;
    if (random(10) > 5) {
      level[0][i] = car;
    } else {
      level[1][i] = car;
    }
  }
}

void checkGame() {
//  if (level[playerPos][pos] == car) {
//    Serial.println("CRASHED");
//    isGameOver = true;
//  }
}

void loop() {
  if (isGameOver) {
    Serial.println("gameover");
  } else {
    if (Serial.available() > 0) {
      char move = Serial.read();
      if (move == '1')
        playerPos = 0;
      else if (move == '0')
        playerPos = 1;
    }
    checkGame();
    if (pos < LEVEL_LENGTH - 17) {
      Serial.println("****************");
      printLine(level[0], pos, 0);
      printLine(level[1], pos, 1);
      Serial.println("****************");
    } else {
      Serial.println("you win");
    }
    pos++;
  }

  delay(speed);
}
