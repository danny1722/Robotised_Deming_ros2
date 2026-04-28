#ifndef DIG_MODE_HPP
#define DIG_MODE_HPP

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/bool.hpp"

class DigMode : public rclcpp::Node
{
public:
    DigMode();

private:
    void switch_mode(const std_msgs::msg::String::SharedPtr msg);
    void dig_mode_logic(const sensor_msgs::msg::Joy::SharedPtr msg);
    std::string is_ready_to_switch();

    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_data;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_mode;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_sensor_data;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_debug_data;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_error_data;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr subscription_serial_status;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr confirmation_publisher;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr dig_command_publisher;

    // Variables
    std::string current_mode;
    sensor_msgs::msg::Joy::SharedPtr latest_joy_msg;

    bool debug_mode = false; // Set to true to enable debug logs
    bool serial_alive = false; // Track the status of the serial connection
    std::string debug_data = ""; // Variable to store the latest debug data received from the Arduino
};

#endif // DIG_MODE_HPP
