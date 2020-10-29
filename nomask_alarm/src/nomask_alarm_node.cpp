#include "sound_player/sound_player.h"
#include "video_player/video_player.h"
#include "nomask_alarm/judgement.h"
#include "kbhit.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "nomask_alarm_node");
    ros::NodeHandle nh("~");
    ros::Rate looprate(10);

    std::string sample_sound1, sample_sound2;
    std::string sample_video1;
    std::string sample_image1, sample_image2;
    nh.param("sample_sound1", sample_sound1, std::string("/home/suzuki-t/nomask_media/sample1.wav"));
    nh.param("sample_sound2", sample_sound2, std::string("/home/suzuki-t/nomask_media/sample2.wav"));
	nh.param("sample_video1", sample_video1, std::string("/home/suzuki-t/nomask_media/sample1.mp4"));
    nh.param("sample_image1", sample_image1, std::string("/home/suzuki-t/nomask_media/sample1.jpg"));
	nh.param("sample_image2", sample_image2, std::string("/home/suzuki-t/nomask_media/sample2.jpg"));

    std::string curse_sound, curse_sound1, curse_sound2;
    std::string curse_video;
    std::string face1, face2, face3, face4;
    nh.param("curse_sound", curse_sound, std::string("/home/suzuki-t/nomask_media/curse.wav"));
    nh.param("curse_sound1", curse_sound1, std::string("/home/suzuki-t/nomask_media/curse1.wav"));
    nh.param("curse_sound2", curse_sound2, std::string("/home/suzuki-t/nomask_media/curse2.wav"));
	nh.param("curse_video", curse_video, std::string("/home/suzuki-t/nomask_media/curse.mp4"));
	nh.param("face1", face1, std::string("/home/suzuki-t/nomask_media/face1.png"));
	nh.param("face2", face2, std::string("/home/suzuki-t/nomask_media/face2.png"));
	nh.param("face3", face3, std::string("/home/suzuki-t/nomask_media/face3.png"));
	nh.param("face4", face4, std::string("/home/suzuki-t/nomask_media/face4.png"));


    SoundPlayer soundplayer;
    VideoPlayer videoplayer;
    Judgement judgement;
    looprate.sleep(); // 少し待つ

    int state = 1;

    while (ros::ok()) {

        if (1) {
            char key;
            if (kbhit()) {
                std::cin >> key;
                std::cout << "input key... " << key << std::endl;
            }
            switch (key) {
                case 'x':
                    soundplayer.cancel();
                    break;
                case 'c':
                    videoplayer.cancel();
                    break;
                case '1':
                    soundplayer.say("MASUKUWOTUKENASAI");
                    break;
                case '2':
                    soundplayer.setSound(sample_sound2);
                    soundplayer.play();
                    break;
                case '3':
                    soundplayer.setSound(curse_sound1);
                    soundplayer.play();
                    break;
                case '4':
                    soundplayer.setSound(curse_sound2);
                    soundplayer.play();
                    break;
                case '5':
                    videoplayer.setVideo(curse_video);
                    videoplayer.playOnce();
                    break;
                case '6':
                    videoplayer.showImage(face1);
                    break;
                case '7':
                    videoplayer.showImage(face2);
                    break;
                case '8':
                    videoplayer.showImage(face3);
                    break;
                case '9':
                    videoplayer.showImage(face4);
                    break;
            }
            key = '@';
    }
    else
    {
        char key;
        if (kbhit()) {
            std::cin >> key;
            std::cout << "input key... " << key << std::endl;
        }
        switch (state){
            case 1:
                if (judgement.judge()){
                    videoplayer.setVideo(curse_video);
                    videoplayer.playOnce();
                    break;
                }else{
                    videoplayer.showImage(sample_image1);
                    break;
                }
                break;
            case 2:
                break;
            default:
                break;
        }
    }
        

        ros::spinOnce();
        looprate.sleep();
    }

    return 0;
}
