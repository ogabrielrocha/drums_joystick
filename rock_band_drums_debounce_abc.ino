const int piezoPins[6] = {A0, A1, A2, A3, A4, A5}; // RED, YELLOW, BLUE, GREEN, YELLOWPLATE, BLUEPLATE, GREENPLATE
const int kick = 2; // Pedal do Bumbo
const int dpadPins[4] = {3, 4, 5, 6}; // pinos do d-pad
const int startPin = 7;
const int selectPin = 8;
const int threshold = 50; // Ajuste o limiar conforme necessário

unsigned long lastDebounceTime[7]; // Array para armazenar o tempo de debounce dos botões
unsigned long debounceDelay = 50; // Tempo de debounce (em milissegundos)
int lastButtonState[7] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}; // Array para armazenar o estado anterior dos botões
int buttonState[7] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}; // Array para armazenar o estado atual dos botões

void setup() {
  
  Serial.begin(115200);
  
  for (int i = 0; i < 4; i++) {
    pinMode(dpadPins[i], INPUT_PULLUP);
  }

  for (int i = 0; i < 7; i++) {
    pinMode(piezoPins[i], INPUT);
  }
  
  pinMode(kick, INPUT_PULLUP);
  pinMode(startPin, INPUT_PULLUP);
  pinMode(selectPin, INPUT_PULLUP);
}

void loop() {

  //================================================================================//
  //= PARTE DE DECLARAÇÃO DOS TAMBORES PRINCIPAIS (VERDE, AMARELO, AZUL E VERMELHO =//
  //================================================================================//
  
  int piezoValueRed = analogRead(piezoPins[0]);
  if (piezoValueRed > threshold) { // defina um limiar adequado
    Serial.println("H");
  } 

  int piezoValueYellow = analogRead(piezoPins[1]);
  if (piezoValueYellow > threshold) { // defina um limiar adequado
    Serial.println("I");
  } 

  int piezoValueBlue = analogRead(piezoPins[2]);
  if (piezoValueBlue > threshold) { // defina um limiar adequado
    Serial.println("J");
  } 

  int piezoValueGreen = analogRead(piezoPins[3]);
  if (piezoValueGreen > threshold) { // defina um limiar adequado
    Serial.println("K");
  } 

  //=======================================================================================//
  //========== PARTE DE DECLARAÇÃO DOS PRATOS ADICIONAIS AMARELO, AZUL E VERDE ============//
  //=======================================================================================//

  int piezoValueYellowPlate = analogRead(piezoPins[4]);
  if (piezoValueYellowPlate > threshold) { // defina um limiar adequado
    Serial.println("L");
  } 

    int piezoValueBluePlate = analogRead(piezoPins[5]);
  if (piezoValueBluePlate > threshold) { // defina um limiar adequado
    Serial.println("M");
  } 

    int piezoValueGreenPlate = analogRead(piezoPins[6]);
  if (piezoValueGreenPlate > threshold) { // defina um limiar adequado
    Serial.println("N");
  } 
  
  //================================================================================//
  //======== PARTE DE DECLARAÇÃO DOS BOTÕES DE NAVEGAÇÃO E KICK (BUMBO) ============//
  //================================================================================//
  debounceButton(0, dpadPins[0], "A");
  debounceButton(1, dpadPins[1], "B");
  debounceButton(2, dpadPins[2], "C");
  debounceButton(3, dpadPins[3], "D");

  debounceButton(4, kick, "G");

  debounceButton(6, selectPin, "E");
  debounceButton(5, startPin, "F");

  
  delay(10);
}



//================================================================================//
//=========== PARTE DE DECLARAÇÃO DA FUNÇÃO DE DEBOUNCE DOS BOTÕES ===============//
//================================================================================//
void debounceButton(int index, int pin, String message) {
  int reading = digitalRead(pin);

  if (reading != lastButtonState[index]) {
    lastDebounceTime[index] = millis();
  }

  if ((millis() - lastDebounceTime[index]) > debounceDelay) {
    if (reading != buttonState[index]) {
      buttonState[index] = reading;

      if (buttonState[index] == LOW) {
        Serial.println(message);
      }
    }
  }

  lastButtonState[index] = reading;
}
