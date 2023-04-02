# demo1

# DEMO DESCRIPTION

DEMO
    demo1:
        model: model1
        TestRun: testrun1:
            use mpc toolbox (block)
            no yaw reference; use DM steer angle

    demo2:
        model: model2
        TestRun: testrun2
            use myMPC functions
            PID Controller for the tire forces to Torques
            no constraints about tire slip
            not tuned PID gains; 
                at the end of sim, error occurs
            still using DM steer angle as yaw ref

    demo3:
        model: model2
        TestRun: testrun2
            most of systems are same with demo2
            trying sliding mode control to substitute PID controller

MODEL
    model1:
        state: Vy, Ay, Yaw_dot, r
        input: Delta

    model2:
        state: Vx, Vy, Yaw_dot
        input: Ffxl, Ffxr

TESTRUN
    demo1:
        use IPG Driver on Long, Lat

    demo2:
        no Driver model










        
