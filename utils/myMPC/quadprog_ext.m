function u = quadprog_ext(A,B,C,D, Ts, state,delta_state, pre_input, ref, Np, Nc, stateWeight, controlWeight, stateConstraints, controlConstraints)

%% weight matrices
stateWeight = reshape(stateWeight, 1, []);
stateWeight = repmat(stateWeight, 1, Np);

controlWeight = reshape(controlWeight, 1, []);
controlWeight = repmat(controlWeight, 1, Nc);

Q = diag(stateWeight);
R = diag(controlWeight);

%% reference vector
ref = repmat(ref,Np,1);

%% model augmentation
state = [delta_state;state]; 

[A,B,C,D] = augmentation_ext(A,B,C,D,Ts);
[F, Phi] = predMat(A, B, C, Np, Nc);

H = Phi' * Q * Phi + R;
f = 2 * (ref - F * state)' * Q * (-Phi);

if ~issymmetric(H)
    H = (H+H')/2;
end

%% constraints matrices
[a, b] = constraintMatrix(state, pre_input, Np, Nc, F, Phi, stateConstraints, controlConstraints);

%% quadratic programming
options = optimoptions( ...
    'quadprog', ...
    'Algorithm','interior-point-convex', ...
    'Display','none' ...
    );

[u,fval,exitflag,output] = quadprog(H,f,a,b,[],[],[],[], [],options);

if isempty(u) || exitflag ~= 1
    disp("[ERR] infeasible problem")
    disp(exitflag);
    disp(u(1:size(pre_input,1)));
end

u = u(1:size(pre_input,1));
