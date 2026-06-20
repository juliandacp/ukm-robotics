#include<rclcpp/rclcpp.hpp>
#include<geometry_msgs/msg/twist.hpp>
#include<turtlesim/msg/pose.hpp>
#include<turtlesim/srv/teleport_absolute.hpp>
#include<turtlesim/srv/set_pen.hpp>
#include<cmath>
#include<memory>

using namespace std;

class TurtleController : public rclcpp::Node{
public:
    TurtleController() : Node("turtle_controller"){
        current_pose.x = 2.0;
        current_pose.y = 10.0;
        current_pose.theta = 0.0;
        
        vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        pose_sub_ = this->create_subscription<turtlesim::msg::Pose>(
            "/turtle1/pose", 10,
            std::bind(&TurtleController::poseCallback, this, std::placeholders::_1));
        
        setPen(false); 
        teleportTurtle(2.0, 10.0, 0.0);
        rclcpp::sleep_for(std::chrono::seconds(1));
        setPen(true); 
        
        rclcpp::sleep_for(std::chrono::seconds(1));
    }
    
    void setPen(bool on){
        auto client = this->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
        
        while(!client->wait_for_service(std::chrono::seconds(1))){
            if(!rclcpp::ok()){
                RCLCPP_ERROR(this->get_logger(), "Error");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "Pen not available");
        }
        
        auto request = std::make_shared<turtlesim::srv::SetPen::Request>();
        if(on){
            request->r = 255;
            request->g = 255;
            request->b = 255;
            request->width = 2;
            request->off = false;
            RCLCPP_INFO(this->get_logger(), "Pen");
        }else{
            request->off = true;
            RCLCPP_INFO(this->get_logger(), "No pen");
        }
        
        auto future = client->async_send_request(request);
        
        if(rclcpp::spin_until_future_complete(this->get_node_base_interface(), future) ==
            rclcpp::FutureReturnCode::SUCCESS){
            RCLCPP_INFO(this->get_logger(), "Pen changed");
        }else{
            RCLCPP_ERROR(this->get_logger(), "Failed to call pen");
        }
    }
    
    void teleportTurtle(double x, double y, double theta){
        auto client = this->create_client<turtlesim::srv::TeleportAbsolute>("/turtle1/teleport_absolute");
        
        while(!client->wait_for_service(std::chrono::seconds(1))){
            if(!rclcpp::ok()){
                RCLCPP_ERROR(this->get_logger(), "Error");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "Teleport not available");
        }
        
        auto request = std::make_shared<turtlesim::srv::TeleportAbsolute::Request>();
        request->x = x;
        request->y = y;
        request->theta = theta;
        
        auto future = client->async_send_request(request);
        
        if(rclcpp::spin_until_future_complete(this->get_node_base_interface(), future) ==
            rclcpp::FutureReturnCode::SUCCESS){
            RCLCPP_INFO(this->get_logger(), "Turtle teleported to x=%.2f, y=%.2f, theta=%.2f", x, y, theta);
        }else{
            RCLCPP_ERROR(this->get_logger(), "Failed to teleport");
        }
    }
    
    void poseCallback(const turtlesim::msg::Pose::SharedPtr msg){
        current_pose = *msg;
    }
    
    void moveToPoint(double x, double y){
        auto cmd_vel = geometry_msgs::msg::Twist();
        rclcpp::Rate rate(10);
        
        int max_iterations = 300;
        int iterations = 0;
        
        while(rclcpp::ok() && iterations < max_iterations){
            double dx = x - current_pose.x;
            double dy = y - current_pose.y;
            double distance = sqrt(dx*dx + dy*dy);
            
            if(distance < 0.1){
                break;
            }
            
            double angle_to_target = atan2(dy, dx);
            double angle_diff = angle_to_target - current_pose.theta;
            
            while(angle_diff > M_PI) angle_diff -= 2.0 * M_PI;
            while(angle_diff < -M_PI) angle_diff += 2.0 * M_PI;
            
            if(abs(angle_diff) > 0.1){
                cmd_vel.linear.x = 0.0;
                cmd_vel.angular.z = 0.5 * angle_diff;
            }else{
                cmd_vel.linear.x = 0.8 * distance;
                cmd_vel.angular.z = 0.0;
            }
            
            if(cmd_vel.linear.x > 1.0) cmd_vel.linear.x = 1.0;
            if(cmd_vel.angular.z > 1.0) cmd_vel.angular.z = 1.0;
            if(cmd_vel.angular.z < -1.0) cmd_vel.angular.z = -1.0;
            
            vel_pub_->publish(cmd_vel);
            rate.sleep();
            rclcpp::spin_some(shared_from_this());
            iterations++;
        }
        //Stop
        cmd_vel.linear.x = 0.0;
        cmd_vel.angular.z = 0.0;
        vel_pub_->publish(cmd_vel);
        rclcpp::sleep_for(std::chrono::milliseconds(500));
    }
    
    void drawLetterJ(double start_x, double start_y){
        setPen(true);
        moveToPoint(start_x + 1.0, start_y + 0.3);
        moveToPoint(start_x + 0.5, start_y);
        moveToPoint(start_x, start_y + 0.5);
    }
    
    void drawLetterU(double start_x, double start_y){
        setPen(false);
        teleportTurtle(3.0, 10.0, 0.0);

        setPen(true);
        moveToPoint(start_x, start_y);
        moveToPoint(start_x + 1.0, start_y);
        moveToPoint(start_x + 1.0, start_y + 2.0);
    }
    
    void drawLetterL(double start_x, double start_y){
        setPen(false);
        teleportTurtle(5.0, 10.0, 0.0);

        setPen(true);
        moveToPoint(start_x, start_y);
        moveToPoint(start_x + 1.2, start_y);
    }
    
    void drawLetterI(double start_x, double start_y){
        setPen(false);
        teleportTurtle(7.0, 10.0, 0.0);

        setPen(true);
        moveToPoint(start_x + 1.0, start_y + 2.0);
        
        setPen(false);
        moveToPoint(start_x + 0.5, start_y + 2.0);

        setPen(true);
        moveToPoint(start_x + 0.5, start_y);
        
        setPen(false);
        moveToPoint(start_x, start_y);

        setPen(true);
        moveToPoint(start_x + 1.0, start_y);
    }
    
    void drawJuli(){
        double start_y = 8.0;
        
        drawLetterJ(1.0, start_y);        
        drawLetterU(3.0, start_y);
        drawLetterL(5.0, start_y);
        drawLetterI(7.0, start_y);
        
        setPen(false);
        teleportTurtle(1.0, 1.0, 0.0);
    }

private:
    turtlesim::msg::Pose current_pose;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_pub_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_sub_;
};

int main(int argc, char** argv){
    rclcpp::init(argc, argv);
    auto controller = std::make_shared<TurtleController>();
    
    rclcpp::sleep_for(std::chrono::seconds(2));
    
    controller->drawJuli();
    
    rclcpp::shutdown();
    return 0;
}