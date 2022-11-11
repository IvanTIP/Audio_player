#include <iostream>
#include <ctime>

class Track {
  private:
    std::string trackName;
    std::tm trackData;
    int trackDuration = 0;
  public:
    std::string getTrackName () {
        return trackName;
    };
    void setTrackName (std::string &name) {
        trackName = name;
    }

    std::tm getData () {
        return trackData;
    }
    void setData (std::tm data) {
        trackData = data;
    }

    int getDuration () {
        return trackDuration;
    }
    void setDuration (int dur) {
        trackDuration = dur;
    }

    void showInfo () {
        std::cout << "Track name: " << trackName << std::endl;
        std::cout << "Date of creation: " << trackData.tm_mday << "/" << trackData.tm_mon + 1 << "/" << trackData.tm_year + 1900
                  << " " << trackData.tm_hour << ":" << trackData.tm_min << ":" << trackData.tm_sec << std::endl;
        std::cout << "Duration: " << trackDuration << " sec" << std::endl;
    }
};

class Player {
  private:
    Track track[3];
    bool trackPlayback = false;
    bool trackPause = false;
  public:
    void init (std::string &name) {

        for (int i = 0;i < 3;i++) {
            name = "Unknown" + std::to_string(i + 1);
            track[i].setTrackName(name);
            std::time_t t = std::time(nullptr);
            std::tm data = *std::localtime(&t);
            data.tm_hour = std::rand() % 24; // добавил рандомное время создания трека в течение суток
            data.tm_min = std::rand() % 60;
            data.tm_sec = std::rand() % 60;
            track[i].setData(data);
            int dur = rand() % 180 + 120;
            track[i].setDuration(dur);
        }
    }
    int play (std::string &name) {
        for (int i = 0;i < 3;i++) {
            if (name == track[i].getTrackName() && !trackPlayback && !trackPause) {
                trackPlayback = true;
                std::cout << "Track playback has started:" << std::endl;
                track[i].showInfo();
                return 0;
            } else if (name == track[i].getTrackName() && !trackPlayback && trackPause) {
                trackPause = false;
                std::cout << "Track playback has started:" << std::endl;
                track[i].showInfo();
                return 1;
            } else if (trackPlayback) {
                std::cout << "The audio track is already playing right now" << std::endl;
                return 2;
            }
            else if (i == 2 && !trackPause) {
                std::cout << "Track is not found" << std::endl;
                return 3;
            }
        }
    }
    int pause () {
        if (!trackPlayback || trackPause) {
            return 0;
        } else {
            std::cout << "Track playback paused" << std::endl;
            trackPause = true;
            trackPlayback = false;
            return 1;
        }
    }
    void next (std::string &name) {
        if (trackPlayback) {
            int i = std::rand() % 3;
            name = "Unknown" + std::to_string(i + 1);
            std::cout << "Track playback has started:" << std::endl;
            track[i].showInfo();
        }
    }
    void stop () {
        if (trackPlayback) {
            std::cout << "Track playback is stopped" << std::endl;
            trackPlayback = false;
        }
    }
    bool getPlaybackStatus () {
        return trackPlayback;
    }
    bool getPauseStatus () {
        return trackPause;
    }
};

int main() {
    Player* myPlayer = new Player;
    std::string name;
    myPlayer->init(name);
    while (true) {
        std::string command;
        std::cout << "Input the command: ";
        std::cin >> command;
        if (command == "play") {
            if (!myPlayer->getPlaybackStatus() && !myPlayer->getPauseStatus()) {
                std::cout << "Input the name of track: ";
                std::cin >> name;
                myPlayer->play(name);
            } else {
                myPlayer->play(name);
            }
        } else if (command == "pause") {
            myPlayer->pause();
        } else if (command == "next") {
            myPlayer->next(name);
        } else if (command == "stop") {
            myPlayer->stop();
        } else if (command == "exit") {
            delete myPlayer;
            return 0;
        } else {
            std::cout << "Input error! Try again" << std::endl;
        }
    }
}
