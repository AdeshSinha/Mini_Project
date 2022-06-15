#include <Servo.h>
#define ANALOG_IN_PIN A2
#define buzzerPin 8
#define LM35 A0

Servo servo;
int angle = 10;

float adc_voltage = 0.0;
float in_voltage = 0.0;
float R1 = 30000.0;
float R2 = 7500.0; 
float ref_voltage = 5.0;
int adc_value = 0;

double Vout = 0;
double Current = 0;
const double scale_factor = 0.185;
const double vRef = 5.00;
const double resConvert = 1024;
double resADC = vRef/resConvert;
double zeroPoint = vRef/2;

float sensorValue1=0;
float sensorValue2=0;
float tempc;

float SOH =0;
float SOC =0;
float base_voltage=9;
float base_resistance=180;

void setup() 
{
  Serial.begin(9600);
  servo.attach(9);
  servo.write(angle);
  pinMode (8, OUTPUT);
  pinMode (LM35,INPUT);
}


void loop() 
{ 
 // scan from 0 to 180 degrees
  for(angle = 10; angle < 180; angle++)  
  {                                  
    servo.write(angle);      
           
                         
  } 
    adc_value = analogRead(ANALOG_IN_PIN);
    adc_voltage  = (adc_value * ref_voltage) / 1024.0; 
    in_voltage = adc_voltage / (R2/(R1+R2)); 
    Serial.print("Input Voltage = ");
    Serial.println(in_voltage, 2); 

    for(int i = 0; i < 1000; i++)
    {
      Vout = (Vout + (resADC * analogRead(A3)));   
      delay(1);
    }
    Vout = Vout /1000;
    Current = (Vout - zeroPoint)/ scale_factor; 
    Serial.print("Current = ");                  
    Serial.print(Current,4);
    Serial.println(" Amps");

    sensorValue1 = analogRead(LM35);
    sensorValue2 = 150 - sensorValue1;
    tempc = sensorValue2 * 0.7045;
    Serial.print("Temperature = ");
    Serial.println(tempc);

    SOH = ((in_voltage/Current) / base_resistance) * 100 ;
    Serial.print("State of Health = ");
    Serial.println(SOH); 

    SOC = (in_voltage / base_voltage) * 100 ; 
    Serial.print("State of Charge = ");
    Serial.println(SOC);

    if(tempc > 30)
    {
    digitalWrite(buzzerPin , HIGH);
    delay(1000);
    digitalWrite(buzzerPin , LOW);
    delay(1000);
    digitalWrite(buzzerPin , HIGH);
    delay(1000);
    digitalWrite(buzzerPin , LOW);
    delay(1000);
    }
    

    if(in_voltage > 9)
    {
    digitalWrite(buzzerPin , HIGH);
    delay(1000);
    digitalWrite(buzzerPin , LOW);
    delay(1000);
    }
        
    if(in_voltage >9)
    {
      delay(20000);
    }
    else
    {
      delay(20);
    }
  
  // now scan back from 180 to 0 degrees
  for(angle = 180; angle > 10; angle--)    
  {                                
    servo.write(angle);           
          
  } 
   delay(2000);
}
