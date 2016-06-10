/*
 * Blinky.cpp
 *
 * Created: 6/1/2016 7:25:20 PM
 * Author : NexusFS
 */ 

//#include <avr/io.h>
#include <Arduino.h>

bool CheckingInput(int number, int prevPress);
bool CheckingInput(int number);

int main(void)
{
	init();
	
	//pinMode(13, INPUT);
    pinMode(13, INPUT);
	pinMode(12, INPUT);
	pinMode(11, INPUT);
	pinMode(10, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(8, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(5, OUTPUT);
	
    bool redLight = false;
    bool greenLight = false;
    bool blueLight = false;
    
    bool firstTimered = false;
    bool firstTimegreen = false;
    bool firstTimeblue = false;

    Serial.begin(115200);

    /* Replace with your application code */
    while (true) 
    {
		//digitalWrite(13, LOW);
		//delay(250);
		//digitalWrite(13, HIGH);
		//delay(250);

        //int redButton = digitalRead(13);
        //int greenButton = digitalRead(12);
        //int blueButton = digitalRead(11);

        //if(redButton == LOW  && CheckingInput(13, redButton))
           //{ redLight = !redLight;  }
        //if(greenButton == LOW && CheckingInput(12, greenButton))
           //{ greenLight = !greenLight; }
        //if(blueButton == LOW  && CheckingInput(11, blueButton))
           //{ blueLight = !blueLight; }
        
        //Checking RED button press
        if(CheckingInput(13))
        {
            if(firstTimered == false)
                {
                    redLight = !redLight;
                    firstTimered = true;
                }
        }
        else
            firstTimered = false; 
        
        //Checking GREEN button press
        if(CheckingInput(12))
        {
            if(firstTimegreen == false)
            {
                greenLight = !greenLight;
                firstTimegreen = true;
            }
        }
        else
            firstTimegreen = false;

        //Checking BLUE button press
        if(CheckingInput(11))
        {
            if(firstTimeblue == false)
            {
                blueLight = !blueLight;
                firstTimeblue = true;
            }
        }
        else
            firstTimeblue = false;

        //singleLED
        digitalWrite(7, redLight);
        digitalWrite(6, greenLight);
        digitalWrite(5, blueLight);

        //triLED
        digitalWrite(8, redLight);
        digitalWrite(9, greenLight);
        digitalWrite(10, blueLight);
        
    }
}

bool CheckingInput(int number)
{
    for (int x = 0; x < 1000; x++)
    {
        if(digitalRead(number))
            return false;
    }
    return true;
}

bool CheckingInput(int number, int prevPress)
{
    for (int x = 0; x < 1000; x++)
    {
        if(digitalRead(number) != prevPress)
            {return false;}
    }

    return true;
}


bool digital(uint8_t pin, uint8_t mode)
{
    
    static uint16_t states = 0xFFFF;
    uint16_t mask = (1<<pin);
    uint16_t state = 0;
    uint16_t count = 0;
    
    //button debounce
    for (count = 0; count < 1000; count ++)
    {
        //Getting current pin state
        state = (digitalRead(pin) << pin);
        
        //if no state change
        if(state == (states & mask))
            return false;
                         
    }
    
    //save new state
    states &= ~mask;
    states |= state;
    
    //if resulting state transition is the one requesting, return true
    return (((mode && state) || (!mode && !state)) ? true:false);
}