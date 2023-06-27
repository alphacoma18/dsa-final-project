#include "data.h"

Video::Video(std::string title, std::string genre, std::string production, int copyCount) : _title(title), _genre(genre), _production(production), copyCount(copyCount)
{
    _id = ++_idCounter;
}

int Video::getId() const
{
    return _id;
}

std::string Video::getTitle() const
{
    return _title;
}
std::string Video::getGenre() const
{
    return _genre;
}
std::string Video::getProduction() const
{
    return _production;
}

int Video::getCopyCount() const
{
    return copyCount;
}

void Video::addCopy()
{
    ++copyCount;
}

void Video::removeCopy()
{
    --copyCount;
};
int Video::_idCounter = 0;
