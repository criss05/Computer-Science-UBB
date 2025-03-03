import pickle
import socket
import struct

from select import select

try:
    sock=socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
except Exception:
    print("Could not create the socket")
    exit(-1)

sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
try:
    sock.bind(('192.168.0.10', 1234))
    sock.listen(10)
except Exception as e:
    print(e)
    print("Could not bind.")
    exit(-2)

master=[]
clients=[]
crt=0

def sendAll(connected):
        global master, sock
        if connected==0:
            msg=f"client Connected"
        else:
            msg=f"client Disconnected"
        for fds in master:
            if fds!=sock: #and crt!=fds:
                clients_=pickle.dumps(clients)
                fds.send(msg.encode())
                fds.send(clients_)


if __name__ == '__main__':
    master.append(sock)
    while True:
        read, _, _=select(master, [], [])
        for fd in read:
            crt=fd
            if fd==sock:
                c, addr=sock.accept()
                print("New client")
                master.append(c)
            else:
                try:
                    msg=fd.recv(1024)
                except Exception:
                    continue
                if len(msg)<=0:
                    sendAll(1)
                    master.remove(fd)
                    fd.close()
                else:
                    port=msg.decode()
                    clients.append(int(port))
                    sendAll(0)

