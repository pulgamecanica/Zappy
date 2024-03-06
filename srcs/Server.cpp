//***************************//
//*Template by pulgamecanica*//
//***************************//

extern "C" {
	#include <sys/socket.h>
	#include <unistd.h>
	#include <strings.h>
}

#include <algorithm>

#include <toml++/toml.hpp>

#include "Zappy.inc"
#include "Server.hpp"
#include "Command.hpp"

namespace Zappy {
	Server::Server(int players_port, int spectators_port):
		players_port_(players_port), spectators_port_(spectators_port) {
		std::cout << YELLOW << "=> Booting Zappy in " << (DEBUG ? "debug" : "development") << " mode" << ENDC << std::endl;
		std::cout << YELLOW << "=> ZappyServer version: " << GREEN << Server::VERSION << ENDC << std::endl;
		std::cout << YELLOW << "=> Run `./Zappy --help` for more startup options" << ENDC << std::endl;
		// Create players & spectators sockets (IPV4, TCP | man socket)
		players_socket_ = socket(AF_INET, SOCK_STREAM, 0);
		if (players_socket_ == -1) {
			perror("players socket()");
			exit(EXIT_FAILURE);
		}
		spectators_socket_ = socket(AF_INET, SOCK_STREAM, 0);
		if (spectators_socket_ == -1) {
			perror("spectators socket()");
			exit(EXIT_FAILURE);
		}
		// Set sockets to reusable (avoid port binding lag) (man 7 setsockopt & man 7 socket)
		int enable = 1;
		if (setsockopt(players_socket_, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) == -1) {
			perror("players setsockopt()");
			exit(EXIT_FAILURE);
		}
		if (setsockopt(spectators_socket_, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) == -1) {
			perror("spectators setsockopt()");
			exit(EXIT_FAILURE);
		}
		// Set socket to non blocking
		setnonblocking(players_socket_);
		setnonblocking(spectators_socket_);
		// Bind sockets, to port and 0.0.0.0 (localhost)
		players_sockaddr_.sin_family = AF_INET;
		players_sockaddr_.sin_port = htons(players_port_);
		players_sockaddr_.sin_addr.s_addr = htonl(INADDR_ANY);
		if (bind(players_socket_, (struct sockaddr *)&players_sockaddr_, sizeof(players_sockaddr_)) == -1) {
			perror("players bind()");
			exit(EXIT_FAILURE);
		}
		spectators_sockaddr_.sin_family = AF_INET;
		spectators_sockaddr_.sin_port = htons(spectators_port_);
		spectators_sockaddr_.sin_addr.s_addr = htonl(INADDR_ANY);
		if (bind(spectators_socket_, (struct sockaddr *)&spectators_sockaddr_, sizeof(spectators_sockaddr_)) == -1) {
			perror("spectators bind()");
			exit(EXIT_FAILURE);
		}
		// Setup Listen sockets
		if (listen(players_socket_, Server::BACKLOG) == -1) {
			perror("players listen()");
			exit(EXIT_FAILURE);
		}
		if (listen(spectators_socket_, Server::BACKLOG) == -1) {
			perror("spectators listen()");
			exit(EXIT_FAILURE);
		}
		std::cout << BLUE << "Zappy listening in single thread mode" << ENDC << std::endl;
		std::cout << BLUE << "* C++ version:\t20" << ENDC << std::endl;
		std::cout << BLUE << "* Server PID:\t" << GREEN << getpid() << ENDC << std::endl;
		// Epoll setup
		epoll_fd_ = epoll_create1(0);
		setnonblocking(epoll_fd_);
		// Add players socket to epoll list
		{
	   	struct epoll_event ev;
	   	ev.events = EPOLLIN | EPOLLET;
	   	ev.data.fd = players_socket_;
	   	if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, players_socket_, &ev) == -1) {
	   		perror("players ADD epoll_ctl()");
				exit(EXIT_FAILURE);
			}
		}
		// Add spectators socket to epoll list
  	{
  		struct epoll_event ev;
	   	ev.events = EPOLLIN | EPOLLET;
	   	ev.data.fd = spectators_socket_;
	   	if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, spectators_socket_, &ev) == -1) {
	   		perror("spectators ADD epoll_ctl()");
				exit(EXIT_FAILURE);
			}
		}
		// Add standard input to the epoll list
		{
			setnonblocking(0);
  		struct epoll_event ev;
	   	ev.events = EPOLLIN | EPOLLET;
	   	ev.data.fd = 0;
	   	if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, 0, &ev) == -1) {
	   		perror("std input ADD epoll_ctl()");
				exit(EXIT_FAILURE);
			}
		}
		std::cout << BLUE << "* Players:\thttp://localhost:" << players_port_ << ENDC << std::endl;
		std::cout << BLUE << "* Spectators:\thttp://localhost:" << spectators_port_<< ENDC << std::endl;
	}

	Server::~Server() {
		close(players_socket_);
		close(spectators_socket_);
		close(epoll_fd_);
		// close all clients and spectators
		// TODO
		players_.clear();
		spectators_.clear();
		if (DEBUG)
			std::cout << "Server" << " destroyed" << std::endl;
	}

	bool Server::is_server_socket(int fd) {
		return (players_socket_ == fd || spectators_socket_ == fd);
	}

	bool	Server::is_fd_player(int fd) {
		return (players_.find(fd) != players_.end());
	}

	int Server::accept_client(int socket) {
		int fd;
		socklen_t addrlen;

		fd = -1;
		if (players_socket_ == socket) {
			addrlen = sizeof(players_sockaddr_);
			fd = accept(players_socket_, (struct sockaddr *)&players_sockaddr_, &addrlen);
		} else if (spectators_socket_ == socket) {
			addrlen = sizeof(spectators_sockaddr_);
			fd = accept(spectators_socket_, (struct sockaddr *)&spectators_sockaddr_, &addrlen);
		}
		if (DEBUG && fd != -1)
			std::cout << GREEN << "Accepted client (" << BLUE << (socket == players_socket_ ? "Player" : "Spectator") <<  GREEN <<")" << ENDC << std::endl; 
		return fd;
	}

	void Server::add_client(int socket, int fd) {
		if (DEBUG)
			std::cout << YELLOW << "[Server]\t" << GREEN << "add\t" << ENDC << fd << std::endl; 
		if (players_socket_ == socket) {
			players_.insert(std::pair<int, Player>(fd, fd));
		} else if (spectators_socket_ == socket) {
			spectators_.push_back(fd);
		}
	}

	void	Server::remove_client(int fd) {
		if (DEBUG)
			std::cout << YELLOW << "[Server]\t" << RED << "remove\t" << ENDC << fd << std::endl; 
		if (is_fd_player(fd))
			players_.erase(fd);
		else {
			std::vector<int>::const_iterator pos = std::find(spectators_.begin(), spectators_.end(), fd);
			spectators_.erase(pos);
		}
		close(fd);
	}

	const std::string Server::handle_client_input_or_disconnect(int fd) {
		char buf[Server::RECV_BUFFER];
		std::string msg;
		ssize_t read_bytes;

		for (;;) {
			bzero(buf, Server::RECV_BUFFER);
			if (fd == 0)
				read_bytes = read(fd, buf, Server::RECV_BUFFER);
			else
				read_bytes = recv(fd, buf, Server::RECV_BUFFER, MSG_DONTWAIT);
			// Remove client on error
			if (read_bytes == -1) {
				if(errno == EAGAIN || errno == EWOULDBLOCK)
					break;
				else if (fd != 0)
					remove_client(fd);
				else
					break;
			}
			// Remove client on disconnection
			if (read_bytes == 0 && fd != 0) {
				remove_client(fd);
				break;
			}
			// Protect append function from throwing lenght error when -1
			// Return message when the client sends a message
			msg.append(buf, read_bytes);
		}
		return (msg);
	}

	void Server::run(int * sig) {
		struct epoll_event ev;
		int conn_sock, nfds;

		write(1, "$> ", 3);
		while(*sig) {
			nfds = epoll_wait(epoll_fd_, events_, Server::MAX_EPOLL_EVENTS, -1);
			if (nfds == -1) {
			   perror("epoll_wait");
			   break ;
			}
			for (int n = 0; n < nfds; ++n) {
				if (is_server_socket(events_[n].data.fd)) {
					conn_sock = accept_client(events_[n].data.fd);
					if (conn_sock == -1) {
						perror("accept");
		        exit(EXIT_FAILURE);
		      }
		      setnonblocking(conn_sock);
		      // Add fd to epoll list
					ev.events = EPOLLIN | EPOLLET;
					ev.data.fd = conn_sock;
					if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, conn_sock, &ev) == -1) {
						perror("epoll_ctl: conn_sock");
						exit(EXIT_FAILURE);
					}
					add_client(events_[n].data.fd, conn_sock);
				} else {
					// read message
					// handle disconnection if need be
					// read full message
					// Pass message if player
					// Server handles Client messages
					const std::string & client_msg = handle_client_input_or_disconnect(events_[n].data.fd);
					if (client_msg.empty())
						continue ;
					if (DEBUG)
						std::cout << YELLOW << "[Server]\t" << GREEN << "recv:" << BLUE << client_msg.length() << ENDC << "bytes" << std::endl;
					// Server will never use spectator messages (uni-directional communication)
					// Server will send to spectator the game status at a given rate/s
					if (events_[n].data.fd == 0) {
						// handle standard input from the server [BONUS]
						Command * c = Command::parse_server_command(client_msg);
						if (DEBUG)
							std::cout << "[Server]\t" << BLUE << *c << ENDC ":" << YELLOW << (c->is_valid() ? "valid" : "invalid") << std::endl;
						if (c->is_valid()) {
							c->execute(*this);
							std::cout << c->get_output() << std::endl;
						}
						delete c;
						write(1, "$> ", 3);
					}
					else if (is_fd_player(events_[n].data.fd)) {
						// handle players
						// Player & p = players_.at(events_[n].data.fd);

						// Player should parse the command
						// Each player might choose his own configuration (language)
						// Command & cmd = player.parse_command();
						// execute_command(cmd);
						// p.broadcast(cmd);
					}
					// do_use_fd(events_[n].data.fd);
			   }
			}
		}
	}


	std::ostream& operator<<(std::ostream& s, const Server& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}


/**
 * List of commands: 
 * 
 * [GENERAL]
 * help
 * status
 * exit
 * [GAME COMMANDS]
 * 
 * 
 * 
 * 
 * 
 */