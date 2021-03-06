#include <unistd.h>

#include <iostream>
#include <vector>

#include "Command.h"
#include "Environment.h"

int main() {
    Environment env;
    int return_status = 0;
    std::string line;

    while(true) {
        Command c;

        std::cout << return_status << " -> " << std::flush;

        std::getline(std::cin, line);
        
        if (std::cin.eof()) {
            break;
        }

        int status = c.parse(line);

        if (status < 0) {
            if (status != -1) {
                std::cerr << "Invalid syntax" << std::endl;
            }
            continue;
        }

        int code = 0;
        try {
            code = env.run(c);
        } catch(const RunnerException& e) {
            std::cerr << "Could not run " << e.what() << std::endl;
            continue;
        }
        std::cout << "Exited with code " << code << std::endl;

    }
}
