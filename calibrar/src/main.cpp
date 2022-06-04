#include "Arduino.h"
#include "HX711.h"

#define LOADCELL_DOUT_PIN  23
#define LOADCELL_SCK_PIN  19

HX711 scale;

float calibration_factor = -35130; 

void setup() {
  Serial.begin(115200);
  Serial.println("Inicio calibración, retire cualquier peso del dispositivo");
  Serial.println("Una vez iniciadas las lecturas, coloque un peso conocido en el dispositivo");
  Serial.println("Presione + y - para ajustar el factor de calibración");
  delay(3000);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare(); 

}

void loop() {

  scale.set_scale(calibration_factor);

  Serial.print("Lectura:: ");
  Serial.print(scale.get_units(), 5);
  Serial.print(" kg"); 
  Serial.print(" Factor calibración: ");
  Serial.println(calibration_factor);
  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+')
      calibration_factor += 10;
    else if(temp == '-')
      calibration_factor -= 10;
  }
}