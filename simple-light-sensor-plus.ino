/*
Enhanced Simple Light Detector

This sketch creates a simple light sensor with some enhanced features.
It mplements the basic mechanism to detect ambient light with a photoresistor.
Creating a voltage divider with photoresistor and a 1k resistor, it measures the
voltage across the 1k resistor. Then it calculates the resistance of the photoresistor and
total power consumption of the sensor with mathematical equations and sends
the data via serial monitor.

Features:
1.
The resistance of the photoresistor is sent via serial monitor in real-time.
This visualises how the resistance increases in the dark, how power consumption
decreases due to increased equivalent resistance and vice versa.

2.
Additionally, the sketch lights up an LED in the dark and turns that off automatically
when there's adequate ambient light. The same implementation can be used for
home automation. For instance, it can turn ON the backup light during power outage.


Components:
Photoresistor connected to 5V pin & 1k resistor
1k resistor connected to the photoresistor & ground pin
LED connected to the digital pin 13 and GND

Created: 02 August, 2018
By Muhammad Arifur Rahman
*/


const double constRes=1000.0; //The 1k resistor 
const double conVol=5.0/1023.0; //Constant to convert analogRead() value to voltage
bool ledState=0; //Contains 0 or 1 depending on the current LED state
int ledPin=13;
double maxVol, resVol; //Total voltage, Voltage across 1k resistor
double photoRes, powRating; //LDR resistance, power rating of the sensor
void setup() {

pinMode(A0,INPUT);
pinMode(A1,INPUT);
pinMode(ledPin,OUTPUT);

Serial.begin(9600);
while(!Serial)
continue;

}

void loop() {

maxVol=analogRead(A0);
resVol=analogRead(A1);

if(resVol==0)
resVol=0.5;
/* If the voltage across the 1k resistor is less than 4.8mV, analogRead() returns 0.
This mathematically results in infinite resistance of the photoresistor.
It is incorrect as even if its small, there's always a voltage across the 1k resistor.
But the arduino is too insensitive to measure such small voltage.
The above line will set resVol to 0.5, a value in between 0 and 1.
This will prevent maxVol getting divided by zero.
*/

maxVol*=conVol; resVol*=conVol; //Converts the readings to voltage
photoRes=(maxVol/resVol-1)*constRes; //Kirchhoff's Law + simple algebra, R2=(V/V1-1)*R1

double powRating=(maxVol*maxVol)/(constRes+photoRes); //P=V^2/R

if(resVol<20*conVol) //detect darkness when resVol is less than 98mV
{
if(!ledState)
{
Serial.println("Its so dark, I'm scared! Turning the light ON"); //Serial monitor fun
digitalWrite(ledPin,HIGH);
ledState=!ledState; //Toggle LED state
}
}

else
{
if(ledState)
{
Serial.println("So much light, WoW! I'll turn OFF the light");
digitalWrite(ledPin,LOW);
ledState=!ledState;
}
}

Serial.print("LDR Resistance: ");
Serial.print(photoRes);
Serial.println(" ohm");
Serial.print("Sensor Power Rating: ");
Serial.print(powRating*1e+3); //Converts to milliwatts
Serial.println("mW");
Serial.println("");
delay(1000); //Waits for 1s before reading again
}
