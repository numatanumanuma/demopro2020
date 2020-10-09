#include "sound_player/sound_player.h"
#include "video_player/video_player.h"
#include "nomask_alarm/judgement.h"
#include "kbhit.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "nomask_alarm_node");
    //ノード名の初期化
    ros::NodeHandle nh("~");
    ros::Rate looprate(10);

    std::string sound_file, video_file;
    nh.param("sound_file", sound_file, std::string("/home/suzuki-t/.ros/media/sample.wav"));
	nh.param("video_file", video_file, std::string("/home/suzuki-t/.ros/media/sample.mp4"));

    SoundPlayer soundplayer;
    VideoPlayer videoplayer;
    Judgement judgement;

    looprate.sleep(); // 少し待つ

    soundplayer.setSound(sound_file);
    videoplayer.setVideo(video_file);

    while (ros::ok()) {

        char key;
        if (kbhit()) {
            std::cin >> key;
            std::cout << "input key... " << key << std::endl;
        }

        switch (key) {
            case 's':
                soundplayer.playOnce();
                break;
            case 'x':
                soundplayer.cancel();
                break;
        }
        switch (key) {
            case 's':
                if (!videoplayer.playing)
                    videoplayer.play();
                    // videoplayer.playOnce();
                break;
            case 'x':
                if (videoplayer.playing)
                    videoplayer.cancel();
                break;
        }

        key = 'c';
        ros::spinOnce();
        looprate.sleep();
    }

    return 0;
}
