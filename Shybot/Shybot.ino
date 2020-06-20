#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Rotation Servo
#include <Servo.h>
int servoPin = 9;
Servo servo;  
int servoAngle = 0;   // servo position in degrees

const int pingPin = 7; // distance sensor

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin); // servo

  /* lcdscreen */
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(200); // Pause for 2 seconds
}

void loop() {
  long duration, inches, cm;
  
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print(" cm");
  Serial.println();
  delay(100);
  
  if (cm < 55){
    sad();
    for(servoAngle = 0; servoAngle < 180; servoAngle++){                                  
      servo.write(servoAngle);              
      delay(60);                  
    }
  }
  else{    
    happy();
  }
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void happy(void) {
  display.clearDisplay();
  
  display.fillRect(40, 25, 40, 8, SSD1306_WHITE);
  display.fillRect(30, 20, 15, 8, SSD1306_WHITE);
  display.fillRect(20, 15, 15, 8, SSD1306_WHITE);
  display.fillRect(75, 20, 15, 8, SSD1306_WHITE);
  display.fillRect(85, 15, 15, 8, SSD1306_WHITE);

  display.display(); // Update screen with each newly-drawn rectangle
}


void sad(void) {
  display.clearDisplay();

  display.fillRect(40, 15, 40, 8, SSD1306_WHITE);
  display.fillRect(30, 20, 15, 8, SSD1306_WHITE);
  display.fillRect(20, 25, 15, 8, SSD1306_WHITE);
  display.fillRect(75, 20, 15, 8, SSD1306_WHITE);
  display.fillRect(85, 25, 15, 8, SSD1306_WHITE);

  display.display(); // Update screen with each newly-drawn rectangle
}
