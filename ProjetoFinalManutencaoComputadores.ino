// ###################
// ### Bibliotecas ###
// ###################

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

// Definindo LCD

hd44780_I2Cexp lcd;

// valores sensor de luminosidade
const int val = 34;  // pino analogico 1 ou gpio34
int potValue = 0;    // armazena valor do pino

// Valores umidade solo
const int ligasensor = 13;  // Liga e desliga o sensor para evitar corrosão do metal
const int pinumidade = 35;  // pino analogico 2 ou gpio35
int umidadevalor = 0;       // armazena valor umidade

// valores temperatura

void setup() {
  //pinos umidade
  pinMode(ligasensor, OUTPUT);
  pinMode(pinumidade, INPUT);

  Serial.begin(115000);

  // Inicia LCD
  lcd.begin(20, 4);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);

  // Resolução de leitura analógica
  analogReadResolution(12);
}

void loop() {
  Lerumidadesolo(); // void umidade solo
  Leituradeluminosidade();  // Void de leitura da quantidade de luz, mostrando também no display (alterarei mais tarde para um void separado)
}