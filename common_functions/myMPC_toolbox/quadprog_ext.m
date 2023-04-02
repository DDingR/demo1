clear
clf
%% system
A = [
    0 1 0 0
    0 -0.1818 2.6727 0
    0 0 0 1
    0 -0.4545 31.1818 0
    ];
B = [0 1.8182 0 4.5455]';
C = eye(4);
D = [0 0 0 0]';

Ts = 0.01;

plant = ss(A,B,C,D);
plant_d = c2d(plant, Ts);

Np = 50;
Nc = 30;

%% weights
W.ManipulatedVariables = [
    0
    ];
W.ManipulatedVariablesRate = [
    0
    ];
W.OutputVariables = [
    1, 1, 1 , 1
    ];
W.ECR = 1e5;

%% variable property

MV(1) = struct(Min= -1, Max= 1, RateMin= -100, RateMax= 100, ScaleFactor= 1);

OV(1) = struct(Min= -1, Max= 1, MinECR = 1, MaxECR= 1, ScaleFactor= 1);
OV(2) = struct(Min= -1, Max= 1, MinECR = 1, MaxECR= 1, ScaleFactor= 1);
OV(1) = struct(Min= -1, Max= 1, MinECR = 1, MaxECR= 1, ScaleFactor= 1);
OV(2) = struct(Min= -1, Max= 1, MinECR = 1, MaxECR= 1, ScaleFactor= 1);
%% define obj
mpcObj = mpc(plant,Ts,Np,Nc,W,MV,OV);

%% state

state = [0 1 0 0]';
u = [0]';
state_rec = state;
control_rec = u;
% state = mpcstate(mpcObj)
t = 1:10000;
for i = t
    xmpc = mpcstate(mpcObj, state, [],[],u);

    u = mpcmove(mpcObj, xmpc, [], [0 0 0 0]');

    state = plant_d.A * state + plant_d.B*u;
    state_rec = [state_rec state];
    control_rec = [control_rec u];
end

figure(1)
subplot(2,1,1)
hold on
plot([0 t]*Ts, state_rec(1,:))
plot([0 t]*Ts, state_rec(2,:))
plot([0 t]*Ts, state_rec(3,:))
plot([0 t]*Ts, state_rec(4,:))

subplot(2,1,2)
plot([0 t]*Ts, control_rec)



