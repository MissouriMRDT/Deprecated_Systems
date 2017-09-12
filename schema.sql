DROP TABLE IF EXISTS datatypes;
DROP TABLE IF EXISTS readings;
DROP TABLE IF EXISTS spectra_raw;
DROP TABLE IF EXISTS spectra_processed;
DROP TABLE IF EXISTS spectra_peaks;

CREATE TABLE IF NOT EXISTS datatypes (
    code INTEGER PRIMARY KEY,
    sensor_type TEXT NOT NULL,
    sensor_type_key TEXT NOT NULL,
    unit TEXT NOT NULL,
    unit_key TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS readings (
    rid INTEGER PRIMARY KEY,
    dataid INTEGER NOT NULL,
    measured_at INTEGER NOT NULL,  -- DATETIME NOT NULL
    datatype INTEGER NOT NULL,
    FOREIGN KEY(datatype) REFERENCES datatypes(code)
);

CREATE TABLE IF NOT EXISTS spectra_raw (
    id INTEGER PRIMARY KEY,  -- AUTOINCREMENT
    row_inserted DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL,
    rid INTEGER NOT NULL,
    arr_idx INTEGER NOT NULL,
    measurement REAL NOT NULL,
    FOREIGN KEY(rid) REFERENCES readings(rid)
);

CREATE TABLE IF NOT EXISTS spectra_processed (
    id INTEGER PRIMARY KEY,  -- AUTOINCREMENT
    row_inserted DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL,
    rid INTEGER NOT NULL,
    arr_idx INTEGER NOT NULL,
    measurement REAL NOT NULL,
    FOREIGN KEY(rid) REFERENCES readings(rid),
);

CREATE TABLE IF NOT EXISTS spectra_peaks (
    id INTEGER PRIMARY KEY,  -- AUTOINCREMENT
    row_inserted DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL,
    rid INTEGER NOT NULL,
    center REAL NOT NULL,
    amplitude REAL NOT NULL,
    fwhm REAL NOT NULL,
    tag TEXT NOT NULL,
    tag_key TEXT NOT NULL,
    FOREIGN KEY(rid) REFERENCES spectra_processed(rid),
);

INSERT INTO datatypes 
VALUES (0, "Spectrometer", "SPECTROMETER", "Intensity", "INTENSITY");

INSERT INTO datatypes VALUES (1, "Motor", "MOTOR", "Amperage", "AMPERAGE");

INSERT INTO readings VALUES (0, 100, 101, 0);  -- Raw and processed spectrometer
INSERT INTO readings VALUES (1, 110, 111, 1);  -- Generic placeholder
INSERT INTO readings VALUES (2, 120, 121, 0);  -- Only raw spectrometer

INSERT INTO spectra_raw VALUES (0, 200, 0, 0, 2.0);
INSERT INTO spectra_raw VALUES (1, 201, 0, 1, 2.1);
INSERT INTO spectra_raw VALUES (2, 202, 0, 2, 2.2);

INSERT INTO spectra_raw VALUES (3, 205, 2, 0, 2.5);
INSERT INTO spectra_raw VALUES (4, 206, 2, 1, 2.6);
INSERT INTO spectra_raw VALUES (5, 207, 2, 2, 2.7);

INSERT INTO spectra_processed VALUES (0, 200, 0, 0, 2.0);
INSERT INTO spectra_processed VALUES (1, 201, 0, 1, 2.1);
INSERT INTO spectra_processed VALUES (2, 202, 0, 2, 2.2);

INSERT INTO spectra_peaks VALUES (0, 300, 0, 310, 320, 330, "Tag0", "TAG0");
INSERT INTO spectra_peaks VALUES (1, 301, 0, 311, 321, 331, "Tag1", "TAG1");
INSERT INTO spectra_peaks VALUES (2, 302, 0, 312, 322, 332, "Tag2", "TAG2");

CREATE TABLE IF NOT EXISTS soil_humidity (
    id INTEGER PRIMARY KEY,  -- AUTOINCREMENT
    row_inserted DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL,
    rid INTEGER PRIMARY KEY,
    measurement REAL NOT NULL,
    FOREIGN KEY(rid) REFERENCES readings(rid)
);

CREATE TABLE IF NOT EXISTS soil_temperature (
    id INTEGER PRIMARY KEY,  -- AUTOINCREMENT
    row_inserted DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL,
    rid INTEGER PRIMARY KEY,
    measurement REAL NOT NULL,
    FOREIGN KEY(rid) REFERENCES readings(rid)
);

CREATE TABLE IF NOT EXISTS weather_humidity (
    id INTEGER PRIMARY KEY,  -- AUTOINCREMENT
    row_inserted DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL,
    rid INTEGER PRIMARY KEY,
    measurement REAL NOT NULL,
    FOREIGN KEY(rid) REFERENCES readings(rid)
);

CREATE TABLE IF NOT EXISTS weather_temperature (
    id INTEGER PRIMARY KEY,  -- AUTOINCREMENT
    row_inserted DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL,
    rid INTEGER PRIMARY KEY,
    measurement REAL NOT NULL,
    FOREIGN KEY(rid) REFERENCES readings(rid)
);

CREATE TABLE IF NOT EXISTS air_pressure (
    id INTEGER PRIMARY KEY,  -- AUTOINCREMENT
    row_inserted DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL,
    rid INTEGER PRIMARY KEY,
    measurement REAL NOT NULL,
    FOREIGN KEY(rid) REFERENCES readings(rid)
);

CREATE TABLE IF NOT EXISTS methane (
    id INTEGER PRIMARY KEY,  -- AUTOINCREMENT
    row_inserted DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL,
    rid INTEGER PRIMARY KEY,
    measurement REAL NOT NULL,
    FOREIGN KEY(rid) REFERENCES readings(rid)
);

CREATE TABLE IF NOT EXISTS ultraviolet (
    id INTEGER PRIMARY KEY,  -- AUTOINCREMENT
    row_inserted DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL,
    rid INTEGER PRIMARY KEY,
    measurement REAL NOT NULL,
    FOREIGN KEY(rid) REFERENCES readings(rid)
);

CREATE TABLE IF NOT EXISTS joint_angle (
    id INTEGER PRIMARY KEY,  -- AUTOINCREMENT
    row_inserted DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL,
    rid INTEGER PRIMARY KEY,
    measurement REAL NOT NULL,
    FOREIGN KEY(rid) REFERENCES readings(rid)
);

CREATE TABLE IF NOT EXISTS joint_speed (
    id INTEGER PRIMARY KEY,  -- AUTOINCREMENT
    row_inserted DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL,
    rid INTEGER PRIMARY KEY,
    measurement REAL NOT NULL,
    FOREIGN KEY(rid) REFERENCES readings(rid)
);

CREATE TABLE IF NOT EXISTS motors (
    id INTEGER PRIMARY KEY,  -- AUTOINCREMENT
    row_inserted DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL,
    rid INTEGER PRIMARY KEY,
    measurement REAL NOT NULL,
    FOREIGN KEY(rid) REFERENCES readings(rid)
);
