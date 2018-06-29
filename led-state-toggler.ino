/*
   LED state toggler via serial monitor for Arduino Uno

   This sketch takes command from the serial monitor
   and toggles the state of an LED connected to the digital pin 13.
   If the LED is already in the correct state, a humorous message
   is printed in the output. Else, the state of the LED is toggled and
   it prints the time elapsed in the previous state via serial monitor.
    
  Component: LED as output in the digital pin 13
  Created: 19 February, 2016
  By Gus
  Modified: 17 june, 2018
  By Muhammad Arifur Rahman

  https://arduinomylifeup.com/arduino-serial-monitor
*/


int LEDPin = LED_BUILTIN;
int count = 0;
bool LEDstat=0;

void setup() {
	pinMode(LEDPin, OUTPUT); 	//Set led pin to output
	Serial.begin(9600); //Set serial to the 9600 band
	while(!Serial)
	continue;
	Serial.println("Enter Y/y to turn on the LED");
   	Serial.println("Enter N/n to turn off the LED");
}

void loop(){

	if (Serial.available())
	{
		char ch = Serial.read();
		if (ch == 'y' ||	ch == 'Y') //check the command
		{
          if(!LEDstat){ //check if the LED is already turned ON
			digitalWrite(LEDPin, HIGH);
			Serial.println("You have turned on the LED!!");
			Serial.print("The LED was off for ");
			Serial.print((double)count/2); //print elapsed time
			Serial.println(" seconds");
          count=0; LEDstat=!LEDstat; //reset the timer and toggle the LED state
           }
          else{            //if the LED is already off, print a funny message
          Serial.print("Don't you see? Its already ON for ");
          Serial.print((double)count/2);
          Serial.println(" seconds!");
          }
			Serial.println("To turn it off, just enter N or n.");
          Serial.println("");
		}

		else if (ch == 'n' ||	ch == 'N')
		{
          if(LEDstat){
			digitalWrite(LEDPin, LOW);
			Serial.println("You have turned off the LED");
			Serial.print("The LED was ON for ");
			Serial.print((double)count/2);
			Serial.println(" seconds");
          count=0; LEDstat=!LEDstat;
          }
          else
          {Serial.print("Are you kidding? Its turned off for ");
          Serial.print((double)count/2);
          Serial.println(" seconds!");
          }
			Serial.println("To switch it ON again, simply enter Y or y!");
			Serial.println("");
		}
      else if(ch!=10 && ch!=13){ //suppress garbage values from serial receive buffer
      Serial.println("Stop writing gibberish and enter valid command please.");
      Serial.println("");
      }
	}

	delay(500); //pause for 0.5s
	count++;
}
