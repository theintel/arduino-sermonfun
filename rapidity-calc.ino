/*
Pressing Speed Calculator


This sketch calculates the player's button pressing speed. It uses a digital pin to read
analog voltage: the simple method to detect if the button has been pressed. It counts the
number of times the player has pressed the button for 5 seconds. Then it calculates the result
and sends the data via serial monitor. Finally it terminates itself until the arduino is reset.

Features:
1. The sketch has a countdown timer. So it wouldn't start as soon as the serial monitor is launched.
It will wait for 3 seconds before starting the timer, giving the player some time to be ready.

2. The LED will be lit as long as the button's pressed. So a blinking LED is expected in a fair play.

3. And a foolproof technique has been implemented to prevent cheating. So the player
can't cheat by keeping the button pressed for the whole time.


Components:
1k resistor connected with the ground and pushbutton
Pushbutton connected with the 5V pin and the resistor
LED connected to the digital pin 2

Created: 4 July, 2018
By Muhammad Arifur Rahman
*/

int sensePin=2, ledPin=3; 
int buttonPress, counter;
long startTime, stopTime; //time counters
double avgSpeed;
void setup()
{
pinMode(sensePin,INPUT); //using sensePin to detect button press
pinMode(ledPin,OUTPUT); //just a fancy addition to the project

Serial.begin(9600);
while(!Serial)
continue;

counter=0;
Serial.println("You have 5 seconds only!");

for(int i=0;i<3;i++) //start the 3 seconds countdown
{
Serial.print("\t\t\t\t\t\t\t\t"); //tabs for spacing
Serial.println(3-i);
delay(1000);
} 

Serial.println("\t\t\t\t\t\t\t\tGO!");
Serial.println("");

startTime=millis(); //start the 5 seconds timer
}

void loop()
{
buttonPress=digitalRead(sensePin);

if(buttonPress==HIGH)
{
digitalWrite(ledPin,HIGH); //turn on the LED when the button is pressed

while(buttonPress!=LOW) //wait for the button to be released after pressing
buttonPress=digitalRead(sensePin); //prevent cheating by forcing to release the button

Serial.println("+1");
digitalWrite(ledPin,LOW); 
counter++;
}

stopTime=millis(); //record the time since the start

if(stopTime-startTime>5000) //after 5 seconds, send the result
{
Serial.println("");
Serial.println("Time's Up!!!");
Serial.print("You've pressed it ");
Serial.print(counter);
Serial.println(" times.");

avgSpeed=(double)(1000.0*counter)/(labs(stopTime-startTime));
Serial.print("Your average speed is ");
Serial.print(avgSpeed);
Serial.println(" presses per second.");

delay(500); //wait for 0.5s to let arduino transmit the data
exit(0); //avoid counting further by terminating the program
}


}
