#pragma once

#include <iostream>
#include <random>
#include <chrono>
#include <limits>
#include <fstream>

class FakeCoinDetector {

private:
    int *coins;
    int amountOfCoins;

    static const int chanceOfBeingFake = 20;

    int WeightGenerator();
    int GenerateFakeCoin();
    void ShowCoins();
    void StoreData(int index);

    int PromptUser();
    void GenerateCoins();

    int FindFakeCoin();

public:
    FakeCoinDetector();
    ~FakeCoinDetector();
};