
int FlameSensor = A0; // definge the analog pin




void setup() 
{
  pinMode(FlameSensor,INPUT);
  Serial.begin(9600); 

}

void loop() 
{
  float flameReading; 

  flameReading = analogRead(FlameSensor);
  Serial.println(flameReading);
  
  delay (500);
  
}
