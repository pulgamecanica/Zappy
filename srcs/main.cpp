//***************************//
//*Template by pulgamecanica*//
//***************************//
    
extern "C" {
    #include <signal.h>
    #include <string.h>
    #include <fcntl.h>
    #include <stdlib.h>
    #include <time.h>
}

#include <toml++/toml.hpp>

#include "Zappy.inc"
#include "GameEngine.hpp"

int g_stop_sig = 42;

static void sighandler(int signal) {
    std::cout << "Signal Received: [" << RED << signal << ENDC ":" << BLUE << strsignal(signal) << ENDC << "]" << std::endl;
    g_stop_sig = 0;
}

static void setup_signals() {
    struct sigaction sigIntHandler;
    // SETUP SIGNALS
    sigIntHandler.sa_handler = sighandler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGTERM, &sigIntHandler, NULL);
    sigaction(SIGSTOP, &sigIntHandler, NULL);
    sigaction(SIGINT, &sigIntHandler, NULL);
    sigaction(SIGKILL, &sigIntHandler, NULL);
    sigaction(SIGQUIT, &sigIntHandler, NULL);
}

void setnonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl()");
        exit(EXIT_FAILURE);
    }
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl()");
        exit(EXIT_FAILURE);     
    }
}


ssize_t gettimeofday_ms() {
    struct timeval tv;

    if(gettimeofday(&tv, NULL) == -1) {
        throw std::runtime_error(std::string("gettimeofday()") + std::string(strerror(errno)));
    }
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int main(int argc, char *argv[])
{
    // Seed rand
    srand (time(NULL));
    /**
     * Params:
     * -x <width>
     * -y <height>
     * -c <clients> --clients-per-team
     * [-t]         --time-divider-unit         // default 100
     * [-l <name>]  --default-language=<name>   // default "en"
     * [-f <path>]  --toml-file=<path>          // default "conf.toml"
     * [-P]         --players-port=0000         // default 4242
     * [-S]         --spectators-port=0000      // default 2121
     * [-T]         --connection-timeout        // default 60000ms<=>60s<=>1min
    **/
    int opt;
    std::string lang("en");
    std::string file_name("conf.toml");
    int players_port(4242);
    int spectators_port(2121);
    int default_time(100);
    int w(-1), h(-1), num_players(-1), timeout(60000);
    std::vector<std::string> teams;

    setup_signals();
    try {
        while ((opt = getopt(argc, argv, "l:f:P:S:t:x:y:c:T:hn")) != -1) {
            switch (opt) {
            case 'l':
                lang.assign(optarg);
                break ;
            case 'f':
                file_name.assign(optarg);
                break ;
            case 'P':
                players_port = std::stoi(optarg);
                break ;
            case 'S':
                spectators_port = std::stoi(optarg);
                break;
            case 't':
                default_time = std::stoi(optarg);
                break;
            case 'x':
                w = std::stoi(optarg);
                if (w < 1)
                    throw std::runtime_error("width < 1");
                break;
            case 'y':
                h = std::stoi(optarg);
                if (h < 1)
                    throw std::runtime_error("height < 1");
                break;
            case 'c':
                num_players = std::stoi(optarg);
                if (num_players < 1)
                    throw std::runtime_error("num_players < 1");
                break;
            case 'T':
                timeout = std::stoi(optarg);
                if (timeout < 1000)
                    throw std::runtime_error("timeout < 1000");
                break;
            case 'h':
                std::cout << "Help" << std::endl;
                // print_help();
                return (0);
            case 'n':                
                for (int i = optind; i < argc; ++i) {
                    std::string team(argv[i]);

                    if (team.empty() || team.starts_with('-'))
                        break ;
                    if (DEBUG)
                        std::cout << YELLOW << "[Server]\t" << GREEN << "add team:" << BLUE << team << ENDC << std::endl;
                    teams.push_back(team);
                }
                break;
            default:
                // -n team\_name\_1 team\_name\_2 ...
               fprintf(stderr, "" \
                    "Usage: %s -x <width> -y <height> -c <# clients> -n team <team2> ... [-t <time>] [-f <file>] [-l <lang>] [-P <port>] [-S <port>]\n" \
                    "\t -x <width> world width\n" \
                    "\t -y <height> world height\n" \
                    "\t -c <# clients> number of clients authorized per team at the beginning of the game\n" \
                    "\t -n team [<team2>] ... teams\n" \
                    "\t [-t <ms>] time unit divider (the greater t is, the faster the game will go, default 100)\n" \
                    "\t [-T <ms>] connection timeout for the players (disconnect if not joined a room after <ms> default 1 minute)\n" \
                    "\t [-f configuration file] for server messages (default conf.toml)\n" \
                    "\t [-l acronym] default language for the server (default en)\n" \
                    "\t [-P] port for the players (default 4242)\n" \
                    "\t [-S] port for the spectators (default 2121)\n",
                       argv[0]);
               exit(EXIT_FAILURE);
            }
        }
    } catch (std::exception &e) {
        std::cerr << RED << "Error: " << e.what() << ENDC " ("
            << BLUE << "option[" << ENDC << (char)opt << BLUE  << "]"
            << " => Invalid Arg [" << RED << optarg << BLUE "]"
            << ENDC << ")" << std::endl;
        return (1);
    }
    if (w == -1 || h == -1) {
        std::cerr << RED << "Error:" << ENDC <<" [-x, -y] Width & Height must be provided" <<
            std::endl << "./Zappy -h for more information" << std::endl;
        return (1);
    }
    if (num_players == -1) {
        std::cerr << RED << "Error:" << ENDC <<" [-c] # Clients must be provided " <<
            std::endl << "./Zappy -h for more information" << std::endl;
        return (1);
    }
    if (teams.empty()) {
        std::cerr << RED << "Error:" << ENDC <<" [-n team <team2> ...] Server must have at least one team" <<
            std::endl << "./Zappy -h for more information" << std::endl;
        return (1);
    }
    try {
        Zappy::GameEngine trantor(teams, default_time, file_name, lang, players_port, spectators_port,
            {w, h}, num_players, timeout);
        trantor.start(&g_stop_sig);
        // Zappy::Server s;
    } catch (const toml::parse_error& err) {
        std::cerr
            << "Error parsing file '" << *err.source().path
            << "':\n" << RED << err.description() << ENDC
            << "\n\t(" << err.source().begin << ")\n";
        return (1);
    } catch (std::exception &e) {
        std::cerr << RED << e.what() << ENDC << std::endl;
        return (1);
    }
    std::cout << YELLOW << "Thank you for using the " << GREEN "Zappy Server" << ENDC << " :)" << std::endl;
    return (0);
}
