/*********************************************
 * OPL 12.9.0.0 Model
 * Generated Automatic
 * Creation Date: 14 April 2021 at 19:41:44
 *********************************************/

dvar boolean x_1_1;
dvar boolean x_1_2;
dvar boolean x_1_3;
dvar boolean x_1_4;
dvar boolean x_1_5;
dvar boolean x_1_6;
dvar boolean x_1_7;
dvar boolean x_1_8;
dvar boolean x_1_9;
dvar boolean x_1_10;
dvar boolean x_1_11;
dvar boolean x_1_12;
dvar boolean x_1_13;
dvar boolean x_1_14;
dvar boolean x_1_15;
dvar boolean x_1_16;
dvar boolean x_1_17;
dvar boolean x_1_18;
dvar boolean x_1_19;
dvar boolean x_1_20;
dvar boolean x_1_21;
dvar boolean x_1_22;
dvar boolean x_1_23;
dvar boolean x_1_24;
dvar boolean x_1_25;
dvar boolean x_2_1;
dvar boolean x_2_2;
dvar boolean x_2_3;
dvar boolean x_2_4;
dvar boolean x_2_5;
dvar boolean x_2_6;
dvar boolean x_2_7;
dvar boolean x_2_8;
dvar boolean x_2_9;
dvar boolean x_2_10;
dvar boolean x_2_11;
dvar boolean x_2_12;
dvar boolean x_2_13;
dvar boolean x_2_14;
dvar boolean x_2_15;
dvar boolean x_2_16;
dvar boolean x_2_17;
dvar boolean x_2_18;
dvar boolean x_2_19;
dvar boolean x_2_20;
dvar boolean x_2_21;
dvar boolean x_2_22;
dvar boolean x_2_23;
dvar boolean x_2_24;
dvar boolean x_2_25;
dvar boolean y_1_1;
dvar boolean y_1_2;
dvar boolean y_1_3;
dvar boolean y_1_4;
dvar boolean y_1_5;
dvar boolean y_2_1;
dvar boolean y_2_2;
dvar boolean y_2_3;
dvar boolean y_2_4;
dvar boolean y_2_5;

maximize 12*x_1_1 + 35*x_1_2 + 34*x_1_3 + 18*x_1_4 + 32*x_1_5 + 52*x_1_6 + 70*x_1_7 + 61*x_1_8 + 90*x_1_9 + 66*x_1_10 + 49*x_1_11 + 90*x_1_12 + 94*x_1_13 + 24*x_1_14 + 13*x_1_15 + 50*x_1_16 + 97*x_1_17 + 87*x_1_18 + 20*x_1_19 + 46*x_1_20 + 47*x_1_21 + 75*x_1_22 + 12*x_1_23 + 91*x_1_24 + 42*x_1_25 + 89*x_2_1 + 81*x_2_2 + 62*x_2_3 + 76*x_2_4 + 67*x_2_5 + 92*x_2_6 + 13*x_2_7 + 66*x_2_8 + 26*x_2_9 + 16*x_2_10 + 29*x_2_11 + 82*x_2_12 + 85*x_2_13 + 82*x_2_14 + 23*x_2_15 + 43*x_2_16 + 10*x_2_17 + 84*x_2_18 + 51*x_2_19 + 38*x_2_20 + 10*x_2_21 + 52*x_2_22 + 55*x_2_23 + 28*x_2_24 + 20*x_2_25;

subject to {

42*x_1_1 + 22*x_1_2 + 49*x_1_3 + 16*x_1_4 + 93*x_1_5 + 67*x_1_6 + 12*x_1_7 + 33*x_1_8 + 56*x_1_9 + 17*x_1_10 + 67*x_1_11 + 82*x_1_12 + 29*x_1_13 + 11*x_1_14 + 31*x_1_15 + 55*x_1_16 + 52*x_1_17 + 52*x_1_18 + 13*x_1_19 + 87*x_1_20 + 37*x_1_21 + 15*x_1_22 + 11*x_1_23 + 29*x_1_24 + 36*x_1_25 + 82*y_1_1 + 79*y_1_2 + 66*y_1_3 + 59*y_1_4 + 89*y_1_5 <= 507;

42*x_2_1 + 22*x_2_2 + 49*x_2_3 + 16*x_2_4 + 93*x_2_5 + 67*x_2_6 + 12*x_2_7 + 33*x_2_8 + 56*x_2_9 + 17*x_2_10 + 67*x_2_11 + 82*x_2_12 + 29*x_2_13 + 11*x_2_14 + 31*x_2_15 + 55*x_2_16 + 52*x_2_17 + 52*x_2_18 + 13*x_2_19 + 87*x_2_20 + 37*x_2_21 + 15*x_2_22 + 11*x_2_23 + 29*x_2_24 + 36*x_2_25 + 82*y_2_1 + 79*y_2_2 + 66*y_2_3 + 59*y_2_4 + 89*y_2_5 <= 392;

x_1_1 + x_2_1 <= 1;

x_1_2 + x_2_2 <= 1;

x_1_3 + x_2_3 <= 1;

x_1_4 + x_2_4 <= 1;

x_1_5 + x_2_5 <= 1;

x_1_6 + x_2_6 <= 1;

x_1_7 + x_2_7 <= 1;

x_1_8 + x_2_8 <= 1;

x_1_9 + x_2_9 <= 1;

x_1_10 + x_2_10 <= 1;

x_1_11 + x_2_11 <= 1;

x_1_12 + x_2_12 <= 1;

x_1_13 + x_2_13 <= 1;

x_1_14 + x_2_14 <= 1;

x_1_15 + x_2_15 <= 1;

x_1_16 + x_2_16 <= 1;

x_1_17 + x_2_17 <= 1;

x_1_18 + x_2_18 <= 1;

x_1_19 + x_2_19 <= 1;

x_1_20 + x_2_20 <= 1;

x_1_21 + x_2_21 <= 1;

x_1_22 + x_2_22 <= 1;

x_1_23 + x_2_23 <= 1;

x_1_24 + x_2_24 <= 1;

x_1_25 + x_2_25 <= 1;

y_1_1 + y_2_1 <= 1;

y_1_2 + y_2_2 <= 1;

y_1_3 + y_2_3 <= 1;

y_1_4 + y_2_4 <= 1;

y_1_5 + y_2_5 <= 2;

x_1_1 + x_1_11 + x_1_17 + x_1_19 + x_1_21 + x_1_22 - 25*y_1_1 <= 0;

x_1_2 + x_1_6 + x_1_10 + x_1_15 + x_1_18 + x_1_25 - 25*y_1_2 <= 0;

x_1_3 + x_1_7 + x_1_20 - 25*y_1_3 <= 0;

x_1_4 + x_1_9 + x_1_13 + x_1_14 + x_1_23 + x_1_24 - 25*y_1_4 <= 0;

x_1_5 + x_1_8 + x_1_12 + x_1_16 - 25*y_1_5 <= 0;

x_2_1 + x_2_11 + x_2_17 + x_2_19 + x_2_21 + x_2_22 - 25*y_2_1 <= 0;

x_2_2 + x_2_6 + x_2_10 + x_2_15 + x_2_18 + x_2_25 - 25*y_2_2 <= 0;

x_2_3 + x_2_7 + x_2_20 - 25*y_2_3 <= 0;

x_2_4 + x_2_9 + x_2_13 + x_2_14 + x_2_23 + x_2_24 - 25*y_2_4 <= 0;

x_2_5 + x_2_8 + x_2_12 + x_2_16 - 25*y_2_5 <= 0;

}