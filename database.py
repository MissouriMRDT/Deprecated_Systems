import sqlite3
import sys
from flask import Flask, current_app, g


def connect_db():
    """ Connects to the telemetry database """
    rv = sqlite3.connect(current_app.config['DATABASE'])
    rv.row_factory = sqlite3.Row  # Convert from tuple to dictionary
    return rv
    
    
def gen_test_data():
    """ Populates the database with test data """
    db = get_db()
    with current_app.open_resource('data.sql', mode='r') as f:
        db.cursor().executescript(f.read())
    print("Test data genreated", file=sys.stderr)
    db.commit()
    print("Changes committed")
    
    
def get_db():
    """ Opens connection to database. """
    if not hasattr(g, 'sqlite_db'):
        g.sqlite_db = connect_db()
    return g.sqlite_db
    

def init_db():
    """ Applies the database schema. """
    db = get_db()
    # Execute `schema.sql` file on database
    with current_app.open_resource('schema.sql', mode='r') as f:
        db.cursor().executescript(f.read())
    print("Schema generated", file=sys.stderr)
    with current_app.open_resource('datatypes.sql', mode='r') as f:
        db.cursor().executescript(f.read())
    print("Data Types populated", file=sys.stderr)
    db.commit()
    print("Changes committed", file=sys.stderr)
    
    
def close_db(error):
    """ Closes the database """
    if hasattr(g, 'sqlite_db'):
        g.sqlite_db.close()