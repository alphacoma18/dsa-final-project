#pragma once
#include <string>
#include <fstream>
class VideoStore
{

public:
    class Video
    {
    private:
        int _id = 0;
        const std::string _title = "";
        const std::string _genre = "";
        const std::string _production = "";
        int _copyCount = 0;
        Video *_next = nullptr;
        Video *_prev = nullptr;

    public:
        Video(int id, std::string title, std::string genre, std::string production, int copyCount = 1);
        ~Video();

        Video *getNext() const;
        Video *getPrev() const;
        void setNext(Video *next);
        void setPrev(Video *prev);

        int getId() const;
        std::string getTitle() const;
        std::string getGenre() const;
        std::string getProduction() const;
        int getCopyCount() const;

        void addCopy();
        void removeCopy();
    };
    VideoStore(std::string savePath);
    ~VideoStore();
    Video *getVideo(int id) const;
    bool videoExists(int id) const;
    void addVideo(Video *video);
    Video *rentVideo(int id);
    Video *returnVideo(int id) const;
    Video *getHead() const;
    void displayVideos() const;

private:
    Video *_head = nullptr;
    Video *_tail = nullptr;
    Video *_curr = nullptr;
    std::string _savePath = "";
    std::ofstream _ofstream = {};
    std::ifstream _ifstream = {};
};