kt=0.009039; %Newton meters/A
KV1=113.41149466; %rad/sec /V;
kv=KV1^(-1); %V/ rad/sec;
R=0.13846; %Motor Resistance
Bm=0.0000012515538461; %Motor Friction Coefficicent
Tl=0:0.001:0.5; %Varying Load Torque
Vin=20; %Input voltage
Vin1=18;
Vin2=12;
Vin3=6;
wr=(Vin/(((R*Bm)/kt)+kv))-(R/(((R*Bm))+kt*kv))*Tl;
RPM=wr*9.54929659643;
I=(Vin-kv*wr)/R;
Pin=Vin.*I;
Pout=wr.*Tl;
eta=(Pout./Pin)*100;

wr=(Vin/(((R*Bm)/kt)+kv))-(R/(((R*Bm))+kt*kv))*Tl;
RPM=wr*9.54929659643;
I=(Vin-kv*wr)/R;
Pin=Vin.*I;
Pout=wr.*Tl;
eta=(Pout./Pin)*100;

wr1=(Vin1/(((R*Bm)/kt)+kv))-(R/(((R*Bm))+kt*kv))*Tl;
RPM1=wr1*9.54929659643;
I1=(Vin1-kv*wr1)/R;
Pin1=Vin1.*I1;
Pout1=wr1.*Tl;
eta1=(Pout1./Pin1)*100;

wr2=(Vin2/(((R*Bm)/kt)+kv))-(R/(((R*Bm))+kt*kv))*Tl;
RPM2=wr2*9.54929659643;
I2=(Vin2-kv*wr2)/R;
Pin2=Vin2.*I2;
Pout2=wr2.*Tl;
eta2=(Pout2./Pin2)*100;


figure(1)
plot(Tl,RPM,Tl,RPM1,Tl,RPM2)
set(gcf,'Position',[200 200 3.45*96 2.25*96])
set(gca,'FontName','Times')
set(gca,'FontSize',[11])
xlabel('Motor Load Torque (Nm)')
ylabel('Motor RPM')
legend('20V','18V ','12V','Location','NorthEast')
grid on
% figure(2)
% plot(Tl,I)
% set(gcf,'Position',[200 200 3.45*96 2.25*96])
% set(gca,'FontName','Times')
% set(gca,'FontSize',[11])
% xlabel('Motor Load Torque')
% ylabel('Drawn Current')
% legend('A23-150','Location','NorthEast')
figure(3)
plot(Tl,eta,Tl,eta1,Tl,eta2)
set(gcf,'Position',[200 200 3.45*96 2.25*96])
set(gca,'FontName','Times')
set(gca,'FontSize',[11])
xlabel('Motor Load Torque (Nm)')
ylabel('Motor Efficiency (%)')
legend('24V ','18V ','12V ','Location','NorthEast')
grid on
figure(4)
plot(Tl,Pin,Tl,Pout)
set(gcf,'Position',[200 200 3.45*96 2.25*96])
set(gca,'FontName','Times')
set(gca,'FontSize',[11])
xlabel('Motor Load Torque (Nm)')
ylabel('Power (Watts)')
legend('Pin','Pout','Location','NorthWest')