clc; clear all; close all;

% Paso 1: Definir numerador y denominador de G(s)
Num = conv([1 2], [1 5]);            % (s + 2)(s + 5) → s^2 + 7s + 10
Den = conv([1 1], conv([1 3], [1 -2]));  % (s + 1)(s + 3)(s - 2)

% Paso 2: Crear simbólicamente la ecuación característica
syms K s
Num_sym = poly2sym(Num, s);
Den_sym = poly2sym(Den, s);

% Ecuación característica: Den + K*Num
Ec = expand(Den_sym + K*Num_sym);

% Paso 3: Obtener coeficientes
coeffs_Ec = fliplr(coeffs(Ec, s));  % de mayor a menor

% Mostrar el polinomio en la ventana de comandos
fprintf('Ecuación característica:\n');
pretty(poly2sym(coeffs_Ec, s));

% Paso 4: Construir la tabla de Routh simbólicamente
a = fliplr(coeffs_Ec);  % Coeficientes: a0 s^3, a1 s^2, a2 s^1, a3 s^0

B1=[a(4) a(2);
   a(3) a(1)];

% Fila s^2
b1 = -det(B1)/a(3)

C1=[a(3) a(1);
   b1 0];

c1 = -det(C1)/b1;

% Mostrar la tabla
fprintf('\nTabla de Routh-Hurwitz:\n\n');
fprintf('Fila s^3: %s\t\t%s\n', char(a(4)), char(a(2)));
fprintf('Fila s^2: %s\t\t%s\n', char(a(3)), char(a(1)));
fprintf('Fila s^1: %s\t\t%s\n', char(b1), char(0*K));
fprintf('Fila s^0: %s\n', char(c1));

syms K real
digits(2)
sol = solve(a(4)>0,a(3)>0,b1>0,c1>0, K, 'ReturnConditions', true);
sol1 = solve(a(4)>0, K, 'ReturnConditions', true);
sol2 = solve(a(3)>0, K, 'ReturnConditions', true);
sol3 = solve(b1>0, K, 'ReturnConditions', true);
sol4 = solve(c1>0, K, 'ReturnConditions', true);
disp('Intervalo de K: ')
disp(vpa(sol.conditions))
disp(sol1.conditions)
disp(sol2.conditions)
disp(vpa(sol3.conditions))
disp(sol4.conditions)
