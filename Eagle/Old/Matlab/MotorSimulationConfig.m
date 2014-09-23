%Mars Rover Design Team
% Missouri S&T
%Permanent Magnet Brushed DC motor simulation parameters
% Author: Lukas Müller

%Motor Drive Parameter
d=100; %PWM Duty cycle in % between 0-100. 50% = no speed 0% full reverse 100% full forward
Vin=24; %DC bus input voltage in Volts

%Motor Parameters
ra=0.21; %Amerature Resistance in Ohms
La=1*10^(-3); %Amerature Inductance in Henries
kv= 269; %EMF coefficient in RPM/V
kI=0.03552; % Torque coefficient in Nm/A
Bm=0.00005299859; %Friction Coefficient
J=0.031; % Moment of Innertia in kg/m^2

%Load Parameter
rw=0.127; %Wheel radius in meters
GR=1/15; %Gear Ratio
Crr=0.3; %Approximate resistance coefficient
Cd=0.35; % Drag Coefficient
A=0.25; % Crosssectional Area of the Front of the rover in m^2
w=50; %Weight of rover in kg
g=9.81; %Gravitational Constant in m/s^2
phi= 60*0.0174532925; %Grade angle in Radians, first number can be put in degress
Nwheel= 6; %Number on Wheels on Rover