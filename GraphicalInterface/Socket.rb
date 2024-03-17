require 'socket'

class Socket
  attr_accessor :socket

  def initialize(host = 'localhost', port = 2121)
    # Initialize Socket at host and port
    @socket = TCPSocket.new(host, port)
    
    # Read the welcome message from the server
    @socket.recvfrom(1024)
  end

  def get(cmd)
    @socket.send("msz", 0)
    response, _ = @socket.recvfrom(1024)
    response
  end
end