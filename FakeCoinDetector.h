#pragma once

#include <iostream>
#include <random>
#include <chrono>
#include <limits>

class FakeCoinDetector {

private:
    int *coins;
    int amountOfCoins;

    static const int chanceOfBeingFake = 20;

    int WeightGenerator();
    int GenerateFakeCoin();
    void ShowCoins();

    int PromptUser();
    void GenerateCoins();

    int FindFakeCoin();

public:
    FakeCoinDetector();
    ~FakeCoinDetector();
};