clear
format shortE

syms x_dot y_dot psi_dot 
syms Srxr Srxl 
syms Sfxl Sfyl Sfxr Sfyr Sryr Sryl
syms beta delta omegaF omegaR
syms lf lr m r Iz w g
syms D C B
syms Ffz Frz

%% wheel speed vector
% Vfxr = V * cos(beta - delta) + psi_dot * lf * sin(delta);
% Vfyr = V * sin(beta - delta) + psi_dot * lf * cos(delta);
% 
% Vfxl = V * cos(beta - delta) + psi_dot * lf * sin(delta);
% Vfyl = V * sin(beta - delta) + psi_dot * lf * cos(delta);
% 
% Vrxr = V * cos(beta);
% Vryr = V * sin(beta) - psi_dot * lr;
% 
% Vrxl = V * cos(beta);
% Vryl = V * sin(beta) - psi_dot * lr;

Vfxr = x_dot + w * psi_dot;
Vfyr = y_dot + lf * psi_dot;

Vfxl = x_dot - w * psi_dot;
Vfyl = y_dot + lf * psi_dot;

Vrxr = x_dot + w * psi_dot;
Vryr = y_dot - lr * psi_dot;

Vrxl = x_dot - w * psi_dot;
Vryl = y_dot - lr * psi_dot;

Vwfxl = + Vfxl * cos(delta) + Vfyl * sin(delta);
Vwfyl = - Vfxl * sin(delta) + Vfyl * cos(delta);

Vwfxr = + Vfxr * cos(delta) + Vfyr * sin(delta);
Vwfyr = - Vfxr * sin(delta) + Vfyr * cos(delta);

Vwrxl = + Vrxl;
Vwryl = + Vryl;

Vwrxr = + Vrxr;
Vwryr = + Vryr;

%% slip quantities
Sfxl = 0; Sfxr = 0;
% Sfx = (Vfx - omegaF * r) / (omegaF * r);
% Sfy = Vfy / (omegaF * r);
Sfyl = (1 + Sfxl) * tan(Vwfyl/Vwfxl);
Sfyr = (1 + Sfxr) * tan(Vwfyr/Vwfxr);
% Sfyl = 0; Sfyr = 0;
Sfr = sqrt(Sfxr^2 + Sfyr^2); 
Sfl = sqrt(Sfxl^2 + Sfyl^2);

% Srx = (Vrx - omegaR * r) / (omegaR * r);
% Sry = Vry / (omegaR * r);
Sryl = (1 + Srxl) * tan(Vwryl/Vwrxl);
Sryr = (1 + Srxr) * tan(Vwryr/Vwrxr);
% Sryl = 0; Sryr = 0;
Srr = sqrt(Srxr^2 + Sryr^2);
Srl = sqrt(Srxl^2 + Sryl^2);

%% friction coefficient (MF)
muFr = D * sin(C * atan(B * Sfr));
muFxr = -(Sfxr / Sfr) * muFr;
muFyr = -(Sfyr / Sfr) * muFr;

muFl = D * sin(C * atan(B * Sfl));
muFxl = -(Sfxl / Sfl) * muFl;
muFyl = -(Sfyl / Sfl) * muFl;

muRr = D * sin(C * atan(B * Srr));
muRxr = -(Srxr / Srr) * muRr;
muRyr = -(Sryr / Srr) * muRr;

muRl = D * sin(C * atan(B * Srl));
muRxl = -(Srxl / Srl) * muRl;
muRyl = -(Sryl / Srl) * muRl;


%% tire forces
Ffz = m*g*(lf+lr)/lr/2;
Frz = m*g*(lf+lr)/lf/2;

Ffxr = muFxr * Ffz;
Ffyr = muFyr * Ffz;

Ffxl = muFxl * Ffz;
Ffyl = muFyl * Ffz;

Frxr = muRxr * Frz;
Fryr = muRyr * Frz;

Frxl = muRxl * Frz;
Fryl = muRyl * Frz;

Ffx = Ffxr + Ffxl;
Ffy = Ffyr + Ffyl;
Frx = Frxr + Frxl;
Fry = Fryr + Fryl;

delFfx = Ffxr - Ffxl;
delFrx = Frxr - Frxl;
%% vehicle dynamics
ddxdt = (Ffx * cos(delta) - Ffy * sin(delta) + Frx) / m + y_dot * psi_dot;
ddydt = (Ffx * sin(delta) + Ffy * cos(delta) + Fry) / m - x_dot * psi_dot;
ddpsidt = ((Ffx * sin(delta) + Ffy * cos(delta)) * lf - Fry * lr + delFfx * w + delFrx * w) / Iz;

%% Jacobian
dfdX = jacobian([ddxdt, ddydt, ddpsidt], [x_dot, y_dot, psi_dot]);
dfdU = jacobian([ddxdt, ddydt, ddpsidt], [delta, Srxl, Srxr]);


