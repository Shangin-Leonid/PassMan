#include <iostream>

#include "Unit_tests/Test_utils/File_data_generator/header/UT_TU_FileDataGenerator.h"

int main()
{
    std::string outputFilename;
    std::cout << "Enter the name of output file: ";
    std::cin >> outputFilename;

    UTUtils::FileDataGenerator fileDataGenerator{outputFilename};

    int amount = 0;
    std::cout << "Enter the amount of database entries that will be generated (max is "
              << fileDataGenerator.getMaxPredefinedEntriesAmount() << "): ";
    std::cin >> amount;

    fileDataGenerator.generateUnique(amount);

    return 0;
}
