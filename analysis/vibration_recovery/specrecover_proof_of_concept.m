clear all; %close all; clc;
%%---------------------------------------------------
%% Calculate ideal signal and calibration reference
%%---------------------------------------------------
FMAX = 800; %Max optical frequency in nm
FMIN = 400;

f_ref = [FMIN : 0.1 : FMAX];
calib_ref = (sin((f_ref + 50) /31)) / 2 + 0.5;
% Make a nice spiky waveform with noise as our spectrometer signal
ideal_signal = abs(sin(f_ref/19)) .^ 50 + (0.07 * abs(randn(size(f_ref)))); 

figure('Position', [50 50 1000 900]);
subplot(5,1,1);
plot(f_ref, calib_ref, 'b');
title('Ideal Calibration and Spectrometer Signal');

hold on;
plot(f_ref, ideal_signal, 'r');
legend('Calibration Signal', 'Sample Spectra');
xlabel('wavelength / Slide Position (nm)');
ylabel('Amplitude');

%%---------------------------------------------------
%% Simulate effects of vibration on sampling
%%---------------------------------------------------

% Generate "Jumpy" sample points. 
% Slide generally advances in halting jumps, with 
sp = zeros(500,1);
for idx = 1:100:500
  sp(idx:idx+100) = idx;
end  
% Smooth
filterCoeff = ones(1, 50) / 50;
sp = filter(filterCoeff, 1, sp);
% Offset
sp = sp + 400;
% Add Random Noise
sp = sp + 5 * randn(size(sp),1);


subplot(5,1,2);
plot( sp, 1:length(sp), 'b'); % Plot where our slide actually is
hold on; plot( (1:length(sp)) + FMIN, 1:length(sp) , 'r'); %Plot where it would be ideally
legend('simulated slide', 'ideal slide');
title('Irregular Slide Movement / Sampling');
xlim([FMIN, FMAX]);
xlabel('Slide Position (nm)');
ylabel('Time');

%calib_observed = calib_ref(sample_points);
%signal_observed = ideal_signal(sample_points);


% Read from the ideal data at the specified sample points
calib_sampled = zeros(size(sp));
signal_observed = zeros(size(sp));
for idx = 1:length(sp)
  % Find the index of the ideal data where the slide is
  idy = find(f_ref > (sp(idx)), 1 );
  if(isempty(idy))
    idy = length(calib_ref);
  end
  %sample the ideal data
  calib_sampled(idx) = calib_ref(idy);
  signal_observed(idx) = ideal_signal(idy);
end

subplot(5, 1, 3); plot(1:length(calib_sampled), calib_sampled, 'b');
hold on; plot(1:length(signal_observed), signal_observed, 'r');
legend('Calibration Signal', 'Sample Spectra');
title("Vibration-scrambled signal, 500 samples");
xlabel("Sample Point ");
ylabel("Amplitude");

%----------------------------------------------------
% Plot best possible reconstruction results
%--------------------1--------------------------------
subplot(5,1,4); 
[sortedSP, sortIndex] = sort(sp);
calib_sampled_ordered = calib_sampled(sortIndex);
signal_observed_ordered = signal_observed(sortIndex);

plot(sortedSP, calib_sampled_ordered  , '-b.'); hold on;
plot(sortedSP, signal_observed_ordered, '-r.');
xlim([FMIN FMAX]);
title("Theoretical best recovered signal");
xlabel("Wavelenth (nm)");

%%---------------------------------------------------
%% Reconstruction Algorithm
%%---------------------------------------------------
recovered_timestamp = zeros(size(calib_sampled));
last_pos = FMIN;
pl = subplot(5,1,5);
for idx=1:length(calib_sampled)
  delete(pl);
  pl = subplot(5,1,5);

  % Find the nearest point to the last one
  % where the simulated calibration signal 
  % matches our observed calibration signal
  loc = find_nearest(calib_sampled(idx), calib_ref, last_pos, 100, 300);
  recovered_timestamp(idx) = f_ref(loc);
  last_pos = loc;
  if loc > last_pos; last_pos = loc; end;
  %assert(last_pos >= lpdebug);
  
  plot(recovered_timestamp(1:idx), calib_sampled(1:idx));
  xlim([FMIN-100 FMAX+100]);
  title("Reconstructing Calibration Signal");
  pause(0.01);
end  

%[wavelength calibration spectra] = specRecover(f_ref, calib_ref, calib_sampled, ...
%  signal_observed, FMIN, FMAX, 100, 300);
  
%Recovered_timestamp should match the uneven sampling points  
%%---------------------------------------------------
%% Plot reconstruction results
%%---------------------------------------------------
subplot(5,1,5); 

% Sort recovered timestamp and data vectors
[wavelength, srtidx] = sort(recovered_timestamp); %Sorted Recovered Timestamp (SRT), SRT Index list)
calibration = calib_sampled(srtidx);
spectra = signal_observed(srtidx);

% Plot sorted data
         plot(wavelength, calibration, '-b.');
hold on; plot(wavelength, spectra, '-r.');
title("Algorithmically recovered signal (RESULTS)");
xlim(FMIN, FMAX);