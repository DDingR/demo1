clear

% alexnetONNX = "alexnet.onnx";
% alexnetPY = importONNXNetwork(alexnetONNX, TargetNetwork="dlnetwork")

actorONNX = "DDPG_actor.onnx";
citicONNX = "DDPG_critic.onnx";
% 
% actorLayer = importONNXLayers(actorONNX);
% 
actor = importONNXNetwork(actorONNX, TargetNetwork="dlnetwork", InputDataFormats="BC", OutputDataFormats="BC");
critic = importONNXNetwork(citicONNX, TargetNetwork="dlnetwork", OutputDataFormats="BC");
% 
analyzeNetwork(actor)
analyzeNetwork(critic)

predict(actor,dlarray([1,2,3], "BC"))