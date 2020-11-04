#ifndef NOMASK_ALARM_H
#define NOMASK_ALARM_H

#include "sound_player/sound_player.h"
#include "video_player/video_player.h"
#include "nomask_alarm/judgement.h"
#include "kbhit.h"

class NomaskAlarm{
public:
    NomaskAlarm();
    ~NomaskAlarm();
    void timerCallback(const ros::TimerEvent&);
   
private:
    ros::NodeHandle nh_private_;
    ros::Timer timer_;

    ros::Time start_t_;
    ros::Duration limit_t_;

    void debug();
    void run();
    void startTimer(double t);
    bool checkTimer();

    SoundPlayer soundplayer_;
    VideoPlayer videoplayer_;
    Judgement judgement_;

    std::string sample_sound1_, sample_sound2_;
    std::string sample_video1_;
    std::string sample_image1_, sample_image2_;
    std::string curse_sound_, curse_sound1_, curse_sound2_;
    std::string curse_video_;
    std::string face1_, face2_, face3_, face4_, face5_;
    std::string black_;

    int state_;
    char key_;
    bool debug_;

};

#endif