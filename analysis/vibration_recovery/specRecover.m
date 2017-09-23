%% 
% Sliding Window approach to waveform recovery

function [wavelength, calibration, spectra] = specRecover( ...
      freq_ref, ... %Reference for ideal calibration waveform
      ideal_calibration, ... %Idealized calibration waveform
      observed_calibration, ...
      observed_signal, ...
      freq_min, ... %DEFAULT 400
      freq_max, ... %DEFAULT 800
      max_back_search, ... %DEFAULT 100
      max_front_search)     %DEFAULT 300


%Recover wavelength index
wavelength = zeros(length(observed_calibration),1);
last_pos = freq_min;
for idx=1:length(observed_calibration)
  loc = find_nearest(observed_calibration(idx), ideal_calibration, last_pos, ...
                     max_back_search, max_front_search);
  wavelength(idx) = freq_ref(loc);
  last_pos = loc;
  
%Produce output waveforms from recovered wavelength index
[wavelength, srtidx] = sort(wavelength);
calibration = observed_calibration(srtidx);
spectra = observed_signal(srtidx);
end  