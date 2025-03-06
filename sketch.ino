#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);
// set the LCD address to 0x27 for a 16 chars and 2 line display

float distanceToHeadInCm;
float heightInCm;
float heightInInches;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
	pinMode(triggerPin, OUTPUT);  // Clear the trigger
	digitalWrite(triggerPin, LOW);
	delayMicroseconds(2);
	// Sets the trigger pin to HIGH state for 10 microseconds
	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPin, LOW);
	pinMode(echoPin, INPUT);
	// Reads the echo pin, and returns
	// the sound wave travel time in microseconds
	return pulseIn(echoPin, HIGH);
}

void setup()
{
  Serial.begin(9600);
  lcd.init();	// initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("--> Distance <--");
	delay(3000);
	lcd.clear();
}

void loop()
{
  distanceToHeadInCm = 0.0344/2 * readUltrasonicDistance(3, 2);
	heightInCm = 2000 - distanceToHeadInCm;
	heightInInches = (heightInCm / 2.54);
  /*
	Serial.print("Inches ");
	Serial.print(inches, 1);
	Serial.print("\t");
  Serial.print("cm ");
	Serial.println(cm, 1);
	*/
	lcd.setCursor(0,0);
	lcd.print("Inches");
	lcd.setCursor(4,0);
	lcd.setCursor(12,0);
	lcd.print("cm");
	lcd.setCursor(1,1);
	lcd.print(heightInInches, 1);
	lcd.setCursor(11,1);
	lcd.print(heightInCm, 1);
	lcd.setCursor(14,1);
	delay(2000);
	lcd.clear();
}
