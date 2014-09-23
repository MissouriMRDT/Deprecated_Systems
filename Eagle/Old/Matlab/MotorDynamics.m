%Mars Rover Design Team PMDC Motor Modeling
%Written by Lukas M�ller
%For questions contance lkm8c3@mail.mst.edu

%clearing Workspace & setting up basic variables
clear all
close all
clc
s = tf([1 0],[0 1]);

%Motor & Rover parameters
ra=0.121; %Armature Resistance in Ohms
La=0.068*10^(-3); %Armature Inductance in Henries
kt=0.03552; % Torque coefficient in Nm/A
Bm=0.00008920308; %Friction Coefficient in Kg*m^2/s
kv=0.03552; %radians/V
M=50;
R=0.1397;
J=0.1777+M*R^2; % Moment of Innertia in kg/m^2
Vin=24;
tau_load=0.0; % In Nm applied directely to the motor shaft
%Calculating Motor constants
tau_m=(J*ra)/kv^2;
tau_a=La/ra;
%Motor Controller Parameters
kp=1/300; %kp term for PI
ki=1/50 ; %ki term for PI 
sampletime=0.001; % sampling time of controller in seconds
G_pwm=(1/128);% PWM goes from 128 to 256 from 0 to full speed in Atmega 328P TIMER 2 PWM
%Encoder Parameters
PPR=512; % Number of pulses per revoltuion (Not used right now)
%Calculate Motor Dynamics in laplace domain
G_vw=((1/(kv*tau_a*tau_m))*Vin-(1/J)*(s+(1/tau_a))*tau_load)/(s^2+((1/tau_a)+(Bm/J))*s+(1/tau_a)*((1/tau_m)+(Bm/J)))*0.3267*(1/16);
ZOH=(1/(s*(sampletime))-ss(exp(-s*(sampletime))/((sampletime)*s)));
G_comp=((ki/s)+kp)*ZOH;
T_B=G_vw*G_comp*G_pwm;
sisotool(T_B);
Cloop=feedback(T_B,1);
step(1*Cloop);