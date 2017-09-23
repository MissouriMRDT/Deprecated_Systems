import functools
import os
import struct
import yaml

# from rovecomm import RoveComm

# rc = RoveComm()

# TODO: What the almighty fuck
datatype_to_fmtstr = {
    'uint8': '>B',
    'int16': '>h',
    'uint16': '>H',
    'struct': '>HH',  # This is a singular edge case. Damn you Josh Reed.
    'int32[2]': '>II',
    'int16[2]': '>HH',
    'single[6]': '>ffffff',
    'single': '>f',
}

CONFIG_YAML = os.path.join(os.path.dirname(__file__), 'dataId.yml')
ROVER_IP = '127.0.0.1'

def callback(data, format):
    data_tuple = struct.unpack(data, format)
    print("Data: %s\nFormat: %s" % (data, format))
    # TODO: Switch on name/format to insert to DB
                                                
def configure_rovecomm():
    with open(CONFIG_YAML, 'r') as f:
        rovecomm_settings = yaml.safe_load(f)
    print("datapoints: %s" % type(datapoints))
    
    
    rc.subscribe(ROVER_IP)
    for point in datapoints:
        fmt = datatype_to_fmtstr[point["DataType"]]
        rc.callbacks[point["DataId"]] = functools.partial(callback,
                                                          format=fmt)
                                                        
                                                        
if __name__=="__main__":
    configure_rovecomm()