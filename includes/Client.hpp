//***************************//
//*Template by pulgamecanica*//
//***************************//

/**
 * Clients can send commands to the server, any commands
 * The server is in charge of validating the client commands
 * A command might or might not have a reply
 * Clients can receive messages from the server without warning
 **/
#ifndef __CLIENT_HPP__
# define __CLIENT_HPP__

extern "C" {
	#include <sys/time.h>
}

#include <vector>
#include <iostream>

namespace Zappy {
	

	class Client {
		public:
			enum ClientType {
				Player,
				Spectator,
				Graphic	
			};
			Client(const Client&) = default;
			~Client();
			static constexpr const char * CLIENT_TYPES_STR[3] = {"Player", "Spectator", "Graphic"};
			Client&	operator= (const Client&) = default; // const for safety... not super nesessary
			ssize_t uptime() const; // Seconds
			int			get_fd() const;
			enum ClientType get_client_type() const;
		protected:
			Client(int fd, ClientType type);
			const int							fd_;
			const enum ClientType	client_type_;
			struct timeval				created_at_;
	};

	std::ostream&	operator<<(std::ostream&, const Client&);
}
#endif

