float Frecuencia = 1000; //Hz
float ms,s,t,In;
float m;
void setup(){
Serial.begin(9600);
noInterrupts();
TCCR0A = 0;
TCCR0B = 0;
TCNT0 = 0;
TCCR0A |= (1 << WGM01);
TCCR0B = _BV(CS02)| _BV(CS00);
OCR0A = 16000000/1024/1000/2;
TIMSK0 |= (1 << OCIE0A);
interrupts();
}
ISR(TIMER0_COMPA_vect){
ms = ms+1;
if(ms == 1000.0){
ms = 0.0;
s = s + 1;
}
t = s + ms/1000.0;
if (t<10.0) In=0.0;
if (t>=10.0 && t<50.0){m=(0.0-500.0)/(10.0-50.0);In=m*(t-10.0)+0.0;}
if (t>=50.0 && t<90.0){m=(500.0+500.0)/(50.0-90.0);In=m*(t-50.0)+500.0;}
if (t>=90.0 && t<130.0){m=(-500.0-500.0)/(90.0-130.0);In=m*(t-90.0)-500.0;}
if (t >= 130.0) {t = 50.0;ms = 0, s = 0;}
}

void loop(){
Serial.println(In);
}
