/*
 * EnvironmentalControl_Lab.cpp
 *
 * Created: 6/3/2016 5:28:46 PM
 * Author : NexusFS
 */ 

//#include <avr/io.h>
#include <Arduino.h>
#include <Servo.h>

float getVoltage(int pin);
uint8_t LightTune(int LightAmount);
int SuperLightTune(int LightAmount);
void CalculatingLightAverages(int LightAmount);
bool CheckingInput(int number);

int LightArrStuff[10];
int WhichArrpostion = 0;
int LightMin;
int LightMax;
int Average;
bool FirstTime = false;

int main(void)
{
    init();
    Servo myservo;
    myservo.attach(9);
    myservo.write(90);
    pinMode(8, INPUT_PULLUP);
    int temperaturepin = 0;
    int LightSensorPin = 1;
    
    for (int x =0; x < 10; x++)
    {
        LightArrStuff[x] = 600;
    }
    
    uint32_t nextUpdate = millis();
    uint32_t LongUpdate = millis();
    uint32_t TimeoutValue = 20;
    uint8_t ser;
    float voltage, degreesC, degreesF;
    Serial.begin(115200);
    /* Replace with your application code */
    while (true) 
    {
        if(nextUpdate < millis())
        {
            nextUpdate += 20;
            int LightLevel;
            
            //Temperature Readings
            voltage = getVoltage(temperaturepin);
            degreesC = (voltage - 0.5f) * 100.0;
            degreesF = degreesC * (9.0/5.0) + 32.0;
            
            //LightReadings
            LightLevel = analogRead(LightSensorPin);
            CalculatingLightAverages(LightLevel);
            
            
            if(LightMax - LightMin <= 10)
            {
                //BlueLight
                analogWrite(5, LOW);
                //RedLight
                analogWrite(6, LOW);
                myservo.write(90);
            }    
            else
            {
                uint8_t newlight = LightTune(Average);
                //BlueLight
                analogWrite(5, newlight);
                //RedLight
                analogWrite(6, ~(newlight));
                ser =  map(Average, LightMin, LightMax, 20, 160);
                myservo.write(ser);
            }
            
            if(LightMax > LightMin)
            {
                LightMin++;
                LightMax--;
            }
            //if(CheckingInput(8))
            //{
            //    if(FirstTime == false)
            //    {
            //        FirstTime = true;
            //        Serial.print("Light: ");
            //        Serial.print(Average);
            //        Serial.print(" LightMin: ");
            //        Serial.print(LightMin);
            //        Serial.print(" LightMax: ");
            //        Serial.print(LightMax);
            //        Serial.print(" Map: ");
            //        Serial.print(ser);
            //        Serial.print(" Temp: degC ");
            //        Serial.print(degreesC);
            //        Serial.print(" degF ");
            //        Serial.println(degreesF);
            //    }
            //}
            //else
            //FirstTime = true;
        }
        if(LongUpdate < millis())
        {
            LongUpdate += 500;
            
            if(digitalRead(8) == LOW)
            {
               Serial.print("Light: ");
               Serial.print(Average);
               Serial.print(" LightMin: ");
               Serial.print(LightMin);
               Serial.print(" LightMax: ");
               Serial.print(LightMax);
               Serial.print(" Map: ");
               Serial.print(ser);
               Serial.print(" Temp: degC ");
               Serial.print(degreesC);
               Serial.print(" degF ");
               Serial.println(degreesF);
                
            }
        }              
    }
}


float getVoltage(int pin)
{
    return (analogRead(pin) * 0.004882814);
    // This equation converts the 0 to 1023 value that analogRead()
    // returns, into a 0.0 to 5.0 value that is the true voltage
    // being read at that pin.
}

uint8_t LightTune(int LightAmount)
{
    uint8_t temp;
    
    //temp = map(LightAmount, 500, 800, 0, 255);
    temp = map(LightAmount, LightMin, LightMax, 0, 255);
    //temp = constrain(temp, 0, 255);
    
    return temp;
}

void CalculatingLightAverages(int LightAmount)
{
    
    LightArrStuff[WhichArrpostion] = LightAmount;
    WhichArrpostion++;
    
    if(WhichArrpostion > 9)
        WhichArrpostion = 0;
        
    int average = 0;
    int total = 0;
    for (int x = 0; x < 10; x++)
    {
        total += LightArrStuff[x];
    }
    
    average = total / 10;
    
    
    if(average > LightMax)
         LightMax = average;
         
    if(average < LightMin)
         LightMin = average;
           
    Average = average;
}

bool CheckingInput(int number)
{
    for (int x = 0; x < 50; x++)
    {
        if(digitalRead(number))
        return false;
    }
    return true;
}