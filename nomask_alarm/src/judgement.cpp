#include "nomask_alarm/judgement.h"
   
Judgement::Judgement(){
    ros::NodeHandle nh("~");
    timer_ = nh.createTimer(ros::Duration(0.05), &Judgement::timerCallback, this);
    darknet_sub_ = nh.subscribe("/darknet_ros/bounding_boxes", 100,
        &Judgement::darknetCallback, this);
    nomask_class = "nomask";
    mask_class = "mask";
}

Judgement::~Judgement(){

}

void Judgement::darknetCallback(const darknet_ros_msgs::BoundingBoxes::ConstPtr& results) {
    results_ = *results;
}

void Judgement::timerCallback(const ros::TimerEvent&){
    
}

void Judgement::judge(){
    int nomask_num;
    int mask_num;
    for (const auto& bounding_box : results_.bounding_boxes) {
        if (bounding_box.Class == nomask_class)
            nomask_num ++;
        if (bounding_box.Class == mask_class)
            mask_num ++;
    }
    if (nomask_num > mask_num){
        ROS_INFO("コラコラ");
    }
    // みたいな？
}
