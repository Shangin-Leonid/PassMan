#pragma once

#include <string>
#include <fstream>

#include "Unit_tests/Test_utils/Data_generator/header/UT_TU_DataGenerator.h"

namespace UTUtils
{

/*
** Uses 'DataGenerator' for generating database entries (their string representations) and redirect ** it to the chosen text file.
*/
class FileDataGenerator final : private DataGenerator
{
  public:

    FileDataGenerator() = delete;
    FileDataGenerator(const FileDataGenerator&) = delete;
    FileDataGenerator(FileDataGenerator&&) = delete;
    FileDataGenerator(const std::string& outputFileName);

    void generate(const size_t amount);
    void generateUnique(const size_t amount);

    void redirectOutput(const std::string& anotherOutputFileName);

    size_t getMaxPredefinedEntriesAmount() const noexcept;

  private:

    std::string _outputFileName;
    std::ofstream _outputFile;
    std::function<void(DatabaseEntry::Entry&&)> _fileWriter;
};

} // namespace UTUtils
