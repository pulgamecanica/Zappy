//***************************//
//*Template by pulgamecanica*//
//***************************//

extern "C" {
	#include <sys/socket.h>
	#include <unistd.h>
}

#include "Zappy.inc"
#include "Server.hpp"

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

	bool	Server::is_fd_spectator(int fd) {
		return (players_.find(fd) != players_.end());
	}
			
	bool	Server::is_fd_client(int fd) {
		return (spectators_.find(fd) != spectators_.end());
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
		if (players_socket_ == socket) {
			players_.insert(std::pair<int, Player>(fd, fd));
		} else if (spectators_socket_ == socket) {
			spectators_.insert(std::pair<int, Spectator>(fd, fd));
		}
	}

	void Server::run(int * sig) {
		struct epoll_event ev;
		int conn_sock, nfds;

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
					if (is_fd_client(events_[n].data.fd)) {
						// Player & p = players_.at(events_[n].data.fd);
						// p.handle_io();
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
