function [F, Phi] = predMat(A, B, C, Np, Nc)
% PREDMAT return prediction matrices F and Phi
%     [F, Phi] = predMat(A, B, C, predictionHorizon, controlHorizon)
% 
%     DESCRIPTION 
%         detail form is available in textbook
%
%     INPUT
%         discrete (and augmented) ss
%             A
%             B
%             C
%             D
%         prediction horizon
%         control horizon

    inputSize = size(B);
    inputSize = inputSize(2);

    [outputSize, stateSize] = size(C);

    F = ones(outputSize * Np, stateSize);
    Phi = zeros(outputSize * Np, inputSize * Nc);

    for i = 1:1:Np
        F((i-1)*outputSize+1:i*outputSize, ...
            1:stateSize) = C * A^i;
        
        for j = 1:1:Nc
            tmp = C * A^(i-1) * B;
            Phi((i+j-2)*outputSize+1:(i+j-1)*outputSize, ...
                (j-1)*inputSize+1:j*inputSize) = tmp;
        end
    end

    Phi = Phi(1:outputSize * Np,1:inputSize * Nc);

end
