void temperaturaeventilacao() {
  grau = analogRead(temperatura);
  TF = grau * 0.1075268817204301;

  Serial.print("A temperatura é de: ");
  Serial.print(TF);
  Serial.println("º");
  Serial.println(velocidademotor);

  if ((TF >= 0 || TF <= 16 || TF < 0) && controlevelocidademanual == 0) {
    analogWrite(velocidademotor, 0);
  }
  if ((TF >= 17 || TF <= 20 ) && controlevelocidademanual == 0) {
    analogWrite(velocidademotor, 25);
  }
  if ((TF >= 21 || TF <= 23 ) && controlevelocidademanual == 0) {
    analogWrite(velocidademotor, 50);
  }
  if ((TF >= 24 || TF <= 26 ) && controlevelocidademanual == 0) {
    analogWrite(velocidademotor, 75);
  }
  if ((TF >= 27 || TF <= 29 ) && controlevelocidademanual == 0) {
    analogWrite(velocidademotor, 100);
  }
  if ((TF >= 30 || TF <= 35 ) && controlevelocidademanual == 0) {
    analogWrite(velocidademotor, 150);
  }
  if (TF >= 36 && controlevelocidademanual == 0) {
    analogWrite(velocidademotor, 255);
  }
}