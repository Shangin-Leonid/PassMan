#include <iostream>

#include "Unit_tests/Test_utils/Data_generator/header/UT_TU_DataGenerator.h"

int main()
{
    UTUtils::DataGenerator dataGenerator{};

    int amount = 0;
    std::cout << "Enter the amount of database entries that will be generated and printed (max is "
              << dataGenerator.getMaxPredefinedEntriesAmount() << "): ";
    std::cin >> amount;

    const std::function<void(DatabaseEntry::Entry &&)> callback = [](DatabaseEntry::Entry&& entry) -> void
    {
        std::cout << entry.getAsString() << '\n';
    };

    dataGenerator.generateUnique(amount, callback);

    return 0;
}
