/*
 * ESP8266 - LED Intermitente com Wi-Fi por um Botão
 * Conecta na rede Wi-Fi e acende um LED piscando
 * enquanto o botão estiver pressionado.
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

// Configurações da sua rede Wi-Fi
const char* ssid = "virus.exe";
const char* password = "150051784898";

// Pinos utilizados
const int ledPin = D2;      // GPIO4
const int buttonPin = D5;  // GPIO14

void handleRoot() {
  if (digitalRead(buttonPin) == LOW) {  // botão pressionado
    server.send(200, "text/html",
                "<html><head><meta http-equiv='refresh' content='0.2'></head>"
                "<body><h1>ESP8266</h1>"
                "<p>LED ACESO!</p></body></html>");
  } else {
    server.send(200, "text/html",
                "<html><head><meta http-equiv='refresh' content='0.2'></head>"
                "<body><h1>ESP8266</h1>"
                "<p>LED APAGADO!</p></body></html>");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Botão com pull-up interno

  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
  Serial.println("Servidor HTTP iniciado!");
}

void loop() {
  server.handleClient();

  if (digitalRead(buttonPin) == LOW) {  // botão pressionado
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);  // apaga ao soltar
  }
}
