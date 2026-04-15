# ros2 version
Humble

# Installation
Add the code inside your ros2 workspace inside the src folder

If you clone the reposatory directly into the ros2_ws folder, you file structure will have the following structure:
/ros2_ws/src
└── Robotised_Demining_ros2
    ├── controller_receiver
    ├── dig_mode
    ├── drive_mode
    ├── mode_selector
    ├── README.md
    └── rover_launch
In this case the command:
colcon build --base-paths src/Robotised_Demining_ros2

Should be used to build the packages. This will point ros2 to the correct folder

## Common issues
It may be neccesary to remove the build, install, and log folders by using the command:
cd ~/ros2_ws
rm -rf build install log

It may also be neccesary to reconfigure the ros2 enviroment:
cd ~/ros2_ws
source /opt/ros/humble/setup.bash

# Usage
## Launch all the ros2 nodes
usefull for testing
ros2 launch rover_launch total.launch.py

## Launch pi nodes
ros2 launch rover_launch pi.launch.py

## Launch pc nodes
ros2 launch rover_launch pc.launch.py
