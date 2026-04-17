#ifndef DRIVE_MODE_HPP
#define DRIVE_MODE_HPP

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/bool.hpp"
#include <libserial/SerialPort.h>
#include <libserial/SerialStream.h>

class DriveMode : public rclcpp::Node
{
public:
    DriveMode();

private:
    void switch_mode(const std_msgs::msg::String::SharedPtr msg);
    void drive_mode_logic(const sensor_msgs::msg::Joy::SharedPtr msg);
    std::string is_ready_to_switch();

    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_data;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_mode;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_sensor_data;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_information_data;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr subscription_serial_status;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr confirmation_publisher;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr drive_command_publisher;

    // Variables
    std::string current_mode;
    sensor_msgs::msg::Joy::SharedPtr latest_joy_msg;

    bool debug_mode = false; // Set to true to enable debug logs
    bool is_command_received = false; // Flag to track if the command has been acknowledged by the Arduino
    bool serial_alive = false; // Flag to track if the serial connection is alive
    std::string information_data = ""; // Variable to store the latest information data received from the Arduino
};

#endif // DRIVE_MODE_HPP
