function [PhiPhi, PhiF, PhiR] = dataMatrices(F, Phi, R_s)
    
PhiPhi = Phi' * Phi;
PhiF = Phi' * F;
PhiR = Phi' * R_s;

end