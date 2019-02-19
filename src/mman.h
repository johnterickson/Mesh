#pragma once

#if defined(_WIN32)
#include "vendor/johnterickson/mman-win32/mman.h"
#else
#include <sys/mman.h>
#endif