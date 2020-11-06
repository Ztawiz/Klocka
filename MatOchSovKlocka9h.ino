#define buzzer 9
#define dataPin 6
#define latchPin 7
#define CLKpin 8
#define readPin 2
#define restPin 4
const int countTime[33] = {25, 5, 25, 5, 25, 5, 25, 5, 25, 15, 25, 5, 25, 5, 25, 5, 25, 45, 25, 5, 25, 5, 25, 5, 25, 15, 25, 5, 25, 5, 25, 5, 25};
const int siffror[10] = {252, 96, 218, 242, 102, 182, 190, 224, 254, 230};

void signs(int i);
void countDown(int index);

void setup() {
  delay(1000);
  pinMode(buzzer, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(CLKpin, OUTPUT);
  pinMode(readPin, OUTPUT);
  pinMode(restPin, OUTPUT);
  
  Serial.begin(9600);
  
}

void loop() {

   for (int i = 0; i <= 32; i++){

    
    signs(i);
    tone(buzzer, 3000);
    delay(500);
    noTone(buzzer);
    countDown(countTime[i]);
    tone(buzzer, 3000);
    delay(500);
    noTone(buzzer);
   }

   do {
    delay(1000);
   } while (1);
   
}

  
void signs(int i){
  if (i % 2){                             // Om i är jämn ska LÄS vara tänd, annars ska RAST vara tänd.
      digitalWrite(readPin, LOW);
      digitalWrite(restPin, HIGH);
      Serial.println("Läs släcks, rast tänds");
    } else {
        digitalWrite(readPin, HIGH);
        digitalWrite(restPin, LOW);
        Serial.println("Läs tänds, rast släcks");
    }
}

void countDown(int index){
  int tid = index*60;
  int startTid = millis()/1000;       // Starttid för intervallet.

  do {
  
    int tioMin = (tid / 600);           // antal tiominuter som intervallet omfattar.
    tid = (tid - (tioMin*600));         // Subtrahera detta antar sekunder från det totala.
    int enMin = (tid / 60);             // Antal minuter
    tid = (tid - (enMin*60));
    int tioSek = (tid / 10);
    tid = (tid - (tioSek*10));
    int enSek = tid;

    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, CLKpin, MSBFIRST, siffror[enSek]);
    shiftOut(dataPin, CLKpin, MSBFIRST, siffror[tioSek]);
    shiftOut(dataPin, CLKpin, MSBFIRST, siffror[enMin]);
    shiftOut(dataPin, CLKpin, MSBFIRST, siffror[tioMin]);
    digitalWrite(latchPin, HIGH);
    //delay(50);                                               // Delay för att inte printa för ofta.

   
    Serial.print(tioMin);
    Serial.print(enMin);
    Serial.print(":");
    Serial.print(tioSek);
    Serial.println(enSek);

    tid = (index*60) - ((millis()/1000) - startTid);
    Serial.print("Tid i sekunder: ");
    Serial.println(tid);


  } while (tid >= 0);
}
