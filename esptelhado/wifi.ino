//==========================================
void setup_wifi() {
  delay(10);
  Serial.print("\nConectando na rede:  ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());
  Serial.println("\nWiFi conectedo\nIP da rede: ");
  Serial.println(WiFi.localIP());
}


//=====================================
void reconnect() {
  // Loop até conectar
  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT...");
    String clientId = "ESP32Client-";  // Create a random client ID
    clientId += String(random(0xffff), HEX);
    // Quando conecta
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("conectado");

      client.subscribe(command1_topic);  // adiciona os tópicos aqui
      client.subscribe(command2_topic);

    } else {
      Serial.print("falha, reconectando=");
      Serial.print(client.state());
      Serial.println(" tente novamente em 5 segundos");  // Aguarda 5 seg antes de reiniciar
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String incommingMessage = "";
  for (int i = 0; i < length; i++) incommingMessage += (char)payload[i];

  Serial.println("Mensagem recebida [" + String(topic) + "]" + incommingMessage);

  //--- checa mensagem que foi recebida
  if (strcmp(topic, command1_topic) == 0) {
    if (incommingMessage.equals("1")) digitalWrite(BUILTIN_LED, LOW);  //  LED on
    else digitalWrite(BUILTIN_LED, HIGH);                              //  LED off
  }

  //  checa outros comandos
    else  if( strcmp(topic,command2_topic) == 0){
     if (incommingMessage.equals("1")) { 
       Serial.println("opa, tem mensagem aqui");
      } 
  }
  
}

//======================================= enviando como string
void publishMessage(const char* topic, String payload, boolean retained) {
  if (client.publish(topic, payload.c_str(), true))
    Serial.println("Mensagem enviada [" + String(topic) + "]: " + payload);
}