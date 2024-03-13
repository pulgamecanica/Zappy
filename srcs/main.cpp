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
    // SETUP SIGNALE
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
     * -l <name> --default-language=<name>  // default en
     * -f <path> --toml-file=<path>                 // default conf.toml
     * -P        --players-port=0000                // default 4242
     * -S        --viewers-port=0000                // default 2121
    **/
    int opt;
    std::string lang("en");
    std::string file_name("conf.toml");
    int players_port(4242);
    int spectators_port(2121);
    int default_time(100);


    /* The "-l" option specifies the default language. */
    /* The "-f" modifies default file `conf.toml`. */
    /* The "-P" sets the Players port. */
    /* The "-S" sets the Spectators port. */
    setup_signals();
    try {
        while ((opt = getopt(argc, argv, "l:f:P:S:t:")) != -1) {
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
            case 'h':
                std::cout << "Help" << std::endl;
                // print_help();
                return (0);
            default:
               fprintf(stderr, "Usage: %s [-t time] [-f conf file] [-l default language] [-P players port] [-S spectators-port]\n",
                       argv[0]);
               exit(EXIT_FAILURE);
            }
        }
        Zappy::GameEngine trantor(default_time, file_name, lang, players_port, spectators_port);
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
