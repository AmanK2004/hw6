#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        // Convert characters of the string to numbers using letterDigitToNumber function
        std::size_t convertedDigits[k.length()];
        for (unsigned int i = 0; i < k.length(); i++) {
            convertedDigits[i] = letterDigitToNumber(k[i]);
        }

        // Initialize sequence array to store the calculated sequence
        unsigned long long int sequence[5] = {0, 0, 0, 0, 0};
        int position = k.length() - 1; // Initialize position to the last character index
        int currentIndex = 4; // Initialize currentIndex to the last index of the sequence array

        // Construct the sequence of numbers from converted digits
        while (position >= 0) {
            unsigned long long int digit6 = 0;
            unsigned long long int digit5 = 0;
            unsigned long long int digit4 = 0;
            unsigned long long int digit3 = 0;
            unsigned long long int digit2 = 0;
            unsigned long long int digit1 = 0;

            // Assign converted digits to variables from the right end of the string
            if (position >= 0) {
                digit6 = convertedDigits[position];
            }
            position -= 1;

            if (position >= 0) {
                digit5 = convertedDigits[position];
            }
            position -= 1;

            if (position >= 0) {
                digit4 = convertedDigits[position];
            }
            position -= 1;

            if (position >= 0) {
                digit3 = convertedDigits[position];
            }
            position -= 1;

            if (position >= 0) {
                digit2 = convertedDigits[position];
            }
            position -= 1;

            if (position >= 0) {
                digit1 = convertedDigits[position];
            }
            position -= 1;

            // Calculate the value of the sequence element and store it in the sequence array
            sequence[currentIndex] = (pow(36, 5) * digit1) + (pow(36, 4) * digit2) + (pow(36, 3) * digit3) + (pow(36, 2) * digit4) + (36 * digit5) + digit6;
            currentIndex -= 1;
        }

        // Calculate the hash value using the generated sequence and rValues array
        unsigned long long int hash = rValues[0] * sequence[0];
        for (int i = 1; i < 5; i++) {
            hash = hash + (rValues[i] * sequence[i]);
        }

        // Return the calculated hash value
        return hash;


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        std::size_t value = 0;

        if (isalpha(letter)) {
            letter = tolower(letter);
            value = static_cast<size_t>(letter) - 'a';
        }

        if (isdigit(letter)) {
            value = static_cast<size_t>(letter) - '0' + 26;
        }

        return value;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
