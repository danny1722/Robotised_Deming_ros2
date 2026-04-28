///////////////////////////////////////////////////////////////////////////////////
// File description:
///////////////////////////////////////////////////////////////////////////////////

#include "dig_mode.hpp"

DigMode::DigMode() : Node("dig_mode"), latest_joy_msg(nullptr)
{
    subscription_data = this->create_subscription<sensor_msgs::msg::Joy>(
        "/controller_data",
        10,
        std::bind(&DigMode::dig_mode_logic, this, std::placeholders::_1)
    );

    subscription_mode = this->create_subscription<std_msgs::msg::String>(
        "/selected_mode",
        10,
        std::bind(&DigMode::switch_mode, this, std::placeholders::_1)
    );

    subscription_serial_status = this->create_subscription<std_msgs::msg::Bool>(
        "status",
        10,
        [this](const std_msgs::msg::Bool::SharedPtr msg) {
            if (debug_mode) {
                RCLCPP_INFO(this->get_logger(), "Serial status updated: %s", msg->data ? "Alive" : "Dead");
            }
            serial_alive = msg->data;
        }
    );

    subscription_debug_data = this->create_subscription<std_msgs::msg::String>(
        "debug",
        10,
        [this](const std_msgs::msg::String::SharedPtr msg) {
            if (debug_mode) {
                RCLCPP_INFO(rclcpp::get_logger("DigMode"), "Debug: %s", msg->data.c_str());
            }
            debug_data = msg->data;
        }
    );

    subscription_sensor_data = this->create_subscription<std_msgs::msg::String>(
        "sensor",
        10,
        [](const std_msgs::msg::String::SharedPtr msg) {
            RCLCPP_INFO(rclcpp::get_logger("DigMode"), "Sensor Data: %s", msg->data.c_str());
        }
    );

    subscription_error_data = this->create_subscription<std_msgs::msg::String>(
        "error",
        10,
        [](const std_msgs::msg::String::SharedPtr msg) {
            RCLCPP_ERROR(rclcpp::get_logger("DigMode"), "Error: %s", msg->data.c_str());
        }
    );

    confirmation_publisher = this->create_publisher<std_msgs::msg::String>("/mode_switch_confirmation", 10);
    dig_command_publisher = this->create_publisher<std_msgs::msg::String>("cmd", 10);

    RCLCPP_INFO(this->get_logger(), "Dig Mode Node Started");
}

void DigMode::switch_mode(const std_msgs::msg::String::SharedPtr msg)
{
    std::string requested_mode = msg->data;

    if (requested_mode == "dig_to_drive" && current_mode == "dig") {
        std_msgs::msg::String confirm_msg;
        confirm_msg.data = is_ready_to_switch();
        confirmation_publisher->publish(confirm_msg);
    }
    else if (requested_mode == "dig") {
        current_mode = "dig";
    }
    else if (requested_mode == "drive") {
        current_mode = "drive";
    }
}

std::string DigMode::is_ready_to_switch()
{
    // Check if rover is stationary by examining joystick input
    if (!latest_joy_msg) {
        if (debug_mode) {
            RCLCPP_WARN(this->get_logger(), "No joystick data available");
        }
        return "No joystick data available";

    }

    // All drive control axes must be 0 for the rover to be considered stationary
    if (std::abs(latest_joy_msg->axes[0]) > 0 || 
        std::abs(latest_joy_msg->axes[1]) > 0 || 
        std::abs(latest_joy_msg->axes[2]) > 0 || 
        std::abs(latest_joy_msg->axes[3]) > 0) {

        if (debug_mode) {
            RCLCPP_WARN(this->get_logger(), "Jostick inputs is not zero, cannot switch modes");
        }
        return "Joystick inputs is not zero";
    }

    // Add additional conditions here:
    // - Check arm position is safe
    // - Check sensors are ready
    // etc.

    return "Switch confirmed";
}

void DigMode::dig_mode_logic(const sensor_msgs::msg::Joy::SharedPtr msg)
{
    latest_joy_msg = msg;
    if (current_mode == "dig") {
        // Implement the logic for controlling the excavator in dig mode based on joystick input
    }
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DigMode>());
    rclcpp::shutdown();
    return 0;
}
