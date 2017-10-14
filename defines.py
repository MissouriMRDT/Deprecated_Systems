import os
import re
import sys
import yaml

# Location of YAML file
CONFIG_YAML = os.path.join(os.path.dirname(__file__), 'dataId.yml')


first_cap_re = re.compile('(.)([A-Z][a-z]+)')
all_cap_re = re.compile('([a-z0-9])([A-Z])')


def tupleize(addr):
    return ', '.join(addr.split('.'))
    
    
def constantize(variable):
    modded = '_'.join(variable.split(' '))
    subbed = all_cap_re.sub(r'\1_\2', first_cap_re.sub(r'\1_\2', modded))
    return subbed.upper()

    
    
if __name__ == "__main__":
    with open(CONFIG_YAML, 'r') as f:
        roveCommData = yaml.safe_load(f)
        
    # .upper() to make case insensitive.
    subsystems = set([ did['Subsystem'].upper() for did in roveCommData['DataIds'] ])
    # TODO: Better argparsing
    # TODO: Break if they have arguments but none are valid.
    shown_systems = [ arg.upper() for arg in sys.argv[1:] if arg.upper() in subsystems ]
    
    defines_list = []
    
    if len(shown_systems) == 0:        
        for data_id in roveCommData['DataIds']:
            if not (data_id["Name"] == "Reserved" or data_id["Name"] == ""):
                defines_list.append("const uint16", constantize(data_id["Name"])+"_ID",  "= " + str(data_id["Id"]))
    else:
        for data_id in roveCommData['DataIds']:
            if not (data_id["Name"] == "Reserved" or data_id["Name"] == "") and data_id["Subsystem"].upper() in shown_systems:
                const_str = "const uint16 {0}_ID = {1}".format(constantize(data_id["Name"]), data_id["Id"])
                defines_list.append(const_str)
                
    # TODO: Figure out how to get minimal number of IP addresses through args.     
    for ip in roveCommData['IpAddresses']:
        # const uint8_t <device> = <ip_addr>
        const_str = "const uint8_t {0} [4] = {{{1}}};".format(constantize(ip['Device']) + "_IP", tupleize(ip['Address']))
        defines_list.append(const_str)
    
    with open('defines.h', 'w') as f:
        f.writelines("\n".join(defines_list))