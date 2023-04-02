clear
clf
Ts = 0.01;

A = [-0.5572 -0.7814; 0.7814 0];
B = [1 -1; 0 2];
C = eye(2);
D = zeros(2,2);

Np = 20;
Nc = 10;

state = [0 0]';
delta_state = [0 0]';
pre_input = [0 0]';
ref = [5,5];

stateWeight = [1, 1];
controlWeight = [10,10];

stateConstraints = [
    0 0 -10 100 1e0 1e0 1e2 1e2
    0 0 -10 100 1e0 1e0 1e2 1e2
    ];
controlConstraints = [
    -1 1 -5 5 1e0 1e0 1e100 1e100
    -1 1 -5 5 1e0 1e0 1e100 1e100 
    ];

state_rec = [state];
del_u_rec = [pre_input];
u_rec = [pre_input];

for i = 1:1:200
    u = quadprog_ext_slack(A,B,C,D, Ts, state,delta_state, pre_input, ref, Np, Nc, stateWeight, controlWeight, stateConstraints, controlConstraints);

    state = A * state + B * u;
    del_state = state - state_rec(end);
    state_rec = [state_rec state];
    del_u_rec = [del_u_rec, u];
    pre_input = sum(del_u_rec, 2);
    u_rec = [u_rec, pre_input];
end

%%
figure(1)
subplot(3,1,1)
plot(state_rec(1,:))
hold on
plot(state_rec(2,:))


subplot(3,1,2)
plot(del_u_rec(1,:))
hold on
plot(del_u_rec(2,:))

subplot(3,1,3)
plot(u_rec(1,:))
hold on
plot(u_rec(2,:))

