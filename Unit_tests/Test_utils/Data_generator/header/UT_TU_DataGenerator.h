#pragma once

#include "Unit_tests/Test_utils/header/UT_TU_CommonGenerator.h"
#include "Database_entry/DBE_DatabaseEntry.h"

namespace UTUtils
{

using DatabaseEntry::Entry;

/*
** Generate database entries (their string representations) and use it in chosen callback function.
*/
class DataGenerator : public CommonGenerator<Entry>
{
  public:

    virtual ~DataGenerator() noexcept = default;

    void generate(const size_t amount, std::function<void(Entry&&)> callback) const override;
    void generateUnique(const size_t amount, std::function<void(Entry&&)> callback) const override;

    void resetIdCounter() const noexcept;

    size_t getMaxPredefinedEntriesAmount() const noexcept;

  protected:

    void generateMoreThanHalfPredefinedEntries(const size_t amount, std::function<void(Entry&&)> callback) const;
    void generateTemplateEntries(const size_t amount, std::function<void(Entry&&)> callback) const;
    void generateShuffleSequence(const size_t amount, std::function<void(Entry&&)> callback) const;

    Entry generateNthPredefinedEntry(const size_t orderNumber) const;

  private:

    mutable DatabaseEntry::id_t _idCounter = 1;
};

} // namespace UTUtils
