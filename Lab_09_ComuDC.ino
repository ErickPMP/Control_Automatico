float t;
unsigned long timeNow,timeNow2,timeOld,timeOld2;
const unsigned long Ts = 1000;
/* //100 Hz
float b0=0.0,b1=0.759957410305847,b2=0.239936702970382;
float a0=1,a1=-0.755310406124729,a2=0.0256260890031707;
*/
 //1000Hz
float b0=0.0,b1=0.0180062897325937,b2=0.0159372589025214;
float a0=1,a1=-1.68403900409704,a2=0.693215449289375;

/* //10000Hz
float b0=0.0,b1=0.000200433506803307,b2=0.000198000353723324;
float a0=1,a1=-1.96391401536920,a2=0.964021729695806;
*/

float u_n,u_n1,u_n2;
float y_n,y_n1,y_n2;

typedef union {
  float number;
  uint8_t bytes[4];
} valor;
valor u_n_ML,y_n_ML;

void setup(){
  Serial.begin(115200);
}

void loop(){
  timeNow = micros();
  if (timeNow - timeOld2 >= Ts){
    timeOld2 = timeNow;
    t = t + (Ts / 1e6);
    y_n=b1*u_n1+b2*u_n2-a1*y_n1-a2*y_n2;
    u_n2=u_n1;
    u_n1=u_n;
    y_n2=y_n1;
    y_n1=y_n;
    if (t<1.0) u_n=0.0;
    else  if (t>=1.0 && t<2.0){u_n=6.0;}
    else  if (t>=2.0 && t<3.0){u_n=0.0;}
    else  if (t>=3.0 && t<4.0){u_n=6.0;}
    else  if (t >= 4.0) {t = 0.0;}
    u_n_ML.number = u_n;
    y_n_ML.number = y_n;
    Serial.write('V');
    for (int i = 0; i < 4; i++) Serial.write(u_n_ML.bytes[i]);
    for (int i = 0; i < 4; i++) Serial.write(y_n_ML.bytes[i]);
    Serial.write('\n');
  }
}
