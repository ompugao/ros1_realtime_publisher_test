#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include <std_msgs/Time.h>
#include <realtime_tools/realtime_publisher.h>

int main(int argc, char * argv[])
{
    ros::init(argc, argv, "publishtest");
    ros::NodeHandle nh("~");
    realtime_tools::RealtimePublisher<std_msgs::Time> pub(nh, "hoge", 1);

    struct sched_param param;
    // do not use 99 for sched_priority
    // https://rt.wiki.kernel.org/index.php/HOWTO:_Build_an_RT-application#Priority_99
    param.sched_priority = 96;
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
        ROS_WARN("failed to set scheduler priority");
        return 1;
    }


    while (ros::ok()) {
        auto tloopstart = std::chrono::high_resolution_clock::now();
        if (pub.trylock()) {
            pub.msg_.data = ros::Time::now();
            pub.unlockAndPublish();
        }
        std::this_thread::sleep_until(tloopstart + std::chrono::duration<double>(0.008));
    }
    return 0;
}
