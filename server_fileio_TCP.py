#This sample program, based on the one in the standard library documentation, receives incoming messages and echos them back to the sender. It starts #by creating a TCP/IP socket.
import socket
import sys

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#Then bind() is used to associate the socket with the server address. In this case, the address is localhost, referring to the current server, and the #port number is 10000.

# Bind the socket to the port
server_address = ('127.0.0.1', 10000)
print >>sys.stderr, 'starting up on %s port %s' % server_address
sock.bind(server_address)

#Calling listen() puts the socket into server mode, and accept() waits for an incoming connection.

# Listen for incoming connections
sock.listen(1)
fos = open("server.txt", "w")
bufs = ""

while True:
    # Wait for a connection
    print >>sys.stderr, 'waiting for a connection'
    connection, client_address = sock.accept()
#accept() returns an open connection between the server and client, along with the address of the client. The connection is actually a different #socket on another port (assigned by the kernel). Data is read from the connection with recv() and transmitted with sendall().

    try:
        print >>sys.stderr, 'connection from', client_address
        while True:
            bufs = connection.recv(16)
            if bufs:
                fos.write(bufs)
            else:
                print >>sys.stderr, 'all contents written, no more data'
                break
            
    finally:
        # Clean up the connection
        connection.close()
        fos.close()
        r = raw_input("do you want to stop listening? ")
        if r == 'y':
            break

#When communication with a client is finished, the connection needs to be cleaned up using close(). This example uses a try:finally block to ensure #that close() is always called, even in the event of an error.
