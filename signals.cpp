#include <iostream>
#include <signal.h>
#include <sys/wait.h>
#include "signals.h"
#include "Commands.h"

using namespace std;

//void ctrlCHandler(int sig_num) {
//  if (sig_num == SIGINT) {
//        cout << "smash: got ctrl-C" << endl;
//
//        // Retrieve the current foreground process ID
//        pid_t foreground_pid = SmallShell::getInstance().getPid();
//
//        if (foreground_pid != -1) {
//            // Send SIGINT to the foreground process
//            if (kill(foreground_pid, SIGINT) == -1) {
//                perror("smash error: failed to send SIGINT");
//            }
//        }
//    }
//}


void ctrlCHandler(int sig_num) {
    std::cout << "smash: got ctrl-C" << std::endl;
    JobsList* jobsList = SmallShell::getInstance().getJobsList();
    for (auto & job : *jobsList->getJobsList())
    {
        if(job.getStatus() == JobsList::JobEntry::Status::fg)
        {
            int status;
            pid_t result = waitpid(job.getJobPid(), &status, WNOHANG);
            if (result == 0) {
                // Child still alive
                if (kill(job.getJobId(), sig_num) == -1)
                    perror("smash error: kill failed");
                std::cout << "smash: process " << job.getJobId() << " was killed" << std::endl;
            }
        }
    }
    // If there is no process running in the foreground, then the smash should ignore them.
}


/*
----------timeout----------
void alarmHandler(int sig_num) {
  time_t current_time = time(nullptr);

    // Check if any timed commands have timed out
    for (auto &timed_cmd : timed_commands_list) {
        if (current_time - timed_cmd.start_time >= timed_cmd.timeout_duration) {
            // Command has timed out
            std::cerr << "smash: " << timed_cmd.cmd_line << " timed out!" << std::endl;

            // Send SIGKILL to the command's process
            kill(timed_cmd.pid, SIGKILL);
        }
    }
}
*/

