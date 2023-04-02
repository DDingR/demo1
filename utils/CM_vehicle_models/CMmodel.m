function [A, B, C, D] = CMmodel()
    % MODEL1 very simple model with small steering angle
    %     [A, B, C, D] = model1()
    %
    %     DESCRIPTION
    %         linear model (using small steering angle approximation)
    %
    %     STATE
    %         y
    %         dot y
    %         psi
    %         dot psi
    %
    %     INPUT
    %         steering angle (delta)

    Cf = 80000;
    Cr = 80000;
    m = 2065.03;
    Iz = 3637.526;
    lf = 1.169;
    lr = 1.801;
    Vx = 30;

    a22 = -1 * (2 * Cf + 2 * Cr) / (m * Vx);
    a24 = -Vx + (-2 * Cf * lf + 2 * Cr * lr) / (m * Vx);
    a42 = -1 * (2 * Cf * lf - 2 * Cr * lr) / (Iz * Vx);
    a44 = -1 * (2 * Cf * lf ^ 2 + 2 * Cr * lr ^ 2) / (Iz * Vx);

    b12 = 2 * Cf / m;
    b14 = 2 * Cf * lf / Iz;

    A = [0 1 0 0
             0 a22 0 a24
             0 0 0 1
             0 a42 0 a44];
    B = [0
            b12
            0
            b14];

    C = eye(4);
    D = zeros(4, 1);

end
