clc; clear all; close all;

path = '\\minerfiles.mst.edu\dfs\users\krbzhb\Desktop\Science Data\';
file = 'REDSpectrometerData20170523T223817';
file1 = 'REDSpectrometerData20170523T235435';
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

FMAX = 800; %Max optical frequency in nm
FMIN = 400;

%make ideal diode 2 signal
f_ref = linspace(FMIN, FMAX, length(diode2));
avg = mean(diode2);
cal_max = max(diode2);
cal_min= min(diode2);
amplitude = (cal_max - cal_min)/2;
calib_ref = amplitude*(sin((f_ref + 50) /10)) / 2 + avg;


ideal_signal = diode2;

figure('Position', [50 50 1000 900]);
subplot(5,1,1);
plot(f_ref, calib_ref, 'b');
title('Ideal Calibration and Spectrometer Signal');

hold on;
plot(f_ref, ideal_signal, 'r');
legend('Calibration Signal', 'Sample Spectra');
xlabel('wavelength / Slide Position (nm)');
ylabel('Amplitude');
peaks=0;

for i=1:length(calib_ref)
    if (calib_ref(i) == amplitude)
        peaks=peaks+1;
    end
end