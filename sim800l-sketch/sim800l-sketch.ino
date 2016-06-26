 /**
  * SIM800L SMS Gateway
  * by Marcin Borkowski <marborkowski@gmail.com>
  * ------------------------------------------------------------
  * 
  * You can use this arduino sketch
  * to send and receive SMS messages using simple SIM800L board.
  * 
  * WARNING: The input voltage should not be higher than 4.7V
  * 
  * Aliexpress.com:
  * http://www.aliexpress.com/item/1pcs-Smallest-SIM800L-GPRS-GSM-Module-MicroSIM-Card-Core-BOard-Quad-band-TTL-Serial-Port/32664202170.html
  */
#include <SoftwareSerial.h>

static int BAUD_RATE = 9600;
const byte SIM800L_RX_PIN = 8;
const byte SIM800L_TX_PIN = 7;

SoftwareSerial SMSGateway(SIM800L_RX_PIN, SIM800L_TX_PIN);

void setup()
{
  delay(1000);
  
  SMSGateway.begin(BAUD_RATE);
  Serial.begin(BAUD_RATE);

  while(!Serial || !SMSGateway);

  Serial.println("Serial gateway ready.");
  
  Serial.println("Configuring incoming SMS policy...");
  SMSGateway.write("AT+CNMI=2,2,0,0,0\r");
  delay(1000);

  Serial.println("Selecting TE character set.");
  SMSGateway.write("AT+CSCS=\"GSM\"\r");
  delay(1000);

  Serial.println("Selecting ASCII as a text mode");
  SMSGateway.println("AT+CMGF=1");
  delay(1000);
}

void sendMessage() {
  SMSGateway.println("AT+CMGF=1");
  delay(100);
  
  SMSGateway.println("AT+CMGS=\"+48697000000\"");
  delay(100);
  
  SMSGateway.println("Random Message #" + String(random(100)));
  delay(100);
  
  SMSGateway.write(0x1A);
  delay(1000);
  
  SMSGateway.println("AT");
}

void incomingCommands() {
  if (Serial.available() > 0) {
    switch(Serial.read()) {
      case 's':
        sendMessage();
        break;
    }
  }
}

void printOutput() {
  if (SMSGateway.available() > 0) {
    Serial.write(SMSGateway.read());
  }  
}

void loop()
{
  printOutput();
  incomingCommands();
}
