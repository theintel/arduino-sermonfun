/*
Average analog pin voltage calculator for Arduino Uno.


This sketch calculates the average voltage on analog pins of an Arduino Uno.
As soon as the serial monitor starts, the arduino keeps taking readings from the analog pins.
It calculates the average voltage and reports the data to the serial monitor every second.
The accuracy of the average voltage data increases as the arduino receives more readings in each loop.
Within about 20 loops, the data becomes as much as 95% accurate.

Component: Potentiometer/voltage source as input in analog pins.


Created: 12 June, 2018
By Muhammad Arifur Rahman

*/


int loopNum; //declaring average voltage calculation variables
double avgVol,volSum;

void setup() {
for(int apin=A0;apin<=A5;apin++) //there are six(6) analog pins in arduino uno
pinMode(apin,INPUT); //initializing to read voltage from analog pins

loopNum=1;
avgVol=volSum=0;

Serial.begin(9600); //define the serial data transmission rate
if(Serial) //check if serial monitor is ready
Serial.println("Arduino is live!");
}

void loop() {
Serial.print("Reading #");
Serial.println(loopNum);
Serial.print("Current average voltage: ");


Serial.print(avgVol);
Serial.println("V");

for(int apin=A0;apin<=A5;apin++)
{
double apinVol=analogRead(apin);
apinVol=map(apinVol, 0,1023, 0,5);  //conversion of the voltage to the standard

Serial.print("Pin #A");
Serial.print(apin);
Serial.print(": Voltage= ");
Serial.print(apinVol);
Serial.print("V | ");

if(fabs(apinVol-avgVol)>0.01) //check further if the voltage difference is more than 10mV
{
Serial.print(fabs((apinVol-avgVol))*1000);

if(apinVol>avgVol)
Serial.println("mV more");
else if(apinVol<avgVol)
Serial.println("mV less");
}

else
Serial.println("Perfect voltage!");

volSum+=apinVol;
}


avgVol=volSum/(6*loopNum);
loopNum++;
Serial.println("");
delay(1000); //reading interval, change it for faster/slower data reading
}
