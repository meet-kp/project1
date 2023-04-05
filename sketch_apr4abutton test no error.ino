#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>

const char* ssid = "mkp";
const char* password = "11111111";
const char* websocket_server = "49, 249, 200, 132";

WebSocketsClient webSocket;

const int BUTTON_PIN = D1;
int buttonState = LOW;
int lastButtonState = LOW;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Replace "websocket_server" with the hostname of the WebSocket server you are trying to connect to
  const char* websocket_server = "49, 249, 200, 132, 3000"; 

  webSocket.begin(websocket_server, 3000, "/"); // Change the port number and path if necessary
  


  webSocket.setExtraHeaders("Authorization: 1234567890");
  webSocket.setExtraHeaders("data:test,test123,station");
 
 webSocket.onEvent(webSocketEvent);
}




// void setup() {
//   pinMode(BUTTON_PIN, INPUT);
//   Serial.begin(115200);
//   WiFi.begin(ssid, password);
//   Serial.print("Connecting to WiFi");
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.print(".");
//   }
//   Serial.println();
//   Serial.print("Connected to WiFi: ");
// //   Serial.println(ssid);


//   // webSocket.begin(websocket_server);
//   webSocket.begin(websocket_server);
//   // webSocket.begin(websocket_server.c_str());

//   webSocket.onEvent(webSocketEvent);
// }

void loop() {
  buttonState = digitalRead(BUTTON_PIN);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      // button pressed, send message to server
      JsonObject message;
      message["button"] = "pressed";
      String json;
      serializeJson(message, json);
      webSocket.sendTXT(json);
    }
  }
  lastButtonState = buttonState;
  webSocket.loop();
}

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    // case WStype_DISCONNECTED:
    //   Serial.println("Disconnected from WebSocket server");
    //   break;
    case WStype_CONNECTED:
      Serial.println("Connected to WebSocket server");
      break;
    case WStype_TEXT:
      Serial.println("Received message from WebSocket server:");
      Serial.println((char*)payload);
      break;
  }
}
