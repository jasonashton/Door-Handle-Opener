#include <SPI.h>
#include <MFRC522.h>
#include <AccelStepper.h>

//CardReader Constants
#define RST_PIN 9 
#define SS_PIN 10

String cards[2] = {"15318785229", "103113543"}; //Accepted Keys
byte cardread[4]; //To store read key

//Motor Constants
#define HALFSTEP 8

// Motor pin definitions
#define motorPin1  3     // IN1 on the ULN2003 driver 1
#define motorPin2  4     // IN2 on the ULN2003 driver 1
#define motorPin3  5     // IN3 on the ULN2003 driver 1
#define motorPin4  6     // IN4 on the ULN2003 driver 1

//CardReader Initialize
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
MFRC522::MIFARE_Key key;

//Motor Initialize
//pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

void setup(){
  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max); //Set Max Gain ?working?

  stepper1.setMaxSpeed(1000.0); //Max Speed
  stepper1.setAcceleration(100.0); //100 steps/s^2
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
      turn_motor();
    }
    //stepper1.run(); //required to turn motor
    
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

void turn_motor(){
  Serial.println("Moving!");
  stepper1.move(4076); //4096 is what it SHOULD be
  stepper1.runToPosition();
  delay(2000);
  stepper1.move(-4076);
  stepper1.runToPosition();
}

