#ifndef COMMON_H

#define COMMON_H

#include <iostream>
#include <time.h>
#include <unordered_map>
#include <chrono>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include <ctime>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <windows.h>
#include <memory>

float RandF(float _min, float _max);
int RandI(int _min, int _max);
int AskPositiveNumberBetween(std::string _message, int _min, int _max);
#endif // !COMMON_H
