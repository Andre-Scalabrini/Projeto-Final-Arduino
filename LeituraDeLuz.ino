void Leituradeluminosidade() {

  potValue = analogRead(val);
  Serial.println(potValue);
  delay(100);

  if (val <= 600) {
    lcd.print("Tá com luz pra caralho");
  }

  if (val >= 601 && val <= 799) {
    lcd.print("Tá com luz um pouco de luz");
  }

  if (val >= 800 && val <= 999) {
    lcd.print("Tá com luz");
  }

  if (val >= 1000) {
    lcd.print("Tá quase sem luz");
  }
}