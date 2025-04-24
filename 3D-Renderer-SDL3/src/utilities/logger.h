#pragma once

#define LOG_ONCE_ENABLED static bool firstFrame = true
#define LOG_ONCE(x) if(firstFrame) {std::cout << x << std::endl;}
#define FRAME_END firstFrame = false