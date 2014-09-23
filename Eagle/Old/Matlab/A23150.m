kt=0.03552; %Newton meters/A
KV1=28.16961409498638; %rad/sec /V;
kv=KV1^(-1); %V/ rad/sec;
R=0.21; %Motor Resistance
Bm=0.00005299859; %Motor Friction Coefficicent
Tl=0:0.001:4.025; %Varying Load Torque
Vin=24; %Input voltage
Vin1=18;
Vin2=12;
Vin3=6;
C=(2*pi*5*9.47*10^(-4))/15;

wr=(Vin/(((R*Bm)/kt)+kv))-(R/(((R*Bm))+kt*kv))*Tl;
RPM=wr*9.54929659643*C;
I=(Vin-kv*wr)/R;
Pin=Vin.*I;
Pout=wr.*Tl;
eta=(Pout./Pin)*100;


wr=(Vin/(((R*Bm)/kt)+kv))-(R/(((R*Bm))+kt*kv))*Tl;
RPM=wr*9.54929659643*C;
I=(Vin-kv*wr)/R;
Pin=Vin.*I;
Pout=wr.*Tl;
eta=(Pout./Pin)*100;

wr1=(Vin1/(((R*Bm)/kt)+kv))-(R/(((R*Bm))+kt*kv))*Tl;
RPM1=wr1*9.54929659643*C;
I1=(Vin1-kv*wr1)/R;
Pin1=Vin1.*I1;
Pout1=wr1.*Tl;
eta1=(Pout1./Pin1)*100;

wr2=(Vin2/(((R*Bm)/kt)+kv))-(R/(((R*Bm)+kt)*kv))*Tl;
RPM2=wr2*9.54929659643*C;
I2=(Vin2-kv*wr2)/R;
Pin2=Vin2.*I2;
Pout2=wr2.*Tl;
eta2=(Pout2./Pin2)*100;


figure(1)
plot(Tl,RPM,Tl,RPM1,Tl,RPM2)
set(gcf,'Position',[200 200 3.45*150 2.25*150])
set(gca,'FontName','Times')
set(gca,'FontSize',[11])
xlabel('Motor Load Torque (Nm)')
ylabel('Rover speed in mp/h')
legend('24V (100%)','18V (75%)','12V (50%)','Location','NorthEast')
axis([0,2,0,15])
set(gca,'XTick',[0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1 2])
set(gca,'YTick',[0 2.5 5 7.5 10 12.5 15])
grid on
figure(2)
plot(Tl,I)
set(gcf,'Position',[200 200 3.45*96 2.25*96])
set(gca,'FontName','Times')
set(gca,'FontSize',[11])
xlabel('Motor Load Torque')
ylabel('Drawn Current')
legend('A23-150','Location','NorthWest')
axis([0,4,0,120])
grid on
figure(3)
plot(Tl,eta,Tl,eta1,Tl,eta2)
set(gcf,'Position',[200 200 3.45*96 2.25*96])
set(gca,'FontName','Times')
set(gca,'FontSize',[11])
xlabel('Motor Load Torque (Nm)')
ylabel('Motor Efficiency (%)')
legend('24V (100%)','18V (75%)','12V (50%)','Location','NorthEast')
axis([0,4,0,85])
grid on
figure(4)
plot(Tl,Pin,Tl,Pout)
set(gcf,'Position',[200 200 3.45*96 2.25*96])
set(gca,'FontName','Times')
set(gca,'FontSize',[11])
xlabel('Motor Load Torque (Nm)')
ylabel('Power (Watts)')
legend('Pin','Pout','Location','NorthWest')