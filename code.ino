int entrySensor = 12;     // IR Sensor 1 - Entry
int exitSensor = 13;      // IR Sensor 2 - Exit

int led1 = 4;             // Parking Slot 1
int led2 = 3;             // Parking Slot 2

int buzzer1 = 6;
int buzzer2 = 5;

bool slot1 = false;
bool slot2 = false;

void setup() {
  Serial.begin(9600);
  pinMode(entrySensor, INPUT);
  pinMode(exitSensor, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(buzzer1, LOW);
  digitalWrite(buzzer2, LOW);

  Serial.println("System ready. All slots empty.");
}

void loop() {
  int entryValue = digitalRead(entrySensor);
  int exitValue = digitalRead(exitSensor);

  // === Entry ===
  if (entryValue == LOW) {  // Car detected entering
    if (!slot1) {
      slot1 = true;
      digitalWrite(led1, HIGH);
      buzz(buzzer1);
      Serial.println("Car entered. Slot 1 occupied.");
    }
    else if (!slot2) {
      slot2 = true;
      digitalWrite(led2, HIGH);
      buzz(buzzer2);
      Serial.println("Car entered. Slot 2 occupied.");
    } else {
      Serial.println("Parking full! Cannot enter.");
    }
    delay(1000);  // Wait to avoid multiple readings
  }

  // === Exit ===
  if (exitValue == LOW) {  // Car detected exiting
    if (slot2) {
      slot2 = false;
      digitalWrite(led2, LOW);
      buzz(buzzer2);
      Serial.println("Car exited. Slot 2 freed.");
    }
    else if (slot1) {
      slot1 = false;
      digitalWrite(led1, LOW);
      buzz(buzzer1);
      Serial.println("Car exited. Slot 1 freed.");
    } else {
      Serial.println("Parking already empty!");
    }
    delay(1000);
  }

  delay(200);  // Small delay to stabilize readings
}

void buzz(int pin) {
  digitalWrite(pin, HIGH);
  delay(500);
  digitalWrite(pin, LOW);
}
