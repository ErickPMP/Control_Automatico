clc; clear all; close all;
Num=[1 2];
Den=[1 3 3 1 -1];

syms K s
Num_sym=poly2sym(Num,s);
Den_sym=poly2sym(Den,s);

Ec=(Den_sym+K*Num_sym)

a=coeffs(Ec,s)

A1=[a(5) a(3);
   a(4) a(2)];
A2=[a(5) a(1);
    a(4) 0];
b1=-det(A1)/a(4);
b2=-det(A2)/a(4);
B1=[a(4) a(2);
    b1 b2];
c1=simplify(-det(B1)/b1);
C1=[b1 b1;
    c1 0];
d1=simplify(-det(C1)/c1);
fprintf('s^4: %s\t\t%s\t\t%s\n',char(a(5)),char(a(3)),char(a(1)));
fprintf('s^3: %s\t\t%s\n',char(a(4)),char(a(2)));
fprintf('s^2: %s\t\t%s\n',char(b1),char(b2));
fprintf('s^1: %s\n',char(c1));
fprintf('s^0: %s\n',char(d1));

syms K real
digits(3)
sol=solve(a(5)>0,a(4)>0,b1>0,c1>0,d1>0,K,'ReturnConditions',true);
disp('Los intervalos de K son:')
disp(vpa(sol.conditions))
