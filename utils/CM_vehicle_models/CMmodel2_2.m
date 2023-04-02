function [A, B, C, D] = CMmodel2_2(state, pre_input)
    % MODEL6 2 Wheel nonlinear model 
    %     [A, B, C, D] = model2(state, pre_input)
    %
    %     DESCRIPTION
    %         2 front wheel vehicle
    %         use linearization at operation point (current state and input)
    %         full observation (C is unit matrix and D is 0 vector)
    %ls
    %     STATE
    %         dot x
    %         dot y
    %         dot psi
    %
    %     INPUT
    %         front left tire force (Ffxl)
    %         front right tire force (Ffxr)
    Cf = 435.418/0.296296;
    Cr = 756.349/(0.6*pi/180);
    m = 1644.80;
    Iz = 2488.892;
    lf = 1.240;
    lr = 1.510;
    w = 0.8;
    
    %% operation point
    x_dot = state(1);
    y_dot = state(2);
    psi_dot = state(3);
   
    delta = pre_input(1);
%    Frxl = pre_input(2);
%    Frxr = pre_input(3);
    %%
    dfdx_op = [
 
[                                               -(2*Cf*sin(delta)*(y_dot + lf*psi_dot))/(m*x_dot^2),             psi_dot + (2*Cf*sin(delta))/(m*x_dot),                   y_dot + (2*Cf*lf*sin(delta))/(m*x_dot)]
[((2*Cr*(y_dot - lr*psi_dot))/x_dot^2 + (2*Cf*cos(delta)*(y_dot + lf*psi_dot))/x_dot^2)/m - psi_dot,       -((2*Cr)/x_dot + (2*Cf*cos(delta))/x_dot)/m, ((2*Cr*lr)/x_dot - (2*Cf*lf*cos(delta))/x_dot)/m - x_dot]
[  -((2*Cr*lr*(y_dot - lr*psi_dot))/x_dot^2 - (2*Cf*lf*cos(delta)*(y_dot + lf*psi_dot))/x_dot^2)/Iz, ((2*Cr*lr)/x_dot - (2*Cf*lf*cos(delta))/x_dot)/Iz,   -((2*Cf*cos(delta)*lf^2)/x_dot + (2*Cr*lr^2)/x_dot)/Iz]
 
 ];

    dfdu_op = [
        
[      -(2*Cf*sin(delta) + 2*Cf*cos(delta)*(delta - (y_dot + lf*psi_dot)/x_dot))/m,   1/m,  1/m]
[       (2*Cf*cos(delta) - 2*Cf*sin(delta)*(delta - (y_dot + lf*psi_dot)/x_dot))/m,     0,    0]
[(2*Cf*lf*cos(delta) - 2*Cf*lf*sin(delta)*(delta - (y_dot + lf*psi_dot)/x_dot))/Iz, -w/Iz, w/Iz]
 
 ];

    A = dfdx_op;
    B = dfdu_op;
    C = eye(size(A));
    D = zeros(size(B));

end
