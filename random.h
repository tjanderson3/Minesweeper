#ifndef UNTITLED8_RANDOM_H
#define UNTITLED8_RANDOM_H
#include <random>

class Random {
    static std::mt19937 random;
    static int x;
public:
    static int Int(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(random);
    }
};
#include <ctime>

std::mt19937 Random::random(time(0));
#endif //UNTITLED8_RANDOM_H
