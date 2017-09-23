import functools
import os
import struct
import yaml

from rovecomm import RoveComm


fmt_dict = {
    'uint8': '>B',
    'int16': '>h',
    'uint16': '>H',
    'struct': '>HH',  # This is a singular edge case. Damn you Josh Reed.
    'int32[2]': '>II',
    'int16[2]': '>HH',
    'single[6]': '>ffffff',
    'single': '>f',
}
rc = RoveComm()

CONFIG_YAML = os.path.join(os.path.dirname(__file__), 'dataId.yml')
ROVER_IP = '127.0.0.1'

def callback(data, format):
    data_tuple = struct.unpack(data, format)
    print("Data: %s\nFormat: %s" % (data, format))
    # TODO: Any preprocessing
    # TODO: Switch to insertion into database
 
 
def configure_rovecomm():
    with open(CONFIG_YAML, 'r') as f:
        rovecomm_settings = yaml.safe_load(f)
    data_ids = rovecomm_settings['DataIds']
    ip_addrs = rovecomm_settings['IpAddresses']
        
    for addr in ip_addrs:
        rc.subscribe(addr["Address"])
    for id in data_ids:
        try:
            fmt = fmt_dict[id["DataType"]]
            rc.callbacks[id["DataId"]] = functools.partial(callback,
                                                           format=fmt)
        except KeyError:
            continue


if __name__=="__main__":
    configure_rovecomm()