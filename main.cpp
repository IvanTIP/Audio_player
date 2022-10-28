#include <iostream>
#include <ctime>

class Track {
  private:
    std::string trackName;
    std::tm* trackData;
    int trackDuration = 0;
  public:
    std::string getTrackName () {
        return trackName;
    };
    void setTrackName (std::string &name) {
        trackName = name;
    }

    std::tm* getData () {
        return trackData;
    }
    void setData (std::tm* data) {
        trackData = data;
    }

    int getDuration () {
        return trackDuration;
    }
    void setDuration (int dur) {
        trackDuration = dur;
    }
};

class Player {
  private:
    Track track[3];
  public:
    void init (std::string &name) {
        for (int i = 0;i < 3;i++) {
            name = "Unknown" + std::to_string(i + 1);
            track[i].setTrackName(name);
            std::time_t t = std::time(nullptr);
            std::tm* data = std::localtime(&t);
            track[i].setData(data);
            int dur = rand() % 180 + 120;// длительность трека от 2 до 3 минут
            track[i].setDuration(dur);
        }
    }
    int play (std::string const &name, bool &trackPlayback, bool &trackPause) {
        for (int i = 0;i < 3;i++) {
            if (name == track[i].getTrackName() && !trackPlayback && !trackPause) {
                trackPlayback = true;
                std::cout << "Track playback has started:" << std::endl;
                std::cout << "Track name: " << track[i].getTrackName() << std::endl;
                std::cout << "Date of creation: " << std::asctime(track[i].getData());
                std::cout << "Duration: " << track[i].getDuration() << " sec" << std::endl;
                return 0;
            } else if (i == 2 && !trackPlayback && !trackPause) {
                std::cout << "Track is not found" << std::endl;
                return 1;
            }
        }
    }
    int pause (bool &trackPause, bool &trackPlayback) {
        if (!trackPlayback || trackPause) {
            return 0;
        } else {
            std::cout << "Track playback paused" << std::endl;
            trackPause = true;
            trackPlayback = false;
            return 1;
        }
    }

    void next (bool &trackPlayback, std::string &name) {
        if (trackPlayback) {
            std::srand(std::time(nullptr));
            int i = std::rand() % 3;
            name = "Unknown" + std::to_string(i + 1);
            std::cout << "Track playback has started:" << std::endl;
            std::cout << "Track name: " << track[i].getTrackName() << std::endl;
            std::cout << "Date of creation: " << std::asctime(track[i].getData());
            std::cout << "Duration: " << track[i].getDuration() << " sec" << std::endl;
        }
    }

    void stop (bool &trackPlayback) {
        if (trackPlayback) {
            std::cout << "Track playback is stopped" << std::endl;
            trackPlayback = false;
        }
    }
};

int main() {
    Player* myPlayer = new Player;
    std::string name;
    myPlayer->init(name);
    bool trackPlayback = false;
    bool trackPause = false;
    while (true) {
        std::string command;
        std::cout << "Input the command: ";
        std::cin >> command;
        if (command == "play") {
            if (trackPause) {
                trackPause = false;
                myPlayer->play(name, trackPlayback, trackPause);
            } else if (trackPlayback) {
                continue;
            } else {
                std::cout << "Input the name of track: ";
                std::cin >> name;
                myPlayer->play(name, trackPlayback, trackPause);
            }
        } else if (command == "pause") {
            myPlayer->pause(trackPause, trackPlayback);
        } else if (command == "next") {
            myPlayer->next(trackPlayback, name);
        } else if (command == "stop") {
            myPlayer->stop(trackPlayback);
        } else if (command == "exit") {
            delete myPlayer;
            return 0;
        } else {
            std::cout << "Input error! Try again" << std::endl;
        }
    }

}
