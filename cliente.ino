//Codigo cliente

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() >= 8) {
    bool receivedBool[8];

    // Lee los 8 caracteres en el arreglo
    for (int i = 0; i < 8; i++) {
      char receivedChar = Serial.read();
      receivedBool[i] = (receivedChar == '1') ? true : false;
    }

    // Imprime el arreglo recibido
    Serial.print("Codigo recibido: ");
    for (int i = 0; i < 8; i++) {
      Serial.print(receivedBool[i]);
      //Serial.print(" ");
    }
    Serial.println();
  }
  delay(1000);
}
