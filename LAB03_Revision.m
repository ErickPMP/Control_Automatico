clear all, close all, clc
Num1=[100];
Den1=[1 2 100];
Num2=[10];
Den2=[conv([1 0],[1 5])];
Num3=[1 2];
Den3=[conv([1 0],[conv([1 3],[1 6])])];
Num4=[10];
Den4=[conv([1 -1],[1 2])];
Num5=[1 4];
Den5=[1 -3 2];

K=[0.1 0.4 5 10];
Gs1=tf(K(1)*Num1,Den1);
Gs2=tf(Num2,Den2);
Gs3=tf(Num3,Den3);
Gs4=tf(Num4,Den4);
Gs5=tf(Num5,Den5);

figure(1)
rlocus(Gs1);
figure(2)
rlocus(Gs2);
figure(3)
rlocus(Gs3);
figure(4)
rlocus(Gs4);
figure(5)
rlocus(Gs5);

figure(6)
bode(Gs1);
figure(7)
bode(Gs2);
figure(8)
bode(Gs3);
figure(9)
bode(Gs4);
figure(10)
bode(Gs5);

sisotool(Gs1)
sisotool(Gs2)
sisotool(Gs3)
sisotool(Gs4)
sisotool(Gs5)
