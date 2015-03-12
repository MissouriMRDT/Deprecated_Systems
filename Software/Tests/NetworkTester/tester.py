from tkinter import *
from tkinter import ttk
import socket
    
def sendmessage(*args):
    global connection
    to_send = bytearray.fromhex(Data.get())
    connection.send(to_send)
    print("Sent data ", to_send  )

root = Tk()
root.title("NetworkTestUtility")

print("Waiting for Connection")
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((socket.gethostname(), 11000))
server.listen(5)
connection, addr = server.accept()
print("Connected")

mainframe = ttk.Frame(root, padding="3 3 12 12")
mainframe.grid(column=0, row=0, sticky=(N, W, E, S))
mainframe.columnconfigure(0, weight=1)
mainframe.rowconfigure(0, weight=1)

Data = StringVar()
meters = StringVar()

data_entry = ttk.Entry(mainframe, width=24, textvariable = Data)
data_entry.grid(column=2, row=1, sticky=(W, E))
#feet_entry = ttk.Entry(mainframe, width=7, textvariable=feet)
#feet_entry.grid(column=2, row=1, sticky=(W, E))

ttk.Label(mainframe, textvariable=meters).grid(column=2, row=2, sticky=(W, E))
ttk.Button(mainframe, text="Send", command=sendmessage).grid(column=3, row=3, sticky=W)

ttk.Label(mainframe, text="Data").grid(column=3, row=1, sticky=W)

for child in mainframe.winfo_children(): child.grid_configure(padx=5, pady=5)

data_entry.focus()
root.bind('<Return>', sendmessage)
try:
    root.mainloop()
except:
    print("Shit hit the fan")
    connection.close()
    server.close()
    quit()

