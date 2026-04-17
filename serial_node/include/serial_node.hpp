#ifndef SERIAL_NODE_HPP
#define SERIAL_NODE_HPP

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/bool.hpp"
#include <libserial/SerialPort.h>
#include <libserial/SerialStream.h>

class SerialNode : public rclcpp::Node
{
public:
    SerialNode();

private:
    void readSerial();
    void sendPing();
    void checkConnection();

    void cmdCallback(const std_msgs::msg::String::SharedPtr msg);

    LibSerial::SerialPort serial_port;
    std::thread read_thread;

    std::mutex serial_mutex;
    std::string port;

    std::atomic<bool> arduino_alive{false};
    std::chrono::steady_clock::time_point last_response_time;
    
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr status_pub;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr info_pub;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr sensor_pub;

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr cmd_sub;

    rclcpp::TimerBase::SharedPtr ping_timer;
    rclcpp::TimerBase::SharedPtr watchdog_timer;
};

#endif // SERIAL_NODE_HPP