#include <ESP32SPISlave.h>

ESP32SPISlave slave;

const int BUFFER_SIZE = 32;
uint8_t rx_buf[BUFFER_SIZE] = {0};
uint8_t tx_buf[BUFFER_SIZE] = "Hi RPi, I am ESP32!";

void setup() {
  Serial.begin(115200);
  delay(1000);

  slave.setDataMode(SPI_MODE0);
  slave.setQueueSize(1);
  slave.begin();  // uses HSPI by default

  Serial.println("ESP32 SPI Slave ready");
}

void loop() {
  if (slave.hasTransactionsCompletedAndAllResultsHandled()) {
    memset(rx_buf, 0, BUFFER_SIZE);
    slave.queue(tx_buf, rx_buf, BUFFER_SIZE);
    slave.trigger();
  }

  if (slave.hasTransactionsCompletedAndAllResultsReady(1)) {
    Serial.print("Received from RPi: ");
    Serial.println((char*)rx_buf);
  }
}
