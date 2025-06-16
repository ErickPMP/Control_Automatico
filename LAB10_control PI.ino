float y_n,u_n,u_n1,e_n,e_n1,SPo;
unsigned long timeOld2 = 0;
unsigned long timeNow;
const unsigned long Ts = 10000;
float t;
//float Kp = 14.0,Ki =0.003;
float b1=14,b2=-13.9995800000000;
float a1=1,a2=-1;
//KP 14 KI 0.003
typedef union {
  float number;
  uint8_t bytes[4];
} valor;
valor u_n_ML, y_n_ML, SPo_ML;

void setup(){
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(9,OUTPUT);
  timeOld2 = micros();
}

void loop(){
  
    if(t>=0.0 && t<15.0) {SPo = 0.0;}
    else if(t>=15.0){SPo = 70.0;}
    else {t=0.0;}

    y_n = ((5.0/1023.0)*analogRead(A0)-0.5)*100.0;
    
    e_n = SPo - y_n;
    u_n = b1*e_n + b2*e_n1 - a2*u_n1;
    e_n1 = e_n;
    u_n1 = u_n;
    if (u_n>=255.0){u_n=255.0;}
    if (u_n<=0.0){u_n=0.0;}
    analogWrite(3,u_n);
    timeNow = micros();
    if (timeNow - timeOld2 >= Ts){
      timeOld2 = timeNow;
      t = t + (Ts / 1e6);
      SPo_ML.number = SPo;
      u_n_ML.number = u_n;    
      y_n_ML.number = y_n;    
      Serial.write('V');
      for (int i = 0; i < 4; i++) Serial.write(SPo_ML.bytes[i]);
      for (int i = 0; i < 4; i++) Serial.write(u_n_ML.bytes[i]);
      for (int i = 0; i < 4; i++) Serial.write(y_n_ML.bytes[i]);
      Serial.write('\n');
    }
}
