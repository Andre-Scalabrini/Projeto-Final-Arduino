void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}