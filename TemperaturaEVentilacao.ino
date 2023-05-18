void temperaturaeventilacao() {
  grau = analogRead(temperatura);
  TF = grau * 0.1075268817204301;

  Serial.print("A temperatura é de: ");
  Serial.print(TF);
  Serial.println("º");
  Serial.println(velocidademotor);

  if (TF >= 0 || TF <= 25 || TF < 0) {
    analogWrite(velocidademotor, 0);
  }
  if (TF >= 26 || TF <= 30) {
    analogWrite(velocidademotor, 125);
  }
  if (TF >= 31) {
    analogWrite(velocidademotor, 255);
  }
}