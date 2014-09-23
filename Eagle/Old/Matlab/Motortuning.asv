
s = tf([1 0],[0 1]);

ra=0.121; %Armature Resistance in Ohms
La=0.068*10^(-3); %Armature Inductance in Henries
kt=0.03552; % Torque coefficient in Nm/A
Bm=0.00008920308; %Friction Coefficient in Kg*m^2/s
kv=0.03552; %radians/V
M=50;
R=0.1397;
J=0.1777+M*R^2; % Moment of Innertia in kg/m^2
Vin=24;
tau_load=0.0;

%Motor transfer function in rad/sec
m_tf=kt/((J*La)*s^2+(J*ra+Bm*La)*s+Bm*ra+kt^2);
sisotool(m_tf);
%Convert rad/sec to km/h
