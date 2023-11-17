//Codigo servidor

const int sensorPin = A0;
//const int led = 7;

const int G[5][8] = {
  {1, 1, 0, 1, 0, 0, 0, 0},
  {0, 1, 1, 0, 1, 0, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {1, 1, 1, 0, 0, 0, 1, 0},
  {1, 0, 1, 0, 0, 0, 0, 1}
};

int m[5];  // Arreglo para almacenar los valores binarios de 5 bits
bool codigo[8];

void setup() {
  //pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  //float voltage = sensorValue * (5.0 / 1023.0);
  int temperatureC = (sensorValue * 5.0 / 1024) * 100;

  // Ajustar el rango de valores
  temperatureC = round(temperatureC);

  if (temperatureC <= 16) {
    temperatureC = 16;
  } else if (temperatureC >= 30) {
    temperatureC = 30;
  }
  
  /*Serial.println();
  Serial.print("Temperatura: ");
  Serial.print(temperatureC);
  Serial.print(" C");
  Serial.println();
  // Imprime la temperatura redondeada en formato binario manualmente
  Serial.print("Temperatura en binario: ");*/
  for (int i = 4; i >= 0; i--) {
    m[i] = (temperatureC & (1 << i)) ? 1 : 0;
  }
  
  //Inversion de el arreglo
  for (int i = 0; i < 2; i++) {
    int temp = m[i];
    m[i] = m[4 - i];
    m[4 - i] = temp;
  }
  
  //Impresion de binario en m
  /*for (int i = 0; i < 5; i++) {
  	Serial.print(m[i]);
  }*/
  
  //Serial.println();
  
  //Creacion de la nueva matriz
  int nuevaG[5][8];
  for (int i = 0; i < 5; i++) {
    if (m[i] == 1) {
      for (int j = 0; j < 8; j++) {
        nuevaG[i][j] = G[i][j];
      }
    } else {
      for (int j = 0; j < 8; j++) {
        nuevaG[i][j] = 0;
      }
    }
  }

  //Impresion de nuevaG
  /*for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 8; j++) {
      Serial.print(nuevaG[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }*/
  
  // Realiza la operación XOR por filas en nuevaG
  for (int fila = 0; fila < 4; fila++) {
    // Realiza el XOR de la fila actual con la siguiente
    for (int columna = 0; columna < 8; columna++) {
      nuevaG[fila + 1][columna] ^= nuevaG[fila][columna];

      // Almacena el resultado de la última operación XOR en el vector "codigo"
      if (fila == 3) {
        codigo[columna] = static_cast<bool>(nuevaG[fila + 1][columna]);
      }
    }
  }

  // Imprime cada elemento del vector "codigo" antes de enviarlo
  //Serial.print("Datos a enviar: ");
  for (int i = 0; i < 8; i++) {
    Serial.print(codigo[i]);
  }
  
  //Serial.println();
  
  // Envio de bits por puerto UART
  /*for (int i = 0; i < 8; i++) {
    Serial.write(codigo[i]);
  }*/
  
  //digitalWrite(led, HIGH);
  delay(1000);
}
