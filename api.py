import json
import sys
import traceback

from flask import abort, Blueprint, current_app, Flask, request, jsonify

from database import connect_db, close_db, init_db, get_db

api = Blueprint('api', __name__)


# Cameras?  # Store metadata to confirm that feed was collected
# TODO: Parameters for each call. Start time, end time, ID, etc.
#         parameter for type? or make type endpoint externally visible?
    

def __fetch_results(query, params):
    db = get_db()
    cur = db.execute(query, params)
    rows_dict_list = [dict(row) for row in cur.fetchall()]
    return rows_dict_list
    

def __fetch_specific_readings(table):
    """
    Gathers the readings for a specific table. Returns the results as a list of
    all entries, represented as a dictionary. 
    """
    db = get_db()
    cur = db.execute("""
        SELECT * 
        FROM readings, %s
        WHERE
            readings.rid=%s.rid 
    """ % (table, table))
    
    rows_dict_list = [dict(row) for row in cur.fetchall()]
    return rows_dict_list
    
 
@api.route('/spectrometer/raw/', methods=['GET', 'POST'])    
def spectrometer_raw():
    if request.method == 'POST':
        if request.is_json is not True:
            abort(404)
        body = request.get_json()
        raise NotImplementedError
    else:
        return json.dump(__fetch_specific_readings('spectra_raw'))
    
    
# curl -H "Content-Type: application/json" -X POST -d \
# '{"username":"xyz","password":"xyz"}' '127.0.0.1:5000/spectrometer/processed/'
@api.route('/spectrometer/processed/', methods=['GET', 'POST'])
def spectrometer_processed():
    """ 
    GET returns only the readings and processed table, not the peaks. The use is
    to see which readings have processed spectra, and their waveforms. Peaks can
    be requested through a separate endpoint for individual spectra.
    """  # TODO: Could make this just return the peaks on its own but, ehh...
    if request.method == 'POST':
        if request.is_json is not True:
            abort(404)
        post_json = request.get_json()
        if not (post_json["data"] and post_json["reading"] and post_json["peaks"]):
            abort(400)
        insert_processed_spectra(post_json)
        return('', 201)
    else:
        return json.dumps(__fetch_specific_readings('spectra_processed'))
        
        
@api.route('/spectrometer/processed/peaks/<int:rid>', methods=['GET'])
def spectrometer_peaks(rid):
    query = """
        SELECT * 
        FROM readings, spectra_processed, spectra_peaks
        WHERE
            readings.rid=?
            AND readings.rid=spectra_processed.rid
            AND spectra_peaks.rid=readings.rid
    """
    return json.dumps(__fetch_results(query, [rid]))
    
    
def insert_processed_spectra(obj):
    db = get_db()
    try:
        def value_generator():
            for idx in range(len(obj["data"])):
                yield (obj["reading"], idx, obj["data"][idx])
        
        db.executemany("""
            INSERT INTO
                spectra_processed
                (rid, arr_idx, measurement)
            VALUES
                (?, ?, ?)
        """, value_generator())
        
        peak_entries = [{
            "spectra": obj["reading"],
            "center": peak["center"],
            "amplitude": peak["amplitude"],
            "fwhm": peak["fwhm"],
            "tag": peak["tag"],
            "tag_key": ''.join(e for e in peak["tag"] if e.isalnum()).upper()
        } for peak in obj["peaks"]]
        
        db.executemany("""
            INSERT INTO
                spectra_peaks
                (rid, center, amplitude, tag, tag_key, fwhm)
            VALUES 
                (:spectra, :center, :amplitude, :tag, :tag_key, :fwhm)
        """, peak_entries)
        
        db.commit()
    except Exception as e:
        traceback.print_exc()
        abort(422)

    
@api.route('/soil/', methods=['GET'])
def soil():
    soil_dict = {
        "temperature": __fetch_specific_readings('soil_temperature'),
        "humidity": __fetch_specific_readings('soil_humidity')
    }
    return json.dumps(soil_dict)

    
# These can be hidden. /soil/ returns all.
# Only use on historical database
@api.route('/soil/temperature/', methods=['GET'])
def soil_temperature():
    return json.dumps(__fetch_specific_readings('soil_temperature'))

    
@api.route('/soil/humidity/', methods=['GET'])
def soil_humidity():
    return json.dumps(__fetch_specific_readings('soil_humidity'))


@api.route('/weather/', methods=['GET'])
def weather():
    weather_dict = {
        "temperature": __fetch_specific_readings('air_humidity'),
        "humidity": __fetch_specific_readings('air_humidity'),
        "pressure": __fetch_specific_readings('air_pressure'),
        "methane": __fetch_specific_readings('methane'),
        "uv": __fetch_specific_readings('ultraviolet')
    }
    return json.dumps(weather_dict)

# These can be hidden. /weather/ returns all.
# Only use on historical database
@api.route('/weather/temperature/', methods=['GET'])
def weather_temperature():
    return json.dumps(__fetch_specific_readings('air_temperature'))
    
@api.route('/weather/humidity/', methods=['GET'])
def weather_humidity():
    return json.dumps(__fetch_specific_readings('air_humidity'))
    
@api.route('/weather/pressure/', methods=['GET'])
def weather_pressure():
    return json.dumps(__fetch_specific_readings('air_pressure'))
    
@api.route('/weather/methane/', methods=['GET'])
def weather_methane():
    return json.dumps(__fetch_specific_readings('methane'))
    
@api.route('/weather/uv/', methods=['GET'])
def weather_uv():
    return json.dumps(__fetch_specific_readings('ultraviolet'))

    

@api.route('/navigation/', methods=['GET'])
def navigation():
    raise NotImplementedError
    
# These can be hidden. /location/ returns all
# Only use on historical database
@api.route('/navigation/coordinates/', methods=['GET'])
def navigation_coordinates():
    raise NotImplementedError
    
@api.route('/navigation/tilt/', methods=['GET'])  # Rover not flat
def navigation_tilt():
    raise NotImplementedError
    
@api.route('/navigation/bearing/', methods=['GET'])
def navigation_bearing():
    raise NotImplementedError
    
# TODO: velocity/acceleration/general speed characteristics


# Controls
# TODO: joint angle
# TODO: joint speed

@api.route('/motors/', methods=['GET'])
def motors():
    raise NotImplementedError
    
@api.route('/accelerometers/', methods=['GET'])
def accelerometers():
    raise NotImplementedError


# Power 
@api.route('/power/', methods=['GET'])
def power():
    raise NotImplementedError

# These can be hidden. /power/ returns all
# Only use on historical database
@api.route('/power/packvolt/', methods=['GET'])
def power_packvolt():
    raise NotImplementedError
    
@api.route('/power/cellvolt/', methods=['GET'])
def power_cellvolt():
    raise NotImplementedError