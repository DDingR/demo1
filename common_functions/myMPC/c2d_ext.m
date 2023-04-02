function [A, B, C, D] = c2d_ext(A, B, C, D, Ts)
    sys = ss(A, B, C, D);
    sys = c2d(sys, Ts);

    A = sys.A;
    B = sys.B;
    C = sys.C;
    D = sys.D;
% 
%     A = A*Ts+eye(size(A));
%     B = B*Ts;
%     C = C; D = D;

end
