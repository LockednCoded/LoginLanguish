#pragma once

#ifdef __DEBUG__
#define __DEBUG__ 1
#else
#define __DEBUG__ 0
#endif
#ifdef __CHEAT_MODE__
#define __CHEAT_MODE__ 1
#else
#define __CHEAT_MODE__ 0
#endif
#ifdef _WIN32
#define __WINDOWS__ 1
#else
#define __WINDOWS__ 0
#endif