import json
import os
#Training
from flask import Flask

from api import api, soil
from database import close_db, gen_test_data, get_db, init_db


app = Flask(__name__)
app.config.from_object(__name__)

app.config.update({
    'DATABASE': os.path.join(app.root_path, 'Rove.db'),
    'SECRET_KEY': 'development key',
    'USERNAME': 'admin',
    'PASSWORD': 'default'
})

# Following line for eventual progression.
# Separate configuration file loaded into envvar, then set
app.config.from_envvar('ROVEDB_SETTINGS', silent=True)

app.register_blueprint(api)
    
    
@app.cli.command('initdb')
def initdb_command():
    """ Initializes the database. """
    init_db()
    
@app.cli.command('gendata')
def gendata_command():
    """ Generates test data for the database. """
    init_db()
    gen_test_data()
    
    
@app.teardown_appcontext
def teardown_db(error):
    """ Closes the database at the teardown of app """
    close_db(error)