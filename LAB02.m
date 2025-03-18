close all,clc,clear all
R=1000;
C=1e-6;
L=10;
Num = [1];
Den = [L*C R*C 1];

%Num=1000*[0.01*0.01 0.01*0.1];
%Den=[0.005 0.06 0.1001];

%Num=[1 20];
%Den=[1 0 -25];
K= 15;
%Num = K*[1 20];
%Den = [1 K-15 20*K+5];

% Num = [1 20];
% Den = [1 -15 5];

%Num = [2 5 14];
%Den = [4 10 2 15];

Gs=tf(Num,Den)

% Definir un rango de frecuencias más denso
w = logspace(-1, 5, 10000); % De 10^(-1) Hz a 10^6 Hz con 1000 puntos
t = linspace(0, 5, 10000);
%sisotool(Gs)
figure(1)
rlocus(Gs)
grid on
figure(2)
step(Gs)
grid on
figure(3)
bode(Gs,w)
grid on
figure(4)
pzmap(Gs)
grid on
