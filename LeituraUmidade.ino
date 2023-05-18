void Lerumidadesolo() {
  umidadevalor = analogRead(pinumidade);

  digitalWrite(ligasensor, HIGH);
  delay(10);
  Serial.println(umidadevalor);

  digitalWrite(ligasensor, LOW);
  delay(10);
}