import sqlite3
from flask import Flask, current_app, g


def connect_db():
    """ Connects to the telemetry database """
    rv = sqlite3.connect(current_app.config['DATABASE'])
    rv.row_factory = sqlite3.Row  # Convert from tuple to dictionary
    return rv
    
    
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
    with current_app.open_resource('datatypes.sql', mode='r') as f:
        db.cursor().executescript(f.read())
    db.commit()
    
    
def close_db(error):
    """ Closes the database """
    if hasattr(g, 'sqlite_db'):
        g.sqlite_db.close()