PORT = if ARGV.any? then ARGV[0] else 4242 end
require 'socket'

SERVER_PORT = 2121

# Create a UDP socket
client_socket = UDPSocket.new

# Set the server address and port
server_addr = Socket.sockaddr_in(SERVER_PORT, '127.0.0.1')

# Send data to the server
message = "Hello, server!"
client_socket.send(message, 0, server_addr)

puts "Data sent to server: #{message}"

# Receive response from the server
response, _ = client_socket.recvfrom(1024)

puts "Response from server: #{response}"

# Close the socket
client_socket.close
