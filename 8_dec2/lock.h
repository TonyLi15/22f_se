#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <atomic>
#include <thread>
#include <iostream>
#include "debug.h"

pthread_mutex_t Lock;
static constexpr uint NbThread = 10;
static constexpr uint NbLoop = 1000 * 1000 * 10;
static constexpr uint LockBit = 0x01;
static constexpr uint UnlockBit = 0x00;
