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
int temperatura = 32;  // pino de entrada analogica do sensor LM35 no arduino

int grau = 0;  // descreve o grau a ser medido pelo sensor
int TF = 0;    // temperatura final

const int velocidademotor = 33;

//config wifi e server, ignorem

#ifdef ESP8266
#include <ESP8266WiFi.h>  // Pinos para esp8266 MCU
#else
#include <WiFi.h>
#endif

#include <PubSubClient.h>
#include <WiFiClientSecure.h>

//---- WiFi settings
const char* ssid = "Techmax 2";
const char* password = "Automotivo#23";

//---- MQTT Broker settings
const char* mqtt_server = "9a658407ed894e5480f0b771edbc86c6.s1.eu.hivemq.cloud";  // Trocar por url gerada
const char* mqtt_username = "minicurso";                                          // usuário gerado
const char* mqtt_password = "Minicurso23";                                        // senha do usuário gerado
const int mqtt_port = 8883;

WiFiClientSecure espClient;  // Para conexão sem senha, comente essa linha e descomente a linha sob ela
//WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;

#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

int sensor1 = 0;
float sensor2 = 0;
int sensor3 = 0;
int command1 = 0;

const char* sensor1_topic = "sensor1";
const char* sensor2_topic = "sensor2";
const char* sensor3_topic = "sensor3";

const char* command1_topic = "command1";
const char* command2_topic = "command2";

static const char* root_ca PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)EOF";  //só nao mexe

// CONFIG DESPERTADOR
#include "time.h"
const char* ntpServer = "br.pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = -10800;

void setup() {
  //pinos umidade
  pinMode(ligasensor, OUTPUT);
  pinMode(pinumidade, INPUT);
  printLocalTime();
  Serial.begin(115000);
  while (!Serial) delay(1);
  setup_wifi();
  pinMode(BUILTIN_LED, OUTPUT);  // Inicializa o LED interno

  //vai pegar o horário no servidor
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

#ifdef ESP8266
  espClient.setInsecure();
#else  // para o ESP32
  espClient.setCACert(root_ca);  // habbilite essa linha e o certificado para conexão segura
#endif

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // Inicia LCD
  lcd.begin(20, 4);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);

  // Resolução de leitura analógica
  analogReadResolution(12);
  //temperatura
  pinMode(temperatura, INPUT);

  // motor velocidade
  pinMode(velocidademotor, OUTPUT);
}

void loop() {
 
  Lerumidadesolo();          // void umidade solo
  Leituradeluminosidade();   // Void de leitura da quantidade de luz, mostrando também no display (alterarei mais tarde para um void separado)
  temperaturaeventilacao();  // void temperatura

 // if (!client.connected()) reconnect();
 // client.loop();

  //---- exemplo: publicando valor dos sensores a cada 5 segundos
  unsigned long now = millis();
  if (now - lastMsg > 10) {
    lastMsg = now;
    sensor1 = potValue;      // Colocar o valor dos sensores aqui
    sensor2 = umidadevalor;  // Colocar o valor dos sensores aqui
    sensor3 = TF;
    publishMessage(sensor1_topic, String(sensor1), true);
    publishMessage(sensor2_topic, String(sensor2), true);
    publishMessage(sensor3_topic, String(sensor3), true);
  }
}
