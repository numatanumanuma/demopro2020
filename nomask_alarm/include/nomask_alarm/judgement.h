#ifndef JUDGEMENT_H
#define JUDGEMENT_H

#include <ros/ros.h>
#include "darknet_ros_msgs/BoundingBoxes.h"


class Judgement{
public:
    Judgement();
    ~Judgement();
    void timerCallback(const ros::TimerEvent&);
    void judge();
   
private:
    ros::Timer timer_;
    ros::Subscriber darknet_sub_;

    darknet_ros_msgs::BoundingBoxes results_;
    std::string nomask_class;
    std::string mask_class;

    void darknetCallback(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg);

};

#endif