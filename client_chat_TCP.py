#The client program sets up its socket differently from the way a server does. Instead of binding to a port and listening, it uses connect() to attach #the socket directly to the remote address.

import socket
import sys

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
server_address = ('127.0.0.1', 10000)
print >>sys.stderr, 'connecting to %s port %s' % server_address
sock.connect(server_address)
data = ""
#After the connection is established, data can be sent through the socket with sendall() and received with recv(), just as in the server.

try:
    # Look for the response
    while data != "quit":
        message = raw_input("type message: ")
        print >>sys.stderr, 'sending "%s"' % message
        sock.sendall(message)
        data = sock.recv(16)        
        print >>sys.stderr, 'received "%s"' % data

finally:
    print >>sys.stderr, 'closing socket'
    sock.close()

#When the entire message is sent and a copy received, the socket is closed to free up the port.
