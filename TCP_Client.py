import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# server address
svrIP = input(('Server IP(default: 127.0.0.1): '))
if svrIP == '':
    svrIP = '127.0.0.1'

# port
port = input('port(default: 2500): ')
if port == '':
    port = 2500
else:
    port = int(port)

sock.connect((svrIP, port))
print('Connected to ' + svrIP)

while True:
    msg = input('Sending message: ')

    if not msg:
        continue

    try:
        sock.send(msg.encode())
    except:
        print('deconnection...')
        break

    try:
        msg = sock.recv(1024)
        if not msg:
            print('deconnection.')
            break
        print('Received message: {}'.format(msg.decode()))
    except:
        print('deconnection.')
        break

sock.close()

