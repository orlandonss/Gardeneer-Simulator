//
// Created by orlando on 11/10/25.
//

#ifndef TPPOO2_RANDOM_H
#define TPPOO2_RANDOM_H

#include <random>
class Random
{
public:
    Random() = delete;
    static int getRandom(int min, int max);
    static int getRandom(int max);
private:
    static std::mt19937 engine;
};

#endif //TPPOO2_RANDOM_H