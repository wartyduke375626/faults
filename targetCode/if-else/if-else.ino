#define LED_PIN 12

bool test = 1;

void setup() {
    Serial.begin(19200);
    pinMode(LED_PIN, OUTPUT);
    Serial.println("\nATMega328P reset!");
    delay(1000);
}


void loop() {
    while(test) {
        digitalWrite(LED_PIN, LOW);
        Serial.print("$");
        digitalWrite(LED_PIN, HIGH);
    }
    while(1) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("Unlocked!");
        delay(2000);
    }
}