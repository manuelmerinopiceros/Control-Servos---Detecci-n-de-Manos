#include <Servo.h>

Servo servothumb;
Servo servoindex;
Servo servomiddle;
Servo servoring;
Servo servopinky;

// Variables para los valores recibidos
int servoPinky = 0, servoRing = 0, servoMiddle = 0, servoIndex = 0, servoThumb = 0;

void setup() {
  Serial.begin(9600);

  servothumb.attach(9);
  servoindex.attach(10);
  servopinky.attach(11);
  servoring.attach(12);
  servomiddle.attach(13);

  Serial.println("Listo. Envia datos como: [1, 0, 0, 0, 0]");
}

void loop() {
  receiveData();

  // Actualizar servos según valores
  servopinky.write(servoPinky == 1 ? 180 : 0);
  servoring.write(servoRing == 1 ? 180 : 0);
  servomiddle.write(servoMiddle == 1 ? 180 : 0);
  servoindex.write(servoIndex == 1 ? 180 : 0);
  servothumb.write(servoThumb == 1 ? 180 : 0);
}

/**
 * Leer una cadena como [1, 0, 0, 0, 0] desde el puerto serial,
 * y actualizar los valores servoPinky ... servoThumb
 */
void receiveData() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');  // leer hasta salto de línea
    input.trim();  // eliminar espacios extra

    // Validar formato
    if (input.startsWith("[") && input.endsWith("]")) {
      input.remove(0, 1);                      // eliminar '['
      input.remove(input.length() - 1, 1);     // eliminar ']'
      input.replace(" ", "");                  // eliminar espacios

      // Dividir por comas
      int values[5] = {0, 0, 0, 0, 0};
      int index = 0;
      char buf[32];
      input.toCharArray(buf, sizeof(buf));
      char *token = strtok(buf, ",");

      while (token != NULL && index < 5) {
        values[index++] = atoi(token);
        token = strtok(NULL, ",");
      }

      // Asignar si hay 5 valores válidos
      if (index == 5) {
        servoPinky  = values[0];
        servoRing   = values[1];
        servoMiddle = values[2];
        servoIndex  = values[3];
        servoThumb  = values[4];

        // Mostrar en Serial lo recibido
        Serial.print("Recibido: ");
        Serial.print(servoPinky);  Serial.print(" ");
        Serial.print(servoRing);   Serial.print(" ");
        Serial.print(servoMiddle); Serial.print(" ");
        Serial.print(servoIndex);  Serial.print(" ");
        Serial.println(servoThumb);
      } else {
        Serial.println("Error: se esperaban 5 valores");
      }
    } else {
      Serial.println("Formato incorrecto. Usa: [1, 0, 0, 0, 0]");
    }
  }
}
