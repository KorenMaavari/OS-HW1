#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "Commands.h"
#include "signals.h"

int main(int argc, char* argv[]) {

    if(signal(SIGINT , ctrlCHandler)==SIG_ERR) {
        perror("smash error: failed to set ctrl-C handler");
    }

//    struct sigaction alarm_action;
//    /*
//    ----------timeout----------
//    alarm_action.sa_handler = alarmHandler;
//    */
//    sigemptyset(&alarm_action.sa_mask);
//    alarm_action.sa_flags = SA_RESTART;
//    if (sigaction(SIGALRM, &alarm_action, nullptr) == -1) {
//        perror("smash error: failed to set timeout handler");
//    }
//
//    struct sigaction action;
//    /*
//    ----------timeout----------
//    action.sa_handler = alarmHandler;
//    */
//    sigemptyset(&action.sa_mask);
//    action.sa_flags = SA_RESTART;
//    if(sigaction(SIGALRM, &action, NULL) == -1){
//        perror("smash error: failed to set timeout handler");
//    }

    SmallShell& smash = SmallShell::getInstance();
    while(true) {
        std::cout << smash.getName() << "> ";
        std::string cmd_line;
        std::getline(std::cin, cmd_line);
        // i
        


        
        smash.executeCommand(cmd_line.c_str());
    }
    return 0;
}