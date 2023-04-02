function [A, B, C, D] = augmentation_ext(A, B, C, D, Ts)
% AUGMENTATION_EXT agmentate continous state space eqn
%     [A,B,C,D] = augmentation_ext(A,B,C,D,Ts)
%
%     DESCRIPTION
%         augmentation to proper form for MPC
%     
%     PROCESS        
%         1. continous to dicrete ss
%             [Ac, Bc, Cc, Dc] -> [Ad, Bd, Cd, Dd]
%         2. augmentation 
%             [Ad, Bd, Cd, Dd] -> [A, B, C, D]
%             
%             A = [Ad 0; Cd*Ad 1]
%             B = [Bd, Cd*Bd]
%             C = [0 1]
%             D = 0
%
%     INPUT
%         conttinous state space (A,B,C,D)
%         time difference (Ts)        

% [A, B, C, D] = c2dm(A,B,C,D,Ts);
[A, B, C, D] = c2d_ext(A,B,C,D, Ts);


[o, s] = size(C);

A = [   A          zeros(s, o);
    C * A     eye(o)             ];

B = [   B;
    C * B];

C = [zeros(o, s) eye(o)];

D = zeros(size(B));
end