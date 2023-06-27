#include <string>

class Video
{
private:
    static int _idCounter;
    int _id = 0;
    const std::string _title = "";
    const std::string _genre = "";
    const std::string _production = "";
    int copyCount = 0;

public:
    Video(std::string title, std::string genre, std::string production, int copyCount = 1);
    int getId() const;
    std::string getTitle() const;
    std::string getGenre() const;
    std::string getProduction() const;
    int getCopyCount() const;
    void addCopy();
    void removeCopy();
};