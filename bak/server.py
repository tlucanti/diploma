import socketserver
import socket

class TCPserver(socketserver.BaseRequestHandler):
    def handle(self):
        self.data = self.request.recv(1024).strip()
        print('{} wrote:'.format(self.client_address[0]))
        print(self.data)
        #self.request.sendall(self.data)
        self.request.sendall(b'1234567890')

class UDPserver(socketserver.BaseRequestHandler):
    def handle(self):
        data = self.request[0].strip()
        print('{} wrote:'.format(self.client_address[0]))
        print(data)
        socket.sendto(data, self.client_address)

def run_tcp_server():
    socketserver.TCPServer.allow_reuse_address = True
    with socketserver.TCPServer((HOST, PORT), TCPserver) as server:
        server.serve_forever()

def run_udp_server():
    socketserver.UDPServer.allow_reuse_address = True
    with socketserver.UDPServer((HOST, PORT), UDPserver) as server:
        server.serve_forever()

def udp_server():
    UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
    for i in range(1):
        print('sending')
        UDPClientSocket.sendto(b'12345' * 10000, ('0.0.0.0', 10001))
        print('sent ok')
    print('waiting to reveive')
    msgFromServer = UDPClientSocket.recvfrom(5)
    print('Message from Server {}'.format(msgFromServer[0]))

if __name__ == '__main__':
    #run_udp_server()
    udp_server()
