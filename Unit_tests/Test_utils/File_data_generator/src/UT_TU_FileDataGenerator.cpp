#include <fstream>

#include "Unit_tests/Test_utils/File_data_generator/header/UT_TU_FileDataGenerator.h"

namespace UTUtils
{

FileDataGenerator::FileDataGenerator(const std::string& outputFileName) :
    _outputFileName(outputFileName), _outputFile(_outputFileName)
{
    if (!_outputFile)
    {
        // TODO
        throw "Cannot open the file in FileDataGenerator constructor!";
    }

    _fileWriter = [this](DatabaseEntry::Entry&& entry) -> void
    {
        _outputFile << entry.getAsString() << '\n';
    };
}

void FileDataGenerator::generate(const size_t amount)
{
    generateUnique(amount);
}

void FileDataGenerator::generateUnique(const size_t amount)
{
    DataGenerator::generateUnique(amount, _fileWriter);
}

void FileDataGenerator::redirectOutput(const std::string& anotherOutputFileName)
{
    _outputFile.close();

    _outputFileName = anotherOutputFileName;
    _outputFile = std::ofstream(_outputFileName);
    if (!_outputFile)
    {
        // TODO
        throw "Cannot open the file during output redirecting in FileDataGenerator";
    }

    DataGenerator::resetIdCounter();
}

size_t FileDataGenerator::getMaxPredefinedEntriesAmount() const noexcept
{
    return DataGenerator::getMaxPredefinedEntriesAmount();
}

} // namespace UTUtils
