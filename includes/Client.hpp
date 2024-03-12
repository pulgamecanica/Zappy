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
				Graphic,
				Error
			};
			Client(const Client&) = default;
			virtual ~Client();
			static constexpr const char * CLIENT_TYPES_STR[4] = {"Player", "Spectator", "Graphic", "Error"};
			Client&									operator= (const Client&) = default; // const for safety... not super nesessary
			ssize_t 								uptime() const; // Seconds
			int											get_fd() const;
			void										broadcast(std::string msg);
			enum ClientType 				get_client_type() const;
		protected:
			Client(int fd, ClientType type);
			const int							fd_;
			enum ClientType				client_type_;
			ssize_t								created_at_ms_;
	};

	std::ostream&	operator<<(std::ostream&, const Client&);
}
#endif

