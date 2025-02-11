#include "nomask_alarm/nomask_alarm.h"


NomaskAlarm::NomaskAlarm(){
    timer_ = nh_private_.createTimer(ros::Duration(0.05), &NomaskAlarm::timerCallback, this);

    ros::NodeHandle nh("~");
    nh.param("sample_sound1", sample_sound1_, std::string("/home/suzuki-t/nomask_media/sample1.wav"));
    nh.param("sample_sound2", sample_sound2_, std::string("/home/suzuki-t/nomask_media/sample2.wav"));
	nh.param("sample_video1", sample_video1_, std::string("/home/suzuki-t/nomask_media/sample1.mp4"));
    nh.param("sample_image1", sample_image1_, std::string("/home/suzuki-t/nomask_media/sample1.jpg"));
	nh.param("sample_image2", sample_image2_, std::string("/home/suzuki-t/nomask_media/sample2.jpg"));

    nh.param("curse_sound", curse_sound_, std::string("/home/suzuki-t/nomask_media/curse.wav"));
    nh.param("curse_sound1", curse_sound1_, std::string("/home/suzuki-t/nomask_media/curse1.wav"));
    nh.param("curse_sound2", curse_sound2_, std::string("/home/suzuki-t/nomask_media/curse2.wav"));
	nh.param("curse_video", curse_video_, std::string("/home/suzuki-t/nomask_media/curse.mp4"));
	nh.param("face1", face1_, std::string("/home/suzuki-t/nomask_media/face1.png"));
	nh.param("face2", face2_, std::string("/home/suzuki-t/nomask_media/face2.png"));
	nh.param("face3", face3_, std::string("/home/suzuki-t/nomask_media/face3.png"));
	nh.param("face4", face4_, std::string("/home/suzuki-t/nomask_media/face4.png"));
	nh.param("face5", face5_, std::string("/home/suzuki-t/nomask_media/face5.png"));
	nh.param("black", black_, std::string("/home/suzuki-t/nomask_media/black.jpg"));

	nh.param("debug", debug_, true);

    start_t_ = ros::Time::now();
    limit_t_ = ros::Duration(1);

    state_ = 1;
    flag_state_ = 0;

    ros::Duration(1).sleep();

}

NomaskAlarm::~NomaskAlarm(){

}

void NomaskAlarm::timerCallback(const ros::TimerEvent&){
    if (kbhit()) {
        std::cin >> key_;
        // std::cout << "input key... " << key_ << std::endl;
    }
    
    if (debug_) {
        debug();
    } else{
        run();
    }
    
    key_ = '@';
}

void NomaskAlarm::debug() {
    switch (key_) {
        case 'x':
            soundplayer_.cancel();
            break;
        case 'c':
            videoplayer_.cancel();
            break;
        case '1':
            videoplayer_.showImage(black_);
            break;
        case '2':
            videoplayer_.showImage(face1_);
            break;
        case '3':
            videoplayer_.showImage(face2_);
            break;
        case '4':
            videoplayer_.showImage(face3_);
            break;
        case '5':
            videoplayer_.showImage(face4_);
            break;
        case '6':
            videoplayer_.showImage(face5_);
            break;
        case '7':
            break;
        case '8':
            break;
        case '9':
            break;
        case 'q':
            videoplayer_.setVideo(curse_video_);
            videoplayer_.play();
            break;
        case 'w':
            break;
        case 'a':
            soundplayer_.say("MA SU KU O TU KE NA SA I");
            break;
        case 's':
            soundplayer_.setSound(curse_sound_);
            soundplayer_.play();
            break;
        case 'd':
            soundplayer_.setSound(curse_sound1_);
            soundplayer_.play();
            break;
        case 'f':
            soundplayer_.setSound(curse_sound2_);
            soundplayer_.play();
            break;
        case 'o':
            startTimer(10);
            break;
        case 'p':
            if (checkTimer()) {
                ROS_INFO("Time Up!!");
            }
            break;
    }
}

void NomaskAlarm::run() {
    switch (state_){
        case 1:
            if (key_ == 's') {
                state_ = 2;
            }
            break;
        case 2:
            videoplayer_.showImage(face1_);
            startTimer(5);
            state_ = 3;
            break;
        case 3:
            if (checkTimer()){
                state_ = 4;
            }
            break;
        case 4:
            if (!judgement_.judge()){
                state_ = 0;
            } else {
                videoplayer_.showImage(face2_);
                soundplayer_.say("MA SU KU O TU KE NA SA I");
                startTimer(5);
                state_ = 5;
            }
            break;
        case 5:
            if(checkTimer()){
                state_ = 6;
            }
            break;
        case 6:
            if (!judgement_.judge()){
                state_ = 0;
            } else {
                videoplayer_.showImage(face3_);
                soundplayer_.say("MA SU KU O TU KE NA SA I");
                startTimer(5);
                state_ = 7;
            }
            break;
        case 7:
            if(checkTimer()) {
                state_ = 8;
            }
            break;
        case 8:
            if (!judgement_.judge()){
                state_ = 0;
            } else {
                videoplayer_.showImage(face4_);
                startTimer(5);
                state_ = 9;
            }
            break;
        case 9:
            if(checkTimer()) {
                state_ = 10;
            }
            break;
        case 10:
            if (!judgement_.judge()){
                state_ = 0;
            } else {
                videoplayer_.setVideo(curse_video_);
                videoplayer_.play();
                startTimer(5);
                state_ = 11;
            }
            break;
        case 11:
            if(checkTimer()) {
                state_ = 2;
                ROS_INFO("owari");
            }
            break;
        case 0:
            videoplayer_.showImage(face5_);
            startTimer(5);
            state_ = 20;
        case 20:
            if(checkTimer()) {
                state_ = 21;
            }
            break;
        case 21:
            if (!judgement_.judge()){
                state_ = 0;
            } else {
                state_ = 2;
            }
            break;
        default:
            break;
    }
    printState();
}

bool NomaskAlarm::printState() {
    if (state_ != flag_state_){
        ROS_INFO("now state... %d", state_);
        flag_state_ = state_;
        return true;
    }
    return false;
}

void NomaskAlarm::startTimer(double t) {
    start_t_ = ros::Time::now();
    limit_t_ = ros::Duration(t);
}

bool NomaskAlarm::checkTimer() {
    ros::Duration t = ros::Time::now() - start_t_;
    if (ros::Time::now() - start_t_ > limit_t_) {
        return true;
    }else {
        // std::cout << t << std::endl;
        return false;
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "nomask_alarm_node");

    NomaskAlarm n;

    ros::spin();

    return 0;
}
