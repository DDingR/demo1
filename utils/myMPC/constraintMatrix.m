function [a,b] = constraintMatrix(state, pre_input, Np, Nc, F, Phi, stateConstraints, controlConstraints)

input_size = length(pre_input);
state_size = length(state)/2;

% S1 = eye(input_size  * controlHorizon);
% S2 = tril(ones(size(S1)),-1) - tril(ones(size(S1)), -2);

C1 = eye(input_size  * Nc);
C2 = tril(ones(size(C1)));


controlConstraints = reshape(controlConstraints, [], 4);
stateConstraints = reshape(stateConstraints, [], 4);

%% state rate
% a2 = [S1; -S1];
% b2 = [
%     Phi \ (S1-S1) \ (+repmat(stateConstraints(:,2), predictionHorizon, 1) - F * state);
%     Phi \ (S1-S1) \ (+repmat(stateConstraints(:,2), predictionHorizon, 1) - F * state);
%     ];


a1 = []; b1 = [];
%% state amp
a2 = [Phi; -Phi];
b2 = [
    +repmat(stateConstraints(:,4), Np, 1) - F * state;
    -repmat(stateConstraints(:,3), Np, 1) + F * state
];

delList = [];
for i = 1:state_size 
    if stateConstraints(i,3) == stateConstraints(i,4)
        tmp = (1:state_size:state_size*Np) + (i-1);
        delList = [delList, tmp, tmp + state_size*Np];
    end
end

a2(delList, :) = [];
b2(delList, :) = [];
% a2 = []; b2 = [];

%% input rate
a3 = [C1; -C1];
b3 = [
    +repmat(controlConstraints(:,2), Nc, 1);
    -repmat(controlConstraints(:,1), Nc, 1)
];

delList = [];
for i = 1:input_size 
    if controlConstraints(i,1) == controlConstraints(i,2)
        tmp = (1:input_size:input_size*Nc) + (i-1);
        delList = [delList, tmp, tmp + input_size*Nc];
    end
end

a3(delList, :) = [];
b3(delList, :) = [];
 
%% input amp
a4 = [C2; -C2];
% b4 = [repmat(controlConstraints(:,4), controlHorizon, 1);
%       repmat(controlConstraints(:,3), controlHorizon, 1)];
b4 = [
    -repmat(pre_input, Nc, 1) + repmat(controlConstraints(:,4), Nc, 1);
    +repmat(pre_input, Nc, 1) - repmat(controlConstraints(:,3), Nc, 1)
];

delList = [];
for i = 1:input_size 
    if controlConstraints(i,3) == controlConstraints(i,4)
        tmp = (1:input_size:input_size*Nc) + (i-1);
        delList = [delList, tmp, tmp + input_size*Nc];
    end
end

a4(delList, :) = [];
b4(delList, :) = [];
 
%% return
% a = [a1;a2;a3;a4];
% b = [b1;b2;b3;b4];

a = [a3;a4];
b = [b3;b4];
% a = [];
% b = [];
end







