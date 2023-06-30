#include <iostream>
#include "data.h"

Video::Video(std::string title, std::string genre, std::string production, int copyCount) : _title(title), _genre(genre), _production(production), _copyCount(copyCount)
{
    _id = ++_idCounter;
}
Video::~Video()
{
    _idCounter--;
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
    return _copyCount;
}

void Video::addCopy()
{
    ++_copyCount;
}

void Video::removeCopy()
{
    --_copyCount;
};
Video *Video::getNext() const
{
    return _next;
}
Video *Video::getPrev() const
{
    return _prev;
}
Video *Video::setNext(Video *next)
{
    _next = next;
    return _next;
}
Video *Video::setPrev(Video *prev)
{
    _prev = prev;
    return _prev;
}
int Video::_idCounter = 0;
