#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void executeCommand(const char* command)
{
    pid_t pid = fork();

    if (pid == 0)
    {
        // child process
        system(command);
        exit(0);
    }
}

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        std::cout << "Usage: script ws_x ws_y rc" << std::endl;
        return 1;
    }

    int ws_x = atoi(argv[1]);
    int ws_y = atoi(argv[2]);
    int rc = atoi(argv[3]);
    int sleep_time = 2
    std::string command1 = "gnome-terminal --command='source ~/gamrcpp_ws/devel/setup.bash && rosclean purge -y && pkill roscore ; roscore'";
    executeCommand(command1.c_str());
    sleep(sleep_time);

    for (int i = 0; i < 10; ++i)
    {
        std::string command2 = "gnome-terminal --command='source ~/gamrcpp_ws/devel/setup.bash && rosrun gamrcpp_pkg gamrcppMainExecutable _ws_x:="
        + std::to_string(ws_x) + " _ws_y:=" + std::to_string(ws_y) + " _rc:=" + std::to_string(rc) + " _test:=" + std::to_string(i + 1) + "'";
        executeCommand(command2.c_str());
        sleep(sleep_time);

        std::string command3 = "gnome-terminal --command='source ~/gamrcpp_ws/devel/setup.bash && rosrun gamrcpp_pkg start_robots " + std::to_string(rc) + "'";
        executeCommand(command3.c_str());
        sleep(sleep_time);

        std::string command4 = "gnome-terminal --command='pkill -f gamrcpp_node'";
        executeCommand(command4.c_str());
        sleep(sleep_time);
    }

    return 0;
}
