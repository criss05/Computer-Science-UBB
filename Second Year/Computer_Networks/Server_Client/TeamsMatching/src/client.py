import pickle
import socket
import threading
import random

try:
    sock=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except Exception:
    print("Could not create the socket")
    exit(-1)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
port=0
students=[]

def serverConnection():
    global students, port
    sock.connect(('192.168.0.10', 1234))
    sock.send(port.encode())
    while True:
        try:
            msg=sock.recv(256)
            print(msg.decode())
            msg=sock.recv(256)
            students_l=pickle.loads(msg)
            students=[] # fara
            for s in students_l:
                students.append(s)
            print(students)
        except Exception:
            continue

try:
    chat_sock=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
except Exception:
    print("Could not create the server")
    exit(-2)
chat_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)



learning=['a', 'v', 'h']
time=[-1,1,2,3]
subject_list=['math', 'english']

learning_style=learning[random.randint(0,2)]
availability=[time[random.randint(0,3)] for _ in range(7)]
subject=subject_list[random.randint(0,1)]

def sendData():
    global students, port
    while True:
        for std in students:
            if std!=port:
                chat_sock.sendto(f"{learning_style}".encode(), ('192.168.0.10', int(std)))
                chat_sock.sendto(pickle.dumps(availability), ('192.168.0.10', int(std)))
                chat_sock.sendto(f"{subject}".encode(), ('192.168.0.10', int(std)))



def receiveData():
    global students, port
    while True:
        try:
            learn_st, addr1=chat_sock.recvfrom(256)
            learn_st=learn_st.decode()
            availab, addr1=chat_sock.recvfrom(256)
            availab=pickle.loads(availab)
            subj, addr1=chat_sock.recvfrom(256)
            subj=subj.decode()
            if learn_st==learning_style:
                if subj==subject:
                    ok=0
                    for a in availab:
                        for b in availability:
                            if a==b:
                                ok=1
                    if ok==1:
                        print('192.168.0.10', port)
                        exit(0)
            print(availability)
        except Exception:
            continue



if __name__ == '__main__':
    port=input("Port:")
    print(f"Preferecnes: {learning_style}, {availability}, {subject}")
    chat_sock.bind(('0.0.0.0', int(port))) #era sus inainte
    threads=[]
    server_thread=threading.Thread(target=serverConnection)
    send_thread=threading.Thread(target=sendData)
    receive_thread=threading.Thread(target=receiveData)
    threads.append(server_thread)
    threads.append(send_thread)
    threads.append(receive_thread)
    server_thread.start()
    send_thread.start()
    receive_thread.start()
    for t in threads:
        t.join()