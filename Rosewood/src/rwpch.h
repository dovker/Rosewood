#pragma once

#ifdef RW_PLATFORM_WINDOWS
#include "Windows.h"
#endif // 
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <random>
#include <new>
#include <limits>
#include <any>

#include <string>
#include <fstream>
#include <sstream>
#include <ostream>
#include <array>
#include <vector>
#include <deque>

#include <stdio.h>

#include <unordered_map>
#include <unordered_set>

#define ASIO_STANDALONE
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include "asio.hpp"
#include "asio/ts/buffer.hpp"
#include "asio/ts/internet.hpp"

#include "asio/ssl.hpp"


#include "Rosewood/Core/Log.h"

