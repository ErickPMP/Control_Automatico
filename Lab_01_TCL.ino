float ms,s,t,In;
float m;
int w;
char command;
bool Start;
void setup(){
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(9,OUTPUT)
  pinMode()
  while (!Serial);
  Serial.println("READY");  // Indica que está listo

  noInterrupts();
  TCCR0A = 0;
  TCCR0B = 0;
  TCNT0 = 0;
  TCCR0A |= (1 << WGM01);
  TCCR0B = _BV(CS02)| _BV(CS00);
  OCR0A = (16000000/1024/1000/2)-1;
  TIMSK0 |= (1 << OCIE0A);
  interrupts();


}

ISR(TIMER0_COMPA_vect){
ms = ms+1;
w = w+1;
if(ms == 1000.0){
ms = 0.0;
s = s + 1;
}
t = s + ms/1000.0;
if (t<10.0) In=0.0;
if (t>=10.0){In=255.0;}

if(Serial.available()){ 
  command = Serial.read();
  if (command == 'S'){
    Start = true;
  }
}

  if(Start){
    if(w ==100){
    Serial.print(t);
    Serial.print(" ");
    Serial.print(In);
    Serial.print(" ");
    Serial.print(2*In);
    Serial.print("\n");
    w=0;
    }
  }
  if (J==500){
    ProcessVar=analogRead(A0);
  }

}
void loop(){
  analogWrite(3,In);
  //Temperatura = 1/10*(ProcessVar-2000)+150
}
