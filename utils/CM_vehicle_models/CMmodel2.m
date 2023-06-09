function [A, B, C, D] = CMmodel2(state, pre_input, delta)
    % MODEL6 2 Wheel nonlinear model 
    %     [A, B, C, D] = model2(state, pre_input)
    %
    %     DESCRIPTION
    %         2 front wheel vehicle
    %         use linearization at operation point (current state and input)
    %         full observation (C is unit matrix and D is 0 vector)
    %
    %     STATE
    %         dot x
    %         dot y
    %         dot psi
    %
    %     INPUT
    %         front left tire force (Ffxl)
    %         front right tire force (Ffxr)

    Cf = 8e4;
    Cr = 8e4;
    m = 1644.80;
    Iz = 2488.892;
    lf = 1.240;
    lr = 1.510;
    w = 0.816;
    
    %% operation point
    Vx = state(1);
    Vy = state(2);
    dot_psi = state(3);
    
    % pre_input is not used here.
    %% element
    dFfydx_dot = 2 * Cf * (-(Vy + lf * dot_psi) / (-Vx^2));
    dFfydy_dot = 2 * Cf * (- 1/Vx);
    dFfydpsi_dot = 2 * Cf * (- lf/Vx);

    dFrydx_dot = 2 * Cr * (-(Vy - lr * dot_psi) / (-Vx^2));
    dFrydy_dot = 2 * Cr * (- 1/Vx);
    dFrydpsi_dot = 2 * Cr * (lr/Vx);

    a11 = (-dFfydx_dot * sin(delta)) / m;
    a21 = (dFfydx_dot * cos(delta)) / m - dot_psi;
    a31 = (dFfydx_dot * cos(delta) * lf - dFrydx_dot * lr) / Iz;
    
    a12 = (-dFfydy_dot * sin(delta)) / m + dot_psi;
    a22 = (dFfydy_dot * cos(delta)) / m;
    a32 = (dFfydy_dot * cos(delta) * lf - dFrydy_dot * lr) / Iz;
    
    a13 = (-dFfydpsi_dot * sin(delta)) / m + Vy;
    a23 = (dFfydpsi_dot * cos(delta)) / m - Vx;
    a33 = (dFfydpsi_dot * cos(delta) * lf - dFrydpsi_dot * lr) / Iz;
    
    b11 = 1 * cos(delta) / m;
    b21 = 1 * sin(delta) / m;
    b31 = (1 * sin(delta) * lf + 1 * cos(delta) * w) / Iz;

    b12 = 1 * cos(delta) / m;
    b22 = 1 * sin(delta) / m;
    b32 = (1 * sin(delta) * lf + -1 * cos(delta) * w) / Iz;

    
    %%
    dfdx_op = [a11 a12 a13;
               a21 a22 a23;
               a31 a32 a33];

    dfdu_op = [b11 b12;
               b21 b22;
               b31 b32];

    A = dfdx_op;
    B = dfdu_op;
    C = eye(size(A));
    D = zeros(size(B));

end
