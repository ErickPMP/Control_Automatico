float t;
unsigned long timeNow,timeNow2,timeOld,timeOld2;
const unsigned long Ts = 10000;
/*
float b0=0.0,b1=1.99800132602355e-05,b2=-1.97812088062726e-05;
float a0=1,a1=-1.98805181253609,a2=0.988071712861931;
*/
float b0=0.0,b1=0.000198013202549303,b2=-0.000179169751944804;
float a0=1,a1=-1.88503420731165,a2=0.886920436717158;

float u_n,u_n1,u_n2;
float y_n,y_n1,y_n2;

typedef union {
  float number;
  uint8_t bytes[4];
} valor;
valor u_n_ML,y_n_ML;

void setup(){
  Serial.begin(9600);
}

void loop(){
  timeNow = micros();
  if (timeNow - timeOld2 >= Ts){
    timeOld2 = timeNow;
    t = t + (Ts / 1e6);
    if (t<10.0) u_n=0.0;
    else  if (t>=10.0 && t<20.0){u_n=12.0;}
    else  if (t>=20.0 && t<30.0){u_n=0.0;}
    else  if (t>=30.0 && t<40.0){u_n=12.0;}
    else  if (t >= 40.0) {t = 0.0;}
    y_n=b1*u_n1+b2*u_n2-a1*y_n1-a2*y_n2;
    u_n2=u_n1;
    u_n1=u_n;
    y_n2=y_n1;
    y_n1=y_n; 
    u_n_ML.number = u_n;
    y_n_ML.number = y_n;
    Serial.write('V');
    for (int i = 0; i < 4; i++) Serial.write(u_n_ML.bytes[i]);
    for (int i = 0; i < 4; i++) Serial.write(y_n_ML.bytes[i]);
    Serial.write('\n');
  }
}
