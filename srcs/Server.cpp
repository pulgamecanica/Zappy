//***************************//
//*Template by pulgamecanica*//
//***************************//

extern "C" {
	#include <unistd.h>
	#include <strings.h>
}

#include <algorithm>

#include <toml++/toml.hpp>

#include "Zappy.inc"
#include "Server.hpp"
#include "Command.hpp"
#include "Player.hpp"

namespace Zappy {
	Server::Server(std::string toml_file, std::string default_lang, int players_port, int spectators_port):
		players_port_(players_port), spectators_port_(spectators_port), health_(Booting) {
		// Setup TOML configuration file
		{
			// Open Toml file
			toml::table tbl = toml::parse_file(toml_file);
			// Setup configuration for all the languages
			auto toml_langs = tbl["languages"];
			if (toml::array* arr = toml_langs.as_array())
    	{
	        // visitation with for_each() helps deal with heterogeneous data
	        arr->for_each([&](auto&& el)
	        {
	            if constexpr (toml::is_string<decltype(el)>) {
	            	if (DEBUG)
	                std::cout << "Loading " << BLUE << *el << ENDC << " configuration" << std::endl;
	        			configs_.push_back(Config(tbl, *el));
	        		} else {
	    					throw std::runtime_error("Error: languages can only contain strings");
	        		}
	        });
	    } else {
	    	throw std::runtime_error("Error: languages is not defined or is not an array");
	    }
	    // Check that default language is included
			std::vector<Config>::iterator it = std::find(configs_.begin(), configs_.end(), default_lang);
			if (it == std::end(configs_))
	    	throw std::runtime_error("Error: default language is not included in the toml file");
			curr_config_ = &(*it);
		}
		std::cout << YELLOW << "=> Booting Zappy in " << (DEBUG ? "debug" : "development") << " mode" << ENDC << std::endl;
		std::cout << YELLOW << "=> ZappyServer version: " << GREEN << Server::VERSION << ENDC << std::endl;
		std::cout << YELLOW << "=> Run `./Zappy --help` for more startup options" << ENDC << std::endl;
		// Create players & spectators sockets (IPV4, TCP | man socket)
		players_socket_ = socket(AF_INET, SOCK_STREAM, 0);
		if (players_socket_ == -1) {
			throw std::runtime_error(std::string("players socket()") + std::string(strerror(errno)));
		}
		spectators_socket_ = socket(AF_INET, SOCK_STREAM, 0);
		if (spectators_socket_ == -1) {
			throw std::runtime_error(std::string("spectators socket()") + std::string(strerror(errno)));
		}
		// Set sockets to reusable (avoid port binding lag) (man 7 setsockopt & man 7 socket)
		int enable = 1;
		if (setsockopt(players_socket_, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) == -1) {
			throw std::runtime_error(std::string("players setsockopt()") + std::string(strerror(errno)));
		}
		if (setsockopt(spectators_socket_, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) == -1) {
			throw std::runtime_error(std::string("spectators setsockopt()") + std::string(strerror(errno)));
		}
		// Set socket to non blocking
		setnonblocking(players_socket_);
		setnonblocking(spectators_socket_);
		// Bind sockets, to port and 0.0.0.0 (localhost)
		players_sockaddr_.sin_family = AF_INET;
		players_sockaddr_.sin_port = htons(players_port_);
		players_sockaddr_.sin_addr.s_addr = htonl(INADDR_ANY);
		if (bind(players_socket_, (struct sockaddr *)&players_sockaddr_, sizeof(players_sockaddr_)) == -1) {
			throw std::runtime_error(std::string("players bind()") + std::string(strerror(errno)));
		}
		spectators_sockaddr_.sin_family = AF_INET;
		spectators_sockaddr_.sin_port = htons(spectators_port_);
		spectators_sockaddr_.sin_addr.s_addr = htonl(INADDR_ANY);
		if (bind(spectators_socket_, (struct sockaddr *)&spectators_sockaddr_, sizeof(spectators_sockaddr_)) == -1) {
			throw std::runtime_error(std::string("spectators bind()") + std::string(strerror(errno)));
		}
		// Setup Listen sockets
		if (listen(players_socket_, Server::BACKLOG) == -1) {
			throw std::runtime_error(std::string("players listen()") + std::string(strerror(errno)));
		}
		if (listen(spectators_socket_, Server::BACKLOG) == -1) {
			throw std::runtime_error(std::string("spectators listen()") + std::string(strerror(errno)));
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
	   		throw std::runtime_error(std::string("players ADD epoll_ctl()") + std::string(strerror(errno)));
			}
		}
		// Add spectators socket to epoll list
  	{
  		struct epoll_event ev;
	   	ev.events = EPOLLIN | EPOLLET;
	   	ev.data.fd = spectators_socket_;
	   	if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, spectators_socket_, &ev) == -1) {
	   		throw std::runtime_error(std::string("spectators ADD epoll_ctl()") + std::string(strerror(errno)));
			}
		}
		// Add standard input to the epoll list
		{
			setnonblocking(0);
  		struct epoll_event ev;
	   	ev.events = EPOLLIN | EPOLLET;
	   	ev.data.fd = 0;
	   	if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, 0, &ev) == -1) {
	   		throw std::runtime_error(std::string("std input ADD epoll_ctl()") + std::string(strerror(errno)));
			}
		}
		// Setup the timestamp
		{
			if(gettimeofday(&created_at_, NULL) == -1) {
				throw std::runtime_error(std::string("gettimeofday()") + std::string(strerror(errno)));
			}
		}
		std::cout << BLUE << "* Players:\thttp://localhost:" << players_port_ << ENDC << std::endl;
		std::cout << BLUE << "* Spectators:\thttp://localhost:" << spectators_port_<< ENDC << std::endl;
		health_ = Running;
	}

	Server::~Server() {
		close(players_socket_);
		close(spectators_socket_);
		close(epoll_fd_);
		// close all clients and spectators
		// TODO
		for (std::map<int, Client *>::const_iterator i = players_.begin(); i != players_.end(); ++i) {
			delete i->second;
		}
		players_.clear();
		spectators_.clear();
		configs_.clear();
		health_ = EndOfLife;
		if (DEBUG)
			std::cout << "Server" << " destroyed" << std::endl;
	}

	const std::map<int, Client *> & Server::get_players() const {
		return players_;
	}

	const std::vector<std::string> Server::get_list_of_supported_languages() const {
		std::vector<std::string> langs;

		for (std::vector<Config>::const_iterator it = configs_.begin(); it != configs_.end(); ++it) {
			langs.push_back(it->get_language_acronym());
		}
		return (langs);
	}

	int Server::total_players() const { return (players_.size()); }

	int Server::total_spectators() const { return (spectators_.size()); }

	const Config & Server::get_config() const { return (*curr_config_); } 

	void Server::stop_server() {
		health_ = ServerHealth::EndOfLife;
	};

	bool	Server::check_health(enum ServerHealth check) const {
		return (check == health_);
	}

	ssize_t Server::current_timestamp() const {
		struct timeval tv;

		if(gettimeofday(&tv, NULL) == -1) {
			throw std::runtime_error(std::string("gettimeofday()") + std::string(strerror(errno)));
		}
		return (tv.tv_sec - created_at_.tv_sec);
	}

	const std::string Server::get_creation_date() const {
		std::string date;
		ssize_t t;

		t = ((created_at_.tv_sec * 1000) + (created_at_.tv_usec / 1000)) / 1000;

		date = ctime(&t);
		date.pop_back();
		return (date);
	}

	void	Server::set_config(const std::string lang_acronym) {
		std::vector<Config>::iterator it = std::find(configs_.begin(), configs_.end(), lang_acronym);
		if (it == std::end(configs_)) {
			std::cout << RED << "Error" << ENDC << " Couldn't change the configuration '" << lang_acronym << "' is not supported" << std::endl;
		} else {
			curr_config_ = &(*it);
			if (DEBUG)
				std::cout << YELLOW << "[Server]\t" << GREEN << "Language [" << BLUE << lang_acronym << GREEN << "]" << ENDC << std::endl;
		}
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
			players_.insert(std::pair<int, Client *>(fd, new Player(fd)));
		} else if (spectators_socket_ == socket) {
			// players_.insert(std::pair<int, Player>(fd, fd));
			spectators_.push_back(fd);
		}
	}

	void	Server::remove_client(int fd) {
		if (DEBUG)
			std::cout << YELLOW << "[Server]\t" << RED << "remove\t" << ENDC << fd << std::endl; 
		if (is_fd_player(fd)) {
			delete players_.at(fd);
			players_.erase(fd);
		} else {
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
				if(errno != EAGAIN && errno != EWOULDBLOCK && fd != 0)
					remove_client(fd);
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

	void Server::update() {
		static struct epoll_event ev;
		int conn_sock, nfds;

		nfds = epoll_wait(epoll_fd_, events_, Server::MAX_EPOLL_EVENTS, 0);
		if (nfds == -1) {
		   throw std::runtime_error(std::string("epoll_wait") + std::string(strerror(errno)));
		}
		for (int n = 0; n < nfds; ++n) {
			if (is_server_socket(events_[n].data.fd)) {
				conn_sock = accept_client(events_[n].data.fd);
				if (conn_sock == -1) {
					throw std::runtime_error(std::string("accept") + std::string(strerror(errno)));
	      }
	      setnonblocking(conn_sock);
	      // Add fd to epoll list
				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = conn_sock;
				if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, conn_sock, &ev) == -1) {
					throw std::runtime_error(std::string("epoll_ctl: conn_sock") + std::string(strerror(errno)));
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
						std::cout << YELLOW << "[Server]\t" << BLUE << *c << ENDC ":" << YELLOW << (c->is_valid() ? "valid" : "invalid") << ENDC << std::endl;
					if (c->is_valid()) {
						c->execute(*this);
					} else {
						write(0, "command not found\n", 18); 
					}
					delete c;
					// TODO
					if (check_health(Running))
						write(1, "$> ", 3);
				}
				else if (is_fd_player(events_[n].data.fd)) {
					// handle players
					Client * p = players_.at(events_[n].data.fd);
					Command * c = p->parse_command();
					if (c->is_valid()) {
						c->execute(*this, p);
					} else {
						p->broadcast("KO: command not found\n");
					}
					std::cout << *p << ":" << *c << std::endl;
					delete c;
					// Player should parse the command
					// Each player might choose his own configuration (language)
					// Command & cmd = player.parse_command();
					// execute_command(cmd);
					// p.broadcast(cmd);
				}
				// do_use_fd(events_[n].data.fd);
		   }
		}
		// Testing Spectators send
		for (std::vector<int>::iterator it = spectators_.begin(); it != spectators_.end(); ++it) {
			std::ostringstream ss;

			ss << "\033[H\033[2J\n";
			ss << GREEN << "Zappy v" << BLUE << Server::VERSION << ENDC
				<< " - [" << BLUE << get_creation_date() << ENDC << "]" << std::endl;
			ss << " * " << curr_config_->get("total_players") << ":" << BLUE << total_players() << ENDC << std::endl;
			ss << " * " << curr_config_->get("total_spectators") << ":" << BLUE << total_spectators() << ENDC << std::endl;
			ss << " * " << curr_config_->get("server_life") << ":" << BLUE << current_timestamp() << ENDC << "s" << std::endl;
			if (send(*it, ss.str().c_str(), ss.str().length(), MSG_DONTWAIT | MSG_NOSIGNAL) == -1) {
				if (errno == EPIPE) {
					if (DEBUG)
						std::cout << YELLOW << "[Server]\t" << RED << "Error" << ENDC << " would send SIGPIPE, problems with socket" << std::endl;
					remove_client(*it);
					break;
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