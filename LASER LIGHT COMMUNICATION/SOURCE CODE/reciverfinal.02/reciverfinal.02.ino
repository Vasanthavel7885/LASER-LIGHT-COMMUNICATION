const int ldrPin = A0;  // LDR pin
const int threshold = 500;  // Adjust based on lighting conditions
#define START_SEQUENCE 0b10101010   // Synchronization pattern
#define BIT_DELAY 600

void setup() {
    Serial.begin(9600);
}

void loop() {
    if (detectStartSequence()) {  
        delay(20);  // Small delay before receiving data
        char receivedChar = receiveData();
        Serial.print("Received: ");
        Serial.println(receivedChar);
    }
}

bool detectStartSequence() { 
    while (true) {  
        while (analogRead(ldrPin) < threshold);  // Wait for signal
        
        Serial.print("Detecting Start Sequence: ");
        
        for (int i = 7; i >= 0; i--) {
            delay(BIT_DELAY / 2);  // Allow LDR to settle before reading
            int bitState = (analogRead(ldrPin) > threshold) ? 1 : 0;
            Serial.print(bitState);
            
            int expectedBit = (START_SEQUENCE >> i) & 1;  
            
            if (bitState != expectedBit) { 
                Serial.println(" ❌ Noise Detected! Restarting...");
                return false; 
            }
            
            delay(BIT_DELAY / 2);
        }
        
        Serial.println(" ✅ Start Sequence Detected!");
        return true;
    }
}

char receiveData() {
    int byteData = 0;
    for (int i = 8; i >= 0; i--) {
        delay(BIT_DELAY / 2);  // Allow LDR to settle
        int bitState = (analogRead(ldrPin) > threshold) ? 0 : 1;
        Serial.print(bitState);
        byteData |= (bitState << i);
        delay(BIT_DELAY / 2);
    }
    Serial.println();
    return (char)byteData;
}
