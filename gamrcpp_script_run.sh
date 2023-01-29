#!/bin/bash

#  run the script by ./script_name.sh ws_x ws_y rc

# get command line arguments
ws_x=$1
ws_y=$2
rc=$3

# set the number of iterations
iterations=10
sleep_time=2
# change directory to catkin workspace
cd ~/gamrcpp_ws

# source the ros workspace
source devel/setup.bash

#gnome-terminal -x bash -c "rosclean purge -y && pkill roscore ; roscore ; exec bash" &
# run the specified number of iterations
for i in $(seq 1 $iterations)
do
    # clean up previous ros processes and start a new roscore
    rosclean purge -y && pkill roscore ; roscore &
    sleep $sleep_time

    # run the first command in a new terminal
    gnome-terminal -x bash -c "rosrun gamrcpp_pkg gamrcppMainExecutable _ws_x:=$ws_x _ws_y:=$ws_y _rc:=$rc _test:=$i ; exec bash" &
    
    pid1=$!
    
    sleep $sleep_time

    # run the second command in a new terminal
    gnome-terminal -x bash -c "rosrun gamrcpp_pkg start_robots $rc ; exec bash" &
    
    pid2=$!
    
    # wait for the nodes to stop running
    while [ "$(rosnode list | grep gamrcpp_node)" != "" ]; do
        sleep 1
    done
    
    # kill the terminal windows
    ps -ef | grep "rosrun gamrcpp_pkg gamrcppMainExecutable" | awk '{print $2}' | xargs kill -9
    ps -ef | grep "rosrun gamrcpp_pkg start_robots" | awk '{print $2}' | xargs kill -9
    
done



