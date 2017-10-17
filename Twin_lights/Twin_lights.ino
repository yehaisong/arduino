#define A 3
#define B 2
#define C 6
#define D 8
#define E 7
#define F_SEG 4
#define G 5

// Pins driving common anodes
#define CA1 13
#define CA2 12

// Pins for A B C D E F G, in sequence
const int segs[7] = { A, B, C, D, E, F_SEG, G };

// Segments that make each number
const byte numbers[10] = {0b0111111, 0b0000110, 0b1011011, 0b1001111, 0b1100110, 0b1101101,0b1111101, 0b0000111, 0b1111111, 0b1101111};

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F_SEG, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(CA1, OUTPUT);
  pinMode(CA2, OUTPUT);
}

void loop() {
  for (int digit1=0; digit1 < 10; digit1++) {
    for (int digit2=0; digit2 < 10; digit2++) {
      unsigned long startTime = millis();
      for (unsigned long elapsed=0; elapsed < 600; elapsed = millis() - startTime) {
        lightDigit1(numbers[digit1]);
        delay(5);
        lightDigit2(numbers[digit2]);
        delay(5);
      }
    }
  }
}

void lightDigit1(byte number) {
  digitalWrite(CA1, LOW);
  digitalWrite(CA2, HIGH);
  lightSegments(number);
}

void lightDigit2(byte number) {
  digitalWrite(CA1, HIGH);
  digitalWrite(CA2, LOW);
  lightSegments(number);
}

void lightSegments(byte number) {
  for (int i = 0; i < 7; i++) {
    int bit = bitRead(number, i);
    digitalWrite(segs[i], bit);
  }
}
