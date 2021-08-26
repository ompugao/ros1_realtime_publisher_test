#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include <std_msgs/Time.h>
#include <realtime_tools/realtime_publisher.h>
 
using Clock = std::chrono::high_resolution_clock;
 
template<class Duration>
using TimePoint = std::chrono::time_point<Clock, Duration>;
 

void callback(const std_msgs::Time::ConstPtr& msg)
{
    TimePoint<std::chrono::duration<double>> t = std::chrono::high_resolution_clock::now();
    std::cout << std::fixed << t.time_since_epoch().count() << "," << msg->data << std::endl;
}

int main(int argc, char * argv[])
{
    ros::init(argc, argv, "receivetest");
    ros::NodeHandle nh("~");

    struct sched_param param;
    // do not use 99 for sched_priority
    // https://rt.wiki.kernel.org/index.php/HOWTO:_Build_an_RT-application#Priority_99
    param.sched_priority = 96;
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
        ROS_WARN("failed to set scheduler priority");
        return 1;
    }

    ros::Subscriber sub = nh.subscribe("/publishtest/hoge", 1, callback);
    ros::spin();
    return 0;
}
