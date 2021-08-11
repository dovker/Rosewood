#pragma once

#include "rwpch.h"

#ifdef RW_NETWORKING_ENABLED
#define ASIO_STANDALONE

#include "asio.hpp"
#include "asio/ts/buffer.hpp"
#include "asio/ts/internet.hpp"
#include "asio/ssl.hpp"
#endif
//Networking part of the engine is based on https://www.youtube.com/watch?v=2hNdkYInj4g&t=1712s Asio networiking video series.