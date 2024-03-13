require 'socket'

PORT = if ARGV.any? then ARGV[0] else 4242 end

s = TCPSocket.new 'localhost', PORT

while (42)
  if line = s.gets # Read lines from socket
    puts line         # and print them
  end
end

s.close             # close socket when done
