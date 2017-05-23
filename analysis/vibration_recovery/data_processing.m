clc; clear all; close all;

path = '\\minerfiles.mst.edu\dfs\users\krbzhb\Desktop\Science Data\';
file = 'REDSpectrometerData20170522T192836';
ext = '.dat';

lookup = [path file ext];
fid = fopen(lookup);
data1=textscan(fid, '%s');
fclose(fid);
data = data1{1};

data_length=length(data)/3;
diode=zeros(data_length, 1);

for i=1:data_length
    diode(i) = str2double(data{3*i});
end

diode1(1)=diode(1);
for i=1:(length(diode)/2)-1
    diode1(i+1)=diode(2*i+1);
    diode2(i)=diode(2*i);
end

subplot(2,1,1)
plot(diode1);
title('Diode 1');
subplot(2,1,2);
plot(diode2);
title('Diode 2');

%-------------------------------------------

