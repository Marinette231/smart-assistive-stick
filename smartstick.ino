#include <SoftwareSerial.h> 
#include <TinyGPS++.h> 
 
// Ultrasonic pins 
#define trig1 A0 
#define echo1 A1 
#define trig2 A2 
#define echo2 A3 
 
// Output/Input 
#define buzzer 5 
#define button 6 
 
// Modules 
SoftwareSerial gpsSerial(11, 10); 
SoftwareSerial gsmSerial(3, 2); 
 
TinyGPSPlus gps; 
 
// Variables 
int distance1, distance2; 
String latitude = "0"; 
String longitude = "0"; 
 
bool buttonPressed = false; 
 
// SETUP 
void setup() 
{ 
  pinMode(trig1, OUTPUT); 
  pinMode(echo1, INPUT); 
  pinMode(trig2, OUTPUT); 
  pinMode(echo2, INPUT); 
 
  pinMode(buzzer, OUTPUT); 
  pinMode(button, INPUT_PULLUP); 
 
  Serial.begin(9600); 

  gpsSerial.begin(9600); 
  gsmSerial.begin(9600); 
 
  Serial.println("System Ready"); 
} 
 
//LOOP  
void loop() 
{ 
  // STOP GPS (avoid interference) 
  gpsSerial.end(); 
 
  // Read stable distances 
  distance1 = stableDistance(trig1, echo1); 
  delay(50); 
  distance2 = stableDistance(trig2, echo2); 
 
  //  Buzzer logic 
  if ((distance1 > 2 && distance1 < 50) || (distance2 > 2 && distance2 < 50)) 
  { 
    digitalWrite(buzzer, HIGH); 
    Serial.println("OBSTACLE DETECTED"); 
  } 
  else 
  { 
    digitalWrite(buzzer, LOW); 
  } 
 
  // Restart GPS 
  gpsSerial.begin(9600); 
 
  // Read GPS once per second 
  static unsigned long lastGPS = 0; 
  if (millis() - lastGPS > 1000) 
  { 
    readGPS(); 
 
    if (gps.location.isValid()) 
    { 
      latitude = String(gps.location.lat(), 6); 
      longitude = String(gps.location.lng(), 6); 
    } 
 
    lastGPS = millis(); 
  } 
 
  // Button  
  if (digitalRead(button) == LOW && !buttonPressed) 
  { 
    delay(50); 
    if (digitalRead(button) == LOW) 
    { 
      buttonPressed = true; 
      sendSMS(); 
    } 
  } 
 
  if (digitalRead(button) == HIGH) 
  { 
    buttonPressed = false; 
  } 
 
  // Debug 
  Serial.print("D1: "); 
  Serial.print(distance1); 
  Serial.print(" cm | D2: "); 
  Serial.print(distance2); 
  Serial.println(" cm"); 
 
  delay(150); 
} 

// GPS FUNCTION  
void readGPS() 
{ 
  gpsSerial.listen(); 
 
  unsigned long start = millis(); 
  while (millis() - start < 300) // read for 300ms 
  { 
    while (gpsSerial.available()) 
    { 
      gps.encode(gpsSerial.read()); 
    } 
  } 
} 
 
// DISTANCE FUNCTION 
int getDistance(int trig, int echo) 
{ 
  digitalWrite(trig, LOW); 
  delayMicroseconds(5); 
 
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig, LOW); 

  long duration = pulseIn(echo, HIGH, 20000); 
 
  if (duration <= 0) 
    return -1; 
 
  int distance = duration * 0.034 / 2; 
 
  if (distance < 2 || distance > 400) 
    return -1; 
 
  return distance; 
} 
 
//STABLE DISTANCE 
int stableDistance(int trig, int echo) 
{ 
  int sum = 0, count = 0; 
 
  for (int i = 0; i < 5; i++) 
  { 
    int d = getDistance(trig, echo); 
 
    if (d > 2 && d < 400) 
    { 
      sum += d; 
      count++; 
    } 
 
    delay(10); 
  } 
 
  if (count == 0) return -1; 
 
  return sum / count; 
} 
 
// SMS FUNCTION  
void sendSMS() 
{ 
  gsmSerial.listen(); 
 
  Serial.println("Sending SMS..."); 
 
  gsmSerial.println("AT+CMGF=1"); 
  delay(1000); 
 
 gsmSerial.println("AT+CMGS=\"+91XXXXXXXXXX\""); 

  delay(1000); 
 
  if (gps.location.isValid()) 
  { 
    gsmSerial.print("EMERGENCY! I need help.\nLocation:\n"); 
    gsmSerial.print("https://maps.google.com/?q="); 
    gsmSerial.print(latitude); 
    gsmSerial.print(","); 
    gsmSerial.print(longitude); 
  } 
  else 
  { 
    gsmSerial.print("EMERGENCY! I need help.\nLocation not available."); 
  } 
 
  delay(500); 
  gsmSerial.write(26); 
 
  Serial.println("SMS Sent"); 
}
