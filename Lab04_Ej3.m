clc; clear all; close all;
syms K real

Num=[conv([1 2],[1 4])];
Den=[6 5 10 2 0];

syms K s
Num_sym=poly2sym(Num,s)
Den_sym=poly2sym(Den,s)

Ec=(Den_sym+K*Num_sym) % 1+C(s)*G(s)
Coef_Ec=coeffs(Ec,s)
a=fliplr(Coef_Ec)
fprintf('Ec:\n '); pretty(poly2sym(a,s));
a=fliplr(a)
A1=[a(5) a(3);
    a(4) a(2)];
A2=[a(5) a(1);
    a(4) 0];
b1=simplify(-det(A1)/a(4));
b2=simplify(-det(A2)/a(4));
B1=[a(4) a(2);
    b1 b2];
c1=simplify(-det(B1)/b1);
C1=[b1 b2;
    c1 0];
d1=simplify(-det(C1)/c1);

fprintf('Tabla de RH\n');
fprintf('s^4: %s\t\t%s\t\t%s\n',char(a(5)),char(a(3)),char(a(1)));
fprintf('s^3: %s\t\t%s\n',char(a(4)),char(a(2)));
fprintf('s^2: %s\t\t%s\n',b1,b2);
fprintf('s^1: %s\t\t%s\n',c1);
fprintf('s^0: %s\n',d1);

syms K real
digits(2)
sol=solve(a(5)>0,a(4)>0,b1>0,c1>0,d1>0,K, 'ReturnConditions', true, 'Real',true);

disp('Intervalo de K:');
disp(vpa(sol.conditions))
