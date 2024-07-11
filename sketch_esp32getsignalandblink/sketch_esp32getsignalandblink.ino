#include <esp_now.h>
#include <WiFi.h>

typedef struct test_struct {
  int x;
  int y;
} test_struct;

test_struct myData;
const int ledPin = 2;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  digitalWrite(ledPin, HIGH); 
  delay(500);                 
  digitalWrite(ledPin, LOW);  
  delay(500);  
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("x: ");
  Serial.println(myData.x);
  Serial.print("y: ");
  Serial.println(myData.y);
  Serial.println();
}
 
void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

  pinMode(ledPin, OUTPUT);
}
 
void loop() {

}



