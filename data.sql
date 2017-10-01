INSERT OR IGNORE INTO readings (rid, dataid, measured_at, datatype) 
VALUES (0, 0, 1, 0);  -- Raw and processed
INSERT OR IGNORE INTO readings (rid, dataid, measured_at, datatype) 
VALUES (1, 100, 101, 0);  -- Only raw 
INSERT OR IGNORE INTO readings (rid, dataid, measured_at, datatype) 
VALUES (2, 200, 201, 1);  -- Soil humidity
INSERT OR IGNORE INTO readings (rid, dataid, measured_at, datatype) 
VALUES (3, 300, 301, 2);  -- Soil Temperature
INSERT OR IGNORE INTO readings (rid, dataid, measured_at, datatype) 
VALUES (4, 400, 401, 3);  -- Air Humidity
INSERT OR IGNORE INTO readings (rid, dataid, measured_at, datatype) 
VALUES (5, 500, 501, 4);  -- Air Temperature
INSERT OR IGNORE INTO readings (rid, dataid, measured_at, datatype) 
VALUES (6, 600, 601, 5);  -- Air Pressure
INSERT OR IGNORE INTO readings (rid, dataid, measured_at, datatype) 
VALUES (7, 700, 701, 6);  -- Methane levels
INSERT OR IGNORE INTO readings (rid, dataid, measured_at, datatype) 
VALUES (8, 800, 801, 7);  -- UV Intensity

INSERT OR IGNORE INTO readings (rid, dataid, measured_at, datatype)
VALUES (9, 900, 901, 8);  -- Joint Angle
INSERT OR IGNORE INTO readings (rid, dataid, measured_at, datatype)
VALUES (10, 1000, 1001, 9);  --Joint Speed

INSERT OR IGNORE INTO spectra_raw (rid, arr_idx, measurement)
VALUES (0, 0, 0.01);
INSERT OR IGNORE INTO spectra_raw (rid, arr_idx, measurement)
VALUES (0, 1, 0.02);
INSERT OR IGNORE INTO spectra_raw (rid, arr_idx, measurement)
VALUES (0, 2, 0.03);
INSERT OR IGNORE INTO spectra_raw (rid, arr_idx, measurement)
VALUES (1, 0, 0.11);
INSERT OR IGNORE INTO spectra_raw (rid, arr_idx, measurement)
VALUES (1, 0, 0.12);
INSERT OR IGNORE INTO spectra_raw (rid, arr_idx, measurement)
VALUES (1, 0, 0.13);

INSERT OR IGNORE INTO spectra_processed (rid, arr_idx, measurement)
VALUES (0, 0, 0.011);
INSERT OR IGNORE INTO spectra_processed (rid, arr_idx, measurement)
VALUES (0, 1, 0.021);
INSERT OR IGNORE INTO spectra_processed (rid, arr_idx, measurement)
VALUES (0, 2, 0.031);

INSERT OR IGNORE INTO spectra_peaks (rid, center, amplitude, fwhm, tag, tag_key)
VALUES (0, 10, 20, 30, "Chem", "CHEM");
INSERT OR IGNORE INTO spectra_peaks (rid, center, amplitude, fwhm, tag, tag_key)
VALUES (0, 11, 21, 31, "Phys", "PHYS");

INSERT OR IGNORE INTO soil_humidity (rid, measurement) VALUES (2, 20);
INSERT OR IGNORE INTO soil_temperature (rid, measurement) VALUES (3, 30);
INSERT OR IGNORE INTO air_humidity (rid, measurement) VALUES (4, 40);
INSERT OR IGNORE INTO air_temperature (rid, measurement) VALUES (5, 50);
INSERT OR IGNORE INTO air_pressure (rid, measurement) VALUES (6, 6);
INSERT OR IGNORE INTO methane (rid, measurement) VALUES (7, 7);
INSERT OR IGNORE INTO ultraviolet (rid, measurement) VALUES (8, 8);


INSERT OR IGNORE INTO joint_angle (rid, measurement) VALUES (9,2);
INSERT OR IGNORE INTO joint_speed (rid, measurement) VALUES (10,1)