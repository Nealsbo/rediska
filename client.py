import time, sys, socket

args1 = sys.argv

msg = args1[1] + ' ' + args1[2] + ' ' + args1[3]
print(msg)

clientsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientsocket.connect(('localhost', 7780))

for i in range(0, 10):
	clientsocket.send(msg.encode('utf-8'))
	data = clientsocket.recv(1024)
	print(str(data))
	time.sleep(2)

clientsocket.close()
	

print(str(data))
