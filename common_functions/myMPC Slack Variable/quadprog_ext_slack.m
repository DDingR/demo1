function u = quadprog_ext_slack(A,B,C,D, Ts, state,delta_state, pre_input, ref, Np, Nc, stateWeight, controlWeight, stateConstraints, controlConstraints)
%% weight matrices
stateWeight = reshape(stateWeight, 1, []);
stateWeight = repmat(stateWeight, 1, Np);

controlWeight = reshape(controlWeight, 1, []);
controlWeight = repmat(controlWeight, 1, Nc);

Q = diag(stateWeight);
R = diag(controlWeight);

%% reference vector
ref = reshape(ref, [], 1);
ref = repmat(ref,Np,1);

%% model augmentation
state = [delta_state; state]; 

[A,B,C,D] = augmentation_ext(A,B,C,D,Ts);
[F, Phi] = predMat(A, B, C, Np, Nc);

H = Phi' * Q * Phi + R;
f = 2 * (ref - F * state)' * Q * (-Phi);

if ~issymmetric(H)
    H = (H+H')/2;
end

%% constraints matrices
[a, b, s] = constraintMatrix_slack(state, pre_input, Np, Nc, F, Phi, stateConstraints, controlConstraints);

%% slack augmentation
tmp_size = size(a);
pred_size = tmp_size(1);
input_size = tmp_size(2);
slackVar_size = length(s);

H = [
    H,                                      zeros(input_size, slackVar_size);
    zeros(slackVar_size, input_size)        diag(s);    
];
f = [f zeros(1, slackVar_size)];

a = [
    a,                                      -zeros(pred_size, slackVar_size);
    zeros(slackVar_size, input_size)        -eye(slackVar_size);                                         
];
b = [b; zeros(slackVar_size, 1)];

%% quadratic programming
options = optimoptions( ...
    'quadprog', ...
    'Algorithm','interior-point-convex', ...
    'Display','none', ...
    'MaxIterations', 200, ... % 200(default)
    'OptimalityTolerance', 1e-8, ... % 1e-8(default)
    'ConstraintTolerance', 1e-8, ... % 1e-8(default)
    'LinearSolver', 'auto' ... % auto(default), sparse, dense
    );

[u,fval,exitflag,output] = quadprog(H,f,a,b,[],[],[],[], [],options);

if isempty(u) || exitflag ~= 1
    disp("[ERR] infeasible problem")
    disp(exitflag)
    disp(u(1:size(pre_input,1)));
end

u = u(1:size(pre_input,1));
