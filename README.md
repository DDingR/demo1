# demo1

## DEMO DESCRIPTION

### DEMO

| DEMO | MODEL | TESTRUN | DESCRIPTION |
|------|-------|---------|-------------|
| demo1 | model1 | testrun1 |  use mpc toolbox (block)<br>no yaw reference; use DM steer angle |
| demo2 | model1 | testrun1 |  use myMpc<br>PID for tire force tracking |


### MODEL
 
 Carmaker models are in `/utils/CM_vehicle_models/`.

| MODEL | STATE | CONTROL |
|-------|-------|---------|
| CMmodel | Vy, Ay, Yaw_dot, Yaw_ddot | Delta |
| CMmodel2 | Vx, Vy, Yaw_dot | Delta, Frxl, Frxr |
| CMmodel3 | Vx, Vy, Yaw_dot | Delta, Srxl, Srxr |


### TESTRUN
    demo1:
        use IPG Driver on Long, Lat

    demo2:
        no Driver model










        
