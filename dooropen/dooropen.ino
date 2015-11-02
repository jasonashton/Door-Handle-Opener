#include <SPI.h>
#include <MFRC522.h>

//CardReader Constants
#define RST_PIN 9 
#define SS_PIN 10

//Motor Drive Contants
#define ENABLE_PIN 2
#define STEP_PIN 3
#define DIR_PIN 4

String cards[2] = {"15318785229", "103113543"}; //Accepted Keys
byte cardread[4]; //To store read key

//CardReader Initialize
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
MFRC522::MIFARE_Key key;

void setup(){
  Serial.begin(9600);
  pinMode(ENABLE_PIN,OUTPUT); // Enable
  pinMode(STEP_PIN,OUTPUT); // Step
  pinMode(DIR_PIN,OUTPUT); // Dir
  digitalWrite(ENABLE_PIN,HIGH); // Set Enable off
  
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
    
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size); //card to cardread


    //If they're the same print match
    if(compare_arrays(cards, cardread)){
      motorDrive();
    }
    
    
}

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        cardread[i] = buffer[i];
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

void motorDrive(){
  digitalWrite(ENABLE_PIN, LOW);
  digitalWrite(DIR_PIN, HIGH);
    
  for(int i=0; i<=200; i++){
    digitalWrite(STEP_PIN,HIGH); // Output high
    delay(5); // Wait
    digitalWrite(STEP_PIN,LOW); // Output low
    delay(5); // Wait
  }
  
  digitalWrite(DIR_PIN, LOW);
  
  for(int i=0; i<=200; i++){
    digitalWrite(STEP_PIN,HIGH); // Output high
    delay(5); // Wait
    digitalWrite(STEP_PIN,LOW); // Output low
    delay(5); // Wait
  }
  
  digitalWrite(ENABLE_PIN, HIGH);
  }


