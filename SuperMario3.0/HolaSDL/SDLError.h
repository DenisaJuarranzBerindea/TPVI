#ifndef SDLERROR_H
#define SDLERROR_H

#include <string>

#include "GameError.h"

class SDLError : public GameError
{
public:
    SDLError(const std::string& message);
};

#endif