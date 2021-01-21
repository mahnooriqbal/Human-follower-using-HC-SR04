#include <Adafruit_NeoPixel.h>
#include <NewPing.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        4 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 12 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
int buzPin=2;
int trigPin=6;
int echoPin=5;
float duration;
float dist;
NewPing sonar1(10, 10, 50);
NewPing sonar2(6, 5, 30);
NewPing sonar3(9, 9, 30);
NewPing sonar4(11, 11, 30);
#define motor_aPin1 A0
#define motor_aPin2 A1
#define motor_bPin1 A2
#define motor_bPin2 A3
void setup(){
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pinMode(trigPin,OUTPUT);
   pinMode(echoPin,INPUT);
   digitalWrite(trigPin,LOW);
  Serial.begin(9600);
  pinMode(motor_aPin1,OUTPUT);
 pinMode(motor_aPin2,OUTPUT);
 pinMode(motor_bPin1,OUTPUT);
 pinMode(motor_bPin2,OUTPUT);
 pinMode(buzPin,OUTPUT);
  Serial.begin(9600);
}
  void brake()
{
 digitalWrite(motor_aPin1,LOW);
 digitalWrite(motor_aPin2,LOW);
 digitalWrite(motor_bPin1,LOW);
 digitalWrite(motor_bPin2,LOW);
}
void forward()
{
 digitalWrite(motor_aPin1,LOW);
 digitalWrite(motor_aPin2,HIGH);
 digitalWrite(motor_bPin1,HIGH);
 digitalWrite(motor_bPin2,LOW);
}
void backward()
{
 digitalWrite(motor_aPin1,HIGH);
 digitalWrite(motor_aPin2,LOW);
 digitalWrite(motor_bPin1,LOW);
 digitalWrite(motor_bPin2,HIGH);
 
}
void buz()
{
 digitalWrite(buzPin,HIGH);
 delay(100);
 digitalWrite(buzPin,LOW);
}
void cal_dist(){
  digitalWrite(trigPin,HIGH);
  delay(10);
  digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  dist=duration*0.0343/2;
}
void loop(){ 
   cal_dist();
  Serial.println("Distance");
  Serial.println(dist);
  delay(500);
  for(int i=0; i<NUMPIXELS; i++) { // For each pix
  if(dist>=50){
    brake();
    Serial.println("brake");

    pixels.setPixelColor(i, pixels.Color(255, 0, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.
 if(sonar4.ping_cm()!=0)
    buz();
    brake();
  }
else if(dist<=25){
  backward();
  Serial.println("backward");
pixels.setPixelColor(i, pixels.Color(0, 0, 255));

    pixels.show();   // Send the updated pixel colors to the hardware.
  }
else{
  forward();
  Serial.println("Forward");
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    pixels.show();   // Send the updated pixel colors to the hardware.
  }
}
}
