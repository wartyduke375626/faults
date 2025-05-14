/**
* Original code from CTF challenge
* (2023-03-18) taken from:
* https://blog.securitybits.io/2019/06/voltage-glitching-on-the-cheap/
*/

int incomingByte = 0;
char b[5];

int powerPin = 2;
int glitchDelay = 0;


void setup() {
    Serial.begin(19200);
    Serial.println("Arduino is ready");
    
    pinMode(powerPin, OUTPUT);
    
    digitalWrite(powerPin, HIGH);
    delay(5000);
    
    Serial.println("Gliching is ready");
}

void glitch() {
    int waste = 0;
    
    digitalWrite(powerPin, LOW);
    for (int i = 0; i<glitchDelay; i++) { waste++; }
    digitalWrite(powerPin, HIGH);
    
    glitchDelay +=10;
    Serial.println();
    Serial.print("Glich Delay set to: ");
    Serial.print(glitchDelay);
    Serial.println();
}

void loop() {
    for (int i = 0; i<200;i++){
        if (Serial.available() > 0) {
            // read the incoming byte:
            incomingByte = Serial.read();
            Serial.print(char(incomingByte));
        }
    }
    
    delay(1000);
    glitch();
}