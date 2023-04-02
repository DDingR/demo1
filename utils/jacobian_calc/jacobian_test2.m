clear
format shortE

syms x_dot y_dot psi_dot 
syms Frxr Frxl 
syms Ffxl Ffyl Ffxr Ffyr Fryr Fryl
syms beta delta
syms lf lr m r Iz w g Cf Cr
syms D C B
syms Ffz Frz


%% tire forces
Ffxl = 0; Ffxr = 0;
Ffyl = Cf * (delta - (y_dot + lf * psi_dot) / x_dot);
Ffyr = Cf * (delta - (y_dot + lf * psi_dot) / x_dot);
Fryl = Cr * (      - (y_dot - lr * psi_dot) / x_dot);
Fryr = Cr * (      - (y_dot - lr * psi_dot) / x_dot);


Ffx = Ffxr + Ffxl;
Ffy = Ffyr + Ffyl;
Frx = Frxr + Frxl;
Fry = Fryr + Fryl;

delFfx = Ffxr - Ffxl;
delFrx = Frxr - Frxl;
%% vehicle dynamics
ddxdt = (Ffx * cos(delta) - Ffy * sin(delta) + Frx) / m + y_dot * psi_dot;
ddydt = (Ffx * sin(delta) + Ffy * cos(delta) + Fry) / m - x_dot * psi_dot;
ddpsidt = ( (Ffx * sin(delta) + Ffy * cos(delta)) * lf - Fry * lr + delFfx * cos(delta) * w + delFrx * w) / Iz;

%% Jacobian
dfdX = jacobian([ddxdt, ddydt, ddpsidt], [x_dot, y_dot, psi_dot]);
dfdU = jacobian([ddxdt, ddydt, ddpsidt], [delta, Frxl, Frxr]);


