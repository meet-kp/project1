//global boolean varialable
bool relayStatus = false;







//checking the elapsed time using a timestamp variable.

if(now - messageTimestamp > 20000) {
    messageTimestamp = now;
    // Send update on relay status to the server
    DynamicJsonDocument doc(1024);
    JsonArray array = doc.to<JsonArray>();
    array.add("relay_status");
    JsonObject param1 = array.createNestedObject();
    param1["status"] = relayStatus;
    String output;
    serializeJson(doc, output);
    socketIO.sendEVENT(output);
}





   
//server to websocket //




#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

const char* ssid = "your-ssid";
const char* password = "your-password";
const char* server_address = "your-websocket-server-address";

WebSocketsClient webSocket;
int ledPin = 13;
String message;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  webSocket.begin(server_address);
  webSocket.onMessage(onMessage);
}

void loop() {
  webSocket.loop();
}

void onMessage(const uint8_t* payload, size_t length) {
  message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);
  if (message == "1") {
    digitalWrite(ledPin, HIGH);
  } else if (message == "0") {
    digitalWrite(ledPin, LOW);
  }
}