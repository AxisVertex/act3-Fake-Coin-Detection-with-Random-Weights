#include "FakeCoinDetector.h"

// CONSTRUCTOR
FakeCoinDetector::FakeCoinDetector() {
    std::cout << "[Fake Coin Detection with Random Weights]" << std::endl;
    
    amountOfCoins = PromptUser(); // when an object of this class is created it will prompt the user how many coins do they want to create

    coins = new int[amountOfCoins]; // create an array with the size that user inputted

    GenerateCoins(); // now generates coins
    int fakeCoinIndex = FindFakeCoin();

    if (fakeCoinIndex != -1)
        std::cout << "Coin " << fakeCoinIndex + 1 << " is the fake coin with its weight being " << coins[fakeCoinIndex] << std::endl;
    else
        std::cout << "No fake coin found." << std::endl;

    ShowCoins();
}

// DECONSTRUCTOR
FakeCoinDetector::~FakeCoinDetector() {
    delete[] coins;
}

// user input
int FakeCoinDetector::PromptUser() {
    int numOfCoins;

    while (true) {
        std::cout << "How many coins do you want to generate?: ";
        std::cin >> numOfCoins;
        std::cin.ignore();

        // makes sure the input is integer
        if (std::cin.fail()) {
            // Clear the failbit and ignore the remaining
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Invalid input, Try again." << std::endl;
            continue;
        }
        else if (numOfCoins <= 1) { // 1 and 0 is not allowed
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "1 and 0 is not valid, Try inputting more than that." << std::endl;
            continue;
        }

        return numOfCoins;
    }
}

// Coin generator
void FakeCoinDetector::GenerateCoins() {
    bool fakeCoinCreated = false;
    int coinWeight = WeightGenerator(); // generates weight from (chooses from 10-20)

    std::cout << "Weight of each coin is " << coinWeight << std::endl;

    for (int i = 0; i < amountOfCoins; i++) {
        if (fakeCoinCreated == false) { // first checks if there has a fake coin has already been made
            if (GenerateFakeCoin() == true) { // checks whether a fake coin should be made or not
                coins[i] = coinWeight - 5;
                fakeCoinCreated = true;
                continue; // continue to avoid creating 2 coins
            }
        }
        
        coins[i] = coinWeight;
    }
}

int FakeCoinDetector::WeightGenerator() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed); // Mersenne Twister engine
    // Define the range for random numbers
    std::uniform_int_distribution<int> distributionAlphabets(10, 20); // generates random integers between 10 and 20

    int randomWeight = distributionAlphabets(generator);

    return randomWeight;
}

// decide whether to put fake coin or real
int FakeCoinDetector::GenerateFakeCoin() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distributionAlphabets(0, 100);

    // This generates from 0 - 100, if its under the chance of being fake then a fake coin will be generated
    int probability = distributionAlphabets(generator);
    bool generateFakeCoin = (probability < chanceOfBeingFake);

    return generateFakeCoin;
}

void FakeCoinDetector::ShowCoins() {
    // show the whole array of coins
    std::cout << "[";
    for (int i = 0; i < amountOfCoins; i++) {
        std::cout << coins[i];

        if (i == amountOfCoins - 1)
            std::cout << "]" << std::endl;
        else
            std::cout << ", ";
    }
}

int FakeCoinDetector::FindFakeCoin() {    
    int left = 0, right = amountOfCoins - 1;
    int iteration = 1;

    while (left < right) {
        int numCoins = right - left + 1;
        bool hasExtraCoin = (numCoins % 2 == 1);
        int extraCoin = -1;

        if (hasExtraCoin) {
            // Set aside the last coin if there's an odd number of coins
            extraCoin = right;
            right--;
        }

        int mid = left + (right - left) / 2;

        int leftSum = 0, rightSum = 0;

        // Weigh left group (left to mid)
        for (int i = left; i <= mid; i++) 
            leftSum += coins[i];

        // Weigh right group (mid+1 to right)
        for (int i = mid + 1; i <= right; i++)
            rightSum += coins[i];

        // Show output each iteration
        std::cout << "-------------------------------------------------------------------------------------" << std::endl;
        std::cout << "[Iteration " << iteration << "]:" << std::endl;
        std::cout << "Weighing coins: (Coin " << left + 1 << " to Coin " << mid + 1 << ") VS (Coin " << mid + 2 << " to Coin " << right + 1 << ")" << std::endl;
        std::cout << "Left sum: " << leftSum << ", Right sum: " << rightSum << std::endl;
        if (hasExtraCoin) {
            std::cout << "Extra coin set aside: Coin " << extraCoin+1 << "\n";
        }

        if (leftSum < rightSum) {
            std::cout << "Fake coin is in the left group." << std::endl;
            right = mid;
        } 
        else if (leftSum > rightSum) {
            std::cout << "Fake coin is in the right group." << std::endl;
            left = mid + 1;
        } 
        else if (hasExtraCoin) {
            // If left and right are equal, check the extra coin.
            std::cout << "Both groups are equal. Checking if the extra coin is fake." << std::endl;
            // check i
            if (coins[extraCoin] < coins[extraCoin + 1])
                return extraCoin;  // This only happens in odd-sized lists.
            else
                return -1;
        } 
        else {
            // Shouldn't happen if there's always exactly one fake.
            std::cout << "Both groups are equal. No fake coin found in this range." << std::endl;
            return -1;
        }

        iteration++;
    }
    std::cout << "-------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl; // space

    // //show which coin is fake
    return left;
}