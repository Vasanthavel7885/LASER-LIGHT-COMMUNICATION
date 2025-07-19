
const int ledPin = 13; // LED as transmitter
#define START_SEQUENCE 0b10101010 // Synchronization pattern
#define BIT_DELAY 600 // Delay between bits in milliseconds

void setup() {
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);

    // Blink LED once to indicate startup
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
}

void loop() {
    if (Serial.available()) {
        char data = Serial.read();  // Read character from serial
        Serial.print("Sending: ");
        Serial.println(data);
        
        sendStartSequence(); // Send synchronization bits
        sendData(data);    // Send actual data immediately after
    }
}

void sendStartSequence() {
  delay(600);
    Serial.print("Start Sequence: ");
    for (int i = 7; i >= 0; i--) {
        int bitState = ((START_SEQUENCE >> i) & 1);
        Serial.print(bitState);
        digitalWrite(ledPin, bitState);
        delay(BIT_DELAY);
    }
    digitalWrite(ledPin, LOW); 
    Serial.print(" "); // Ensure no extra delay in output formatting
}

void sendData(char data) {
    for (int i = 7; i >= 0; i--) {
        int bitState = ((data >> i) & 1);
        Serial.print(bitState);
        digitalWrite(ledPin, bitState);
        delay(BIT_DELAY);
    }
    Serial.print(" "); // Remove newline to prevent extra spacing between transmissions
    digitalWrite(ledPin, LOW);
}
