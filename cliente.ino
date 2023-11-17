//Codigo cliente

const int H_T[8][3] = {
  {1, 0, 0},
  {0, 1, 0},
  {0, 0, 1},
  {1, 1, 0},
  {0, 1, 1},
  {0, 0, 1},
  {1, 1, 1},
  {1, 0, 1}
};

const int error [8][8] = {
  {1, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 1}
};

int mensajes = 0;
int errores = 0;

bool sindrome[3];

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
    Serial.println();
    Serial.print("Codigo recibido: ");
    for (int i = 0; i < 8; i++) {
      Serial.print(receivedBool[i]);
      //Serial.print(" ");
    }
    
    Serial.println();
    
    //Creacion de la nueva matriz
    int nuevaHT [8][3];
    for (int i = 0; i < 8; i++) {
      if (receivedBool[i] == true) {
        for(int j = 0; j < 3; j++) {
        	nuevaHT[i][j] = H_T[i][j];
        }
      } else {
        for(int j = 0; j < 3; j++) {
        	nuevaHT[i][j] = 0;
        }
      }
    }
    
    //Impresion de la matriz
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 3; j++) {
      	Serial.print(nuevaHT[i][j]);
        Serial.print(" ");
      }
      Serial.println();
    }
    
    for (int fila = 0; fila < 8 - 1; fila++) {
    // Realiza el XOR de la fila actual con la siguiente
      for (int columna = 0; columna < 3; columna++) {
        nuevaHT[fila + 1][columna] ^= nuevaHT[fila][columna];
        // Almacena el resultado de la última operación XOR en el vector "codigo"
        if (fila == 8 - 2) {
          sindrome[columna] = static_cast<bool>(nuevaHT[fila + 1][columna]);
        }
      }
  	}
    
    int erroract = 0;
    Serial.println("Sindrome");
	//Impresion del sindrome
    int bandera = 0;
    for (int i = 0; i < 3; i++) {
    	Serial.print(sindrome[i]);
      	Serial.print(" ");
        if(sindrome[i] != 0) {
        	bandera++;
        } if(i == 2 && bandera != 0) {
          	Serial.println(" ERROR DETECTADO");
        	  errores++;
          	erroract = 1;
            //Serial.println();
        }
    }

    mensajes++;
    Serial.println();
    Serial.print("Errores detectados: ");
    Serial.println(errores);
    Serial.print("Mensajes recibidos: ");
    Serial.print(mensajes);
    Serial.println();
    
    //Correcion de error
    if(erroract != 0) {
      int bandera2 = 0;
      int opcion = -1;
      if (erroract != 0) {
        for (int i = 0; i < 8; i++) {
          bandera2 = 0;
          for (int j = 0; j < 3; j++) {
            if (H_T[i][j] == sindrome[j]) {
              bandera2++;
            }//Fin if
            if(bandera2 == 3) {
              opcion = i;
            }//Fin if2
          }//Fin for columnas
        }//Fin for filas
        if(opcion != -1) { //Se encontro el indice
        Serial.println();
        Serial.print("Opcion = ");
        Serial.print(opcion);
        Serial.println();
        bool corregido[8];
        for (int i = 0; i < 8; i++) {
          corregido[i] = receivedBool[i] ^ error[opcion][i];
        }

        Serial.print("CORRECCION ESTIMADA: ");
        Serial.println();
        
        for (int i = 0; i < 8; i++) {
          Serial.print(corregido[i]);
        }
        Serial.println();
          /*for (int i = 0; i < 8; ++i) {
            corregido[i] = receivedBool[i] ^ error[opcion][i];
            for (int j = 0; j < 8; j++) {
                Serial.print(corregido[j]);
                Serial.print(" ");
          }
        Serial.println();
          } */

          //Verificacion de la correccion

          //Creacion de la nueva matriz
          int nuevaHT2 [8][3];
          for (int i = 0; i < 8; i++) {
            if (corregido[i] == true) {
              for(int j = 0; j < 3; j++) {
                nuevaHT2[i][j] = H_T[i][j];
              }
            } else {
              for(int j = 0; j < 3; j++) {
                nuevaHT2[i][j] = 0;
              }
            }
          }

          //Impresion de la matriz
          for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 3; j++) {
              Serial.print(nuevaHT2[i][j]);
              Serial.print(" ");
            }
            Serial.println();
          }

          bool sindrome2[3];
          for (int fila = 0; fila < 8 - 1; fila++) {
          // Realiza el XOR de la fila actual con la siguiente
            for (int columna = 0; columna < 3; columna++) {
              nuevaHT2[fila + 1][columna] ^= nuevaHT2[fila][columna];
              // Almacena el resultado de la última operación XOR en el vector "codigo"
              if (fila == 8 - 2) {
                sindrome2[columna] = static_cast<bool>(nuevaHT2[fila + 1][columna]);
              }
            }
          }

          int erroract2 = 0;
          Serial.println("Sindrome nuevo");
          //Impresion del sindrome
            int bandera2 = 0;
            for (int i = 0; i < 3; i++) {
              Serial.print(sindrome2[i]);
                Serial.print(" ");
                if(sindrome2[i] != 0) {
                  bandera2++;
                } if(i == 2 && bandera2 != 0) {
                    Serial.println(" ERROR DETECTADO");
                    //errores++;
                    erroract2 = 1;
                    //Serial.println();
                }
            }
            Serial.println();

            if(erroract2 != 0) {
              Serial.print("No se pudo corregir el ERROR...");
              Serial.println();
            } else {
              Serial.print("ERROR CORREGIDO!!!");
            }

            Serial.println();

          //

        } else { //Fin encuentro indice
            Serial.println(" - Imposible correguir, no se encuentra el sindrome...");       
          }
      }
    }
    
  }
  
  delay(1000);
  
}
