#include "utils.h"
#include <math.h>

bool isPrime(unsigned int number) {
    if (number < 2)
        return false;

    if (number == 2)
        return true;

    if (number % 2 == 0)
        return false;


    double sqrt_num = sqrt(number);
    for (unsigned int i = 3; i <= sqrt_num; i += 2) {
        if (number % i == 0)
            return false;
    }

    return true;
}