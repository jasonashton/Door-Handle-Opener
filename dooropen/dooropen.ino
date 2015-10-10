#include <SPI.h>
#include "./MFRC522.h"

//CardReader Constants
#define RST_PIN 9 
#define SS_PIN 10

String cards[2] = {"15318785229", "103113543"}; //Accepted Keys
byte cardread[4]; //To store read key

//CardReader Initialize
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
MFRC522::MIFARE_Key key;

void setup(){
  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max); //Set Max Gain ?working?
}

void loop() {
  // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent())
        return;
        
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial())
        return;
    
    // Show some details of the PICC (that is: the tag/card)
    Serial.print(F("Card UID: "));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();


    //If they're the same print match
    if(compare_arrays(cards, cardread)){
      Serial.println("Match!");
    }
    
    Serial.println();
    
}

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        cardread[i] = buffer[i];
        Serial.print(cardread[i]);
    }
}

/**
 * Compares two cards
 */
boolean compare_arrays(String master[], byte readcard[]){
  String card_to_string;

  //convert the read uid to a string
  for(byte i=0;i<4;i++){
    card_to_string += readcard[i];
  }
  
  //return true if they match, cycles through each available "correct" card
  for(byte i=0;i<2;i++){
    if(master[i] == card_to_string){
      return true;
    }
  }
   return false;
}

