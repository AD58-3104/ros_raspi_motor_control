#include <string>
#include <ros/ros.h>
#include <ros_raspi_motor_control/raspi_servo.h>
namespace RASPI_MOTOR
{

    class raspi_motor_control
    {
    public:
        raspi_motor_control(ros::NodeHandle &nodeHandle);
        ~raspi_motor_control();
        void count_plus_1();
        bool is_even();
        ros::Publisher pub;

    private:
        ros::NodeHandle &nodeHandle_;
        std::string topic_name;
        std::int32_t published_times;

    };

    raspi_motor_control::raspi_motor_control(ros::NodeHandle &nodeHandle)
        : nodeHandle_(nodeHandle),published_times(0),topic_name("move_servo")
    {
        pub = nodeHandle_.advertise<ros_raspi_motor_control::raspi_servo>(topic_name,4);
        ROS_INFO("Successfully launched node.");
    }

    raspi_motor_control::~raspi_motor_control()
    {
    }

    void raspi_motor_control::count_plus_1(){
        ++published_times;
    }

    bool raspi_motor_control::is_even(){
        if(published_times % 2 ==0){
            return true;
        }
        else{
            return false;
        }
    }

} // namespace RASPI_MOTOR

int main(int argc, char **argv)
{
    ros::init(argc, argv, "RASPI_MOTOR");
    ros::NodeHandle nodeHandle("~");
    ros::Rate loop_rate(1);
    RASPI_MOTOR::raspi_motor_control MOTOR(nodeHandle);
    ros_raspi_motor_control::raspi_servo msg;
    msg.pinNumber = 12;
    while(ros::ok()){
        if(MOTOR.is_even()){
        msg.degree = 40;
        }
        else{
            msg.degree = -40;
        }
        MOTOR.pub.publish(msg);
        MOTOR.count_plus_1();
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}