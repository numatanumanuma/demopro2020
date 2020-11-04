#include "nomask_alarm/judgement.h"
   
Judgement::Judgement(){
    ros::NodeHandle nh("~");
    timer_ = nh.createTimer(ros::Duration(0.05), &Judgement::timerCallback, this);
    darknet_sub_ = nh.subscribe("/darknet_ros/bounding_boxes", 100,
        &Judgement::darknetCallback, this);
    nomask_class = "no_maskman";
    mask_class = "maskman";
    limit_time_ = 3.0;
}

Judgement::~Judgement(){

}

void Judgement::darknetCallback(const darknet_ros_msgs::BoundingBoxes::ConstPtr& results) {
    results_ = *results;
}

void Judgement::timerCallback(const ros::TimerEvent&){
    
}

bool Judgement::judge(){
    int nomask_num = 0;
    int mask_num = 0;
    int counter = 0;
    while (counter < limit_time_ / 0.1) {
        counter ++;
        for (const auto& bounding_box : results_.bounding_boxes) {
            if (bounding_box.Class == nomask_class)
                nomask_num ++;
            if (bounding_box.Class == mask_class)
                mask_num ++;
        }
        if (nomask_num != 0 || mask_num != 0){
            if (nomask_num > mask_num){
                return true;
            }else{
                return false;
            }
        }
        ros::Duration(0.1).sleep();
    }
    ROS_INFO("no human here......");
    return false;
}
