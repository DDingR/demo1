if strcmp(vehicle, 'Car')
    Simulink.Bus.cellToObject({
    {
	'cm8MotorInArray', {
	    {'m0',	1,'cm8MotorIn', -1, 'real', 'Sample'};
	    {'m1',	1,'cm8MotorIn', -1, 'real', 'Sample'};
	    {'m2',	1,'cm8MotorIn', -1, 'real', 'Sample'};
	    {'m3',	1,'cm8MotorIn', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8GearBoxInArray', {
	    {'GB_m0',	1,'cm8GearBoxIn', -1, 'real', 'Sample'};
	    {'GB_m1',	1,'cm8GearBoxIn', -1, 'real', 'Sample'};
	    {'GB_m2',	1,'cm8GearBoxIn', -1, 'real', 'Sample'};
	    {'GB_m3',	1,'cm8GearBoxIn', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8WheelInArray', {
	    {'FL',	1,'cm8WheelIn', -1, 'real', 'Sample'};
	    {'FR',	1,'cm8WheelIn', -1, 'real', 'Sample'};
	    {'RL',	1,'cm8WheelIn', -1, 'real', 'Sample'};
	    {'RR',	1,'cm8WheelIn', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8Wheels', {
	    {'FL',	1,'double', -1, 'real', 'Sample'};
	    {'FR',	1,'double', -1, 'real', 'Sample'};
	    {'RL',	1,'double', -1, 'real', 'Sample'};
	    {'RR',	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8MotorOutArray', {
	    {'m0',	1,'cm8MotorOut', -1, 'real', 'Sample'};
	    {'m1',	1,'cm8MotorOut', -1, 'real', 'Sample'};
	    {'m2',	1,'cm8MotorOut', -1, 'real', 'Sample'};
	    {'m3',	1,'cm8MotorOut', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8GearBoxOutArray', {
	    {'GB_m0',	1,'cm8GearBoxOut', -1, 'real', 'Sample'};
	    {'GB_m1',	1,'cm8GearBoxOut', -1, 'real', 'Sample'};
	    {'GB_m2',	1,'cm8GearBoxOut', -1, 'real', 'Sample'};
	    {'GB_m3',	1,'cm8GearBoxOut', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8WheelOutArray', {
	    {'FL',	1,'cm8WheelOut', -1, 'real', 'Sample'};
	    {'FR',	1,'cm8WheelOut', -1, 'real', 'Sample'};
	    {'RL',	1,'cm8WheelOut', -1, 'real', 'Sample'};
	    {'RR',	1,'cm8WheelOut', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8DriveSourceArray', {
	    {'d0',	1,'double', -1, 'real', 'Sample'};
	    {'d1',	1,'double', -1, 'real', 'Sample'};
	    {'d2',	1,'double', -1, 'real', 'Sample'};
	    {'d3',	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8GBMArray', {
	    {'GB_m0',		1,'cm8GBCfgOut', -1, 'real', 'Sample'};
	    {'GB_m1',		1,'cm8GBCfgOut', -1, 'real', 'Sample'};
	    {'GB_m2',		1,'cm8GBCfgOut', -1, 'real', 'Sample'};
	    {'GB_m3',		1,'cm8GBCfgOut', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8MotorArray', {
	    {'m0',	1,'cm8Motor', -1, 'real', 'Sample'};
	    {'m1',	1,'cm8Motor', -1, 'real', 'Sample'};
	    {'m2',	1,'cm8Motor', -1, 'real', 'Sample'};
	    {'m3',	1,'cm8Motor', -1, 'real', 'Sample'};
	}
    }
    });
elseif strcmp(vehicle, 'Truck')
    Simulink.Bus.cellToObject({
    {
	'cm8MotorInArray', {
	    {'m0',	1,'cm8MotorIn', -1, 'real', 'Sample'};
	    {'m1',	1,'cm8MotorIn', -1, 'real', 'Sample'};
	    {'m2',	1,'cm8MotorIn', -1, 'real', 'Sample'};
	    {'m3',	1,'cm8MotorIn', -1, 'real', 'Sample'};
	    {'m4',	1,'cm8MotorIn', -1, 'real', 'Sample'};
	    {'m5',	1,'cm8MotorIn', -1, 'real', 'Sample'};
	    {'m6',	1,'cm8MotorIn', -1, 'real', 'Sample'};
	    {'m7',	1,'cm8MotorIn', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8GearBoxInArray', {
	    {'GB_m0',	1,'cm8GearBoxIn', -1, 'real', 'Sample'};
	    {'GB_m1',	1,'cm8GearBoxIn', -1, 'real', 'Sample'};
	    {'GB_m2',	1,'cm8GearBoxIn', -1, 'real', 'Sample'};
	    {'GB_m3',	1,'cm8GearBoxIn', -1, 'real', 'Sample'};
	    {'GB_m4',	1,'cm8GearBoxIn', -1, 'real', 'Sample'};
	    {'GB_m5',	1,'cm8GearBoxIn', -1, 'real', 'Sample'};
	    {'GB_m6',	1,'cm8GearBoxIn', -1, 'real', 'Sample'};
	    {'GB_m7',	1,'cm8GearBoxIn', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8WheelInArray', {
	    {'FL',	1,'cm8WheelIn', -1, 'real', 'Sample'};
	    {'FR',	1,'cm8WheelIn', -1, 'real', 'Sample'};
	    {'RL',	1,'cm8WheelIn', -1, 'real', 'Sample'};
	    {'RR',	1,'cm8WheelIn', -1, 'real', 'Sample'};
	    {'RL2',	1,'cm8WheelIn', -1, 'real', 'Sample'};
	    {'RR2',	1,'cm8WheelIn', -1, 'real', 'Sample'};
	    {'FL2',	1,'cm8WheelIn', -1, 'real', 'Sample'};
	    {'FR2',	1,'cm8WheelIn', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8Wheels', {
	    {'FL',	1,'double', -1, 'real', 'Sample'};
	    {'FR',	1,'double', -1, 'real', 'Sample'};
	    {'RL',	1,'double', -1, 'real', 'Sample'};
	    {'RR',	1,'double', -1, 'real', 'Sample'};
	    {'RL2',	1,'double', -1, 'real', 'Sample'};
	    {'RR2',	1,'double', -1, 'real', 'Sample'};
	    {'FL2',	1,'double', -1, 'real', 'Sample'};
	    {'FR2',	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8MotorOutArray', {
	    {'m0',	1,'cm8MotorOut', -1, 'real', 'Sample'};
	    {'m1',	1,'cm8MotorOut', -1, 'real', 'Sample'};
	    {'m2',	1,'cm8MotorOut', -1, 'real', 'Sample'};
	    {'m3',	1,'cm8MotorOut', -1, 'real', 'Sample'};
	    {'m4',	1,'cm8MotorOut', -1, 'real', 'Sample'};
	    {'m5',	1,'cm8MotorOut', -1, 'real', 'Sample'};
	    {'m6',	1,'cm8MotorOut', -1, 'real', 'Sample'};
	    {'m7',	1,'cm8MotorOut', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8GearBoxOutArray', {
	    {'GB_m0',	1,'cm8GearBoxOut', -1, 'real', 'Sample'};
	    {'GB_m1',	1,'cm8GearBoxOut', -1, 'real', 'Sample'};
	    {'GB_m2',	1,'cm8GearBoxOut', -1, 'real', 'Sample'};
	    {'GB_m3',	1,'cm8GearBoxOut', -1, 'real', 'Sample'};
	    {'GB_m4',	1,'cm8GearBoxOut', -1, 'real', 'Sample'};
	    {'GB_m5',	1,'cm8GearBoxOut', -1, 'real', 'Sample'};
	    {'GB_m6',	1,'cm8GearBoxOut', -1, 'real', 'Sample'};
	    {'GB_m7',	1,'cm8GearBoxOut', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8WheelOutArray', {
	    {'FL',	1,'cm8WheelOut', -1, 'real', 'Sample'};
	    {'FR',	1,'cm8WheelOut', -1, 'real', 'Sample'};
	    {'RL',	1,'cm8WheelOut', -1, 'real', 'Sample'};
	    {'RR',	1,'cm8WheelOut', -1, 'real', 'Sample'};
	    {'RL2',	1,'cm8WheelOut', -1, 'real', 'Sample'};
	    {'RR2',	1,'cm8WheelOut', -1, 'real', 'Sample'};
	    {'FL2',	1,'cm8WheelOut', -1, 'real', 'Sample'};
	    {'FR2',	1,'cm8WheelOut', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8DriveSourceArray', {
	    {'d0',	1,'double', -1, 'real', 'Sample'};
	    {'d1',	1,'double', -1, 'real', 'Sample'};
	    {'d2',	1,'double', -1, 'real', 'Sample'};
	    {'d3',	1,'double', -1, 'real', 'Sample'};
	    {'d4',	1,'double', -1, 'real', 'Sample'};
	    {'d5',	1,'double', -1, 'real', 'Sample'};
	    {'d6',	1,'double', -1, 'real', 'Sample'};
	    {'d7',	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8GBMArray', {
	    {'GB_m0',		1,'cm8GBCfgOut', -1, 'real', 'Sample'};
	    {'GB_m1',		1,'cm8GBCfgOut', -1, 'real', 'Sample'};
	    {'GB_m2',		1,'cm8GBCfgOut', -1, 'real', 'Sample'};
	    {'GB_m3',		1,'cm8GBCfgOut', -1, 'real', 'Sample'};
	    {'GB_m4',		1,'cm8GBCfgOut', -1, 'real', 'Sample'};
	    {'GB_m5',		1,'cm8GBCfgOut', -1, 'real', 'Sample'};
	    {'GB_m6',		1,'cm8GBCfgOut', -1, 'real', 'Sample'};
	    {'GB_m7',		1,'cm8GBCfgOut', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8MotorArray', {
	    {'m0',	1,'cm8Motor', -1, 'real', 'Sample'};
	    {'m1',	1,'cm8Motor', -1, 'real', 'Sample'};
	    {'m2',	1,'cm8Motor', -1, 'real', 'Sample'};
	    {'m3',	1,'cm8Motor', -1, 'real', 'Sample'};
	    {'m4',	1,'cm8Motor', -1, 'real', 'Sample'};
	    {'m5',	1,'cm8Motor', -1, 'real', 'Sample'};
	    {'m6',	1,'cm8Motor', -1, 'real', 'Sample'};
	    {'m7',	1,'cm8Motor', -1, 'real', 'Sample'};
	}
    }
    });
end
    Simulink.Bus.cellToObject({
    %Inputs
    {
	'cm8EngineIn', {
	    {'set_ISC',		1,'double', -1, 'real', 'Sample'};
	    {'FuelCutOff',	1,'double', -1, 'real', 'Sample'};
	    {'Load',		1,'double', -1, 'real', 'Sample'};
	    {'Trq_trg',		1,'double', -1, 'real', 'Sample'};
	    {'rotv_trg',	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8MotorIn', { ...
	    {'Load',		1,'double', -1, 'real', 'Sample'};
	    {'Trq_trg',		1,'double', -1, 'real', 'Sample'};
	    {'rotv_trg',	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8ClutchIn', {
	    {'Pos',		1,'double', -1, 'real', 'Sample'};
	    {'rotv_out_trg',	1,'double', -1, 'real', 'Sample'};
	    {'Trq_out_trg',	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8GearBoxIn', {
	    {'GearNoTrg',	1,'double', -1, 'real', 'Sample'};
	    {'GearNoTrg_dis',	1,'double', -1, 'real', 'Sample'};
	    {'i_trg',		1,'double', -1, 'real', 'Sample'};
	    {'set_ParkBrake',	1,'double', -1, 'real', 'Sample'};
	    {'rotv_in_trg',	1,'double', -1, 'real', 'Sample'};
	    {'Trq_out_trg',	1,'double', -1, 'real', 'Sample'};
	    {'Clutch',		1,'cm8ClutchIn', -1, 'real', 'Sample'};
	    {'Clutch_dis',	1,'cm8ClutchIn', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8PwrSupplyIn', {
	    {'Pwr_HV1toLV_trg', 	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8WheelIn', {
	    {'rot',	1,'double', -1, 'real', 'Sample'};
	    {'rotv', 	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cmPowerTrainXWDIn', {
	    {'Ignition', 	1, 'double', -1, 'real', 'Sample'};
	    {'Gas', 		1, 'double', -1, 'real', 'Sample'};
	    {'SelectorCtrl',	1, 'double', -1, 'real', 'Sample'};
	    {'Velocity', 	1, 'double', -1, 'real', 'Sample'};
	    {'EngineIn', 	1, 'cm8EngineIn', -1, 'real', 'Sample'};
	    {'ISGIn', 		1, 'cm8MotorIn', -1, 'real', 'Sample'};
	    {'MotorIn', 	1, 'cm8MotorInArray', -1, 'real', 'Sample'};
	    {'ClutchIn', 	1, 'cm8ClutchIn', -1, 'real', 'Sample'};
	    {'GearBoxIn', 	1, 'cm8GearBoxIn', -1, 'real', 'Sample'};
	    {'GearBoxM_In', 	1, 'cm8GearBoxInArray', -1, 'real', 'Sample'};
	    {'PwrSupplyIn', 	1, 'cm8PwrSupplyIn', -1, 'real', 'Sample'};
	    {'WheelIn', 	1, 'cm8WheelInArray', -1, 'real', 'Sample'};
	}
    }
    % Output
    {
	'cm8EngineOut', { ...
	    {'Engine_on',	1,'double', -1, 'real', 'Sample'};
	    {'rotv',		1,'double', -1, 'real', 'Sample'};
	    {'Trq',		1,'double', -1, 'real', 'Sample'};
	    {'TrqDrag',		1,'double', -1, 'real', 'Sample'};
	    {'TrqFull',		1,'double', -1, 'real', 'Sample'};
	    {'TrqOpt',		1,'double', -1, 'real', 'Sample'};
	    {'FuelFlow',	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8MotorOut', {
	    {'rotv',		1,'double', -1, 'real', 'Sample'};
	    {'Trq',		1,'double', -1, 'real', 'Sample'};
	    {'TrqMot_max',	1,'double', -1, 'real', 'Sample'};
	    {'TrqGen_max',	1,'double', -1, 'real', 'Sample'};
	    {'PwrElec',		1,'double', -1, 'real', 'Sample'};
	    {'i_M2W',		1,'cm8Wheels', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8ClutchOut', {
	    {'Pos',		1,'double', -1, 'real', 'Sample'};
	    {'rotv_in',		1,'double', -1, 'real', 'Sample'};
	    {'rotv_out',	1,'double', -1, 'real', 'Sample'};
	    {'Trq_in',		1,'double', -1, 'real', 'Sample'};
	    {'Trq_out',		1,'double', -1, 'real', 'Sample'};
	    {'i_TrqIn2Out',	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8GearBoxOut', {
	    {'GearNo',		1,'double', -1, 'real', 'Sample'};
	    {'GearNo_dis',	1,'double', -1, 'real', 'Sample'};
	    {'Trq_DriveSrc_trg',	1,'double', -1, 'real', 'Sample'};
	    {'i',		1,'double', -1, 'real', 'Sample'};
	    {'rotv_in',		1,'double', -1, 'real', 'Sample'};
	    {'rotv_out',	1,'double', -1, 'real', 'Sample'};
	    {'Trq_in',		1,'double', -1, 'real', 'Sample'};
	    {'Trq_out',		1,'double', -1, 'real', 'Sample'};
	    {'Clutch',		1,'cm8ClutchOut', -1, 'real', 'Sample'};
	    {'Clutch_dis',	1,'cm8ClutchOut', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8BattOut', {
	    {'SOC',	1,'double', -1, 'real', 'Sample'};
	    {'SOH',	1,'double', -1, 'real', 'Sample'};
	    {'Current',	1,'double', -1, 'real', 'Sample'};
	    {'AOC',	1,'double', -1, 'real', 'Sample'};
	    {'Temp',	1,'double', -1, 'real', 'Sample'};
	    {'Energy',	1,'double', -1, 'real', 'Sample'};
	    {'Pwr_max',	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8PwrSupplyOut', {
	    {'Pwr_LV',		1,'double', -1, 'real', 'Sample'};
	    {'Pwr_HV1',		1,'double', -1, 'real', 'Sample'};
	    {'Pwr_HV2',		1,'double', -1, 'real', 'Sample'};
	    {'Voltage_LV',	1,'double', -1, 'real', 'Sample'};
	    {'Voltage_HV1',	1,'double', -1, 'real', 'Sample'};
	    {'Voltage_HV2',	1,'double', -1, 'real', 'Sample'};
	    {'Pwr_HV1toLV',	1,'double', -1, 'real', 'Sample'};
	    {'Pwr_HV1toHV2',	1,'double', -1, 'real', 'Sample'};
	    {'Pwr_HV1toLV_max',	1,'double', -1, 'real', 'Sample'};
	    {'Pwr_HV1toHV2_max',	1,'double', -1, 'real', 'Sample'};
	    {'Eta_HV1toLV',	1,'double', -1, 'real', 'Sample'};
	    {'Eta_HV1toHV2',	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm82DTrq', {
	    {'rx',	1,'double', -1, 'real', 'Sample'};
	    {'ry',	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm83DTrq', {
	    {'rx',	1,'double', -1, 'real', 'Sample'};
	    {'ry',	1,'double', -1, 'real', 'Sample'};
	    {'rz',	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8WheelOut', {
	    {'Inert_in',  	1,'double', -1, 'real', 'Sample'};
	    {'Trq_Drive', 	1,'double', -1, 'real', 'Sample'};
	    {'Trq_Supp2WC',	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8PowerDelta', {
	    {'PlanetGear',	1,'double', -1, 'real', 'Sample'};
	    {'Diffs',		1,'double', -1, 'real', 'Sample'};
	    {'Shafts',		1,'double', -1, 'real', 'Sample'};
	    {'Spring_DL',	1,'double', -1, 'real', 'Sample'};
	    {'Inert_DL',	1,'double', -1, 'real', 'Sample'};
	    {'Inert',		1,'double', -1, 'real', 'Sample'};
	    {'PowerSupply',	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cmPowerTrainXWDOut', {
	    {'ECU_Status',	1,'double', 		-1, 'real', 'Sample'};
	    {'EngineOut',	1,'cm8EngineOut', 	-1, 'real', 'Sample'};
	    {'MCU_Status',	1,'double', 		-1, 'real', 'Sample'};
	    {'ISGOut',		1,'cm8MotorOut', 	-1, 'real', 'Sample'};
	    {'MotorOut',	1,'cm8MotorOutArray',	-1, 'real', 'Sample'};
	    {'TCU_Status',	1,'double', 		-1, 'real', 'Sample'};
	    {'ClutchOut',	1,'cm8ClutchOut', 	-1, 'real', 'Sample'};
	    {'GearBoxOut',	1,'cm8GearBoxOut', 	-1, 'real', 'Sample'};
	    {'GearBoxM_Out',	1,'cm8GearBoxOutArray', -1, 'real', 'Sample'};
	    {'BCU_Status',	1,'double', 		-1, 'real', 'Sample'};
	    {'BattLVOut',	1,'cm8BattOut', 	-1, 'real', 'Sample'};
	    {'BattHVOut',	1,'cm8BattOut', 	-1, 'real', 'Sample'};
	    {'PwrSupplyOut',	1,'cm8PwrSupplyOut', 	-1, 'real', 'Sample'};
	    {'Trq_Supp2Bdy1',	1,'cm83DTrq', 		-1, 'real', 'Sample'};
	    {'Trq_Supp2Bdy1B',	1,'cm83DTrq', 		-1, 'real', 'Sample'};
	    {'Trq_Supp2BdyEng',	1,'cm82DTrq', 		-1, 'real', 'Sample'};
	    {'DL_iDiff_mean',	1,'double', 		-1, 'real', 'Sample'};
	    {'WheelOut',	1,'cm8WheelOutArray', 	-1, 'real', 'Sample'};
	    {'PowerDelta',	1,'cm8PowerDelta', 	-1, 'real', 'Sample'};
	}
    }
    % Cfg Input
    {
	'cmPowerTrainXWDCfgIn', {
	    {'nWheels',	1, 'double', -1, 'real', 'Sample'};
	}
    }
    % Cfg Output
    {
	'cm8DriveLine', {
	    {'iDiff_mean',  	1,'double', -1, 'real', 'Sample'};
	    {'DriveSourcePos', 	1,'cm8DriveSourceArray', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8FGearArray', {
	    {'Gear1',		1,'double', -1, 'real', 'Sample'};
	    {'Gear2',		1,'double', -1, 'real', 'Sample'};
	    {'Gear3',		1,'double', -1, 'real', 'Sample'};
	    {'Gear4',		1,'double', -1, 'real', 'Sample'};
	    {'Gear5',		1,'double', -1, 'real', 'Sample'};
	    {'Gear6',		1,'double', -1, 'real', 'Sample'};
	    {'Gear7',		1,'double', -1, 'real', 'Sample'};
	    {'Gear8',		1,'double', -1, 'real', 'Sample'};
	    {'Gear9',		1,'double', -1, 'real', 'Sample'};
	    {'Gear10',		1,'double', -1, 'real', 'Sample'};
	    {'Gear11',		1,'double', -1, 'real', 'Sample'};
	    {'Gear12',		1,'double', -1, 'real', 'Sample'};
	    {'Gear13',		1,'double', -1, 'real', 'Sample'};
	    {'Gear14',		1,'double', -1, 'real', 'Sample'};
	    {'Gear15',		1,'double', -1, 'real', 'Sample'};
	    {'Gear16',		1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8BGearArray', {
	    {'Gear1',		1,'double', -1, 'real', 'Sample'};
	    {'Gear2',		1,'double', -1, 'real', 'Sample'};
	    {'Gear3',		1,'double', -1, 'real', 'Sample'};
	    {'Gear4',		1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8GBCfgOut', {
	    {'GBKind',  	1,'double', -1, 'real', 'Sample'};
	    {'ClKind',  	1,'double', -1, 'real', 'Sample'};
	    {'nFGears',  	1,'double', -1, 'real', 'Sample'};
	    {'iFGear',  	1,'cm8FGearArray', -1, 'real', 'Sample'};
	    {'nBGears',  	1,'double', -1, 'real', 'Sample'};
	    {'iBGear',  	1,'cm8BGearArray', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8PlanetGear', {
	   {'Ratio',	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8Batt', {
	   {'SOC_min',	1,'double', -1, 'real', 'Sample'};
	   {'SOC_max',	1,'double', -1, 'real', 'Sample'};
	   {'Capacity',	1,'double', -1, 'real', 'Sample'};
	   {'Voltage',	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8Map', {
	    {'x',	100,'double', -1, 'real', 'Sample'};
	    {'z',	100,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8Engine', {
	    {'Fuel_l2kWh',	1,'double', -1, 'real', 'Sample'};
	    {'rotv_off',	1,'double', -1, 'real', 'Sample'};
	    {'rotv_max',	1,'double', -1, 'real', 'Sample'};
	    {'rotv_idle',	1,'double', -1, 'real', 'Sample'};
	    {'rotv_opt',	1,'double', -1, 'real', 'Sample'};
	    {'TrqFull',	1,	'cm8Map', -1, 'real', 'Sample'};
	    {'TrqDrag',	1,	'cm8Map', -1, 'real', 'Sample'};
	    {'TrqOpt',	1,	'cm8Map', -1, 'real', 'Sample'};
	}
    }
    {
	'cm8Motor', {
	    {'Level',		1,'double', -1, 'real', 'Sample'};
	    {'Ratio',		1,'double', -1, 'real', 'Sample'};
	    {'TrqMot_max',	1,'cm8Map', -1, 'real', 'Sample'};
	    {'rotv_Mot_max',	1,'double', -1, 'real', 'Sample'};
	    {'TrqGen_max',	1,'cm8Map', -1, 'real', 'Sample'};
	    {'rotv_Gen_max',	1,'double', -1, 'real', 'Sample'};
	}
    }
    {
	'cmPowerTrainXWDCfgOut', {
	    {'PTKind',		1,'double', -1, 'real', 'Sample'};
	    {'ClKind',		1,'double', -1, 'real', 'Sample'};
	    {'nMotor',		1,'double', -1, 'real', 'Sample'};
	    {'nGearBoxM',	1,'double', -1, 'real', 'Sample'};
	    {'nPlanetGear',	1,'double', -1, 'real', 'Sample'};
	    {'DriveLine',	1,'cm8DriveLine', -1, 'real', 'Sample'};
	    {'GearBox',		1,'cm8GBCfgOut', -1, 'real', 'Sample'};
	    {'GearBoxM',	1,'cm8GBMArray', -1, 'real', 'Sample'};
	    {'PlanetGear',	1,'cm8PlanetGear', -1, 'real', 'Sample'};	
	    {'BattLV',		1,'cm8Batt', -1, 'real', 'Sample'};
	    {'BattHV',		1,'cm8Batt', -1, 'real', 'Sample'};
	    {'Engine',		1,'cm8Engine', -1, 'real', 'Sample'};
	    {'ISG',		1,'cm8Motor', -1, 'real', 'Sample'};
	    {'Motor',		1,'cm8MotorArray', -1, 'real', 'Sample'};
	}
    }
    });
