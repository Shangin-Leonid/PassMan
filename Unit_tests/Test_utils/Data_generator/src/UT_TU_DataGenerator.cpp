#include "Database_entry/header/DBE_Types_Fwd.h"
#include "Unit_tests/Test_utils/Data_generator/header/UT_TU_DataGenerator.h"

namespace UTUtils
{

using namespace DatabaseEntry;

namespace
{

// clang-format off

const string_t EntryNames[] = {
    "Telegram",      "VK",            "YouTube", "RuTube",      "Google",    "Yandex",
    "Avito",         "Aliexpress",    "Github",  "Microsoft",   "Samsung",   "Wikipedia",
    "Stackoverflow", "Overleaf",      "Zoom",    "HH.ru",       "Ozon",      "MTS",
    "Beeline",       "Megafon",       "Tele2",   "Sber",        "Alfa-bank", "VTB",
    "RosSelHozBank", "Bank Otkritie", "MKB",     "GazPromBank", "Profi.ru",  "Cian.ru"
};

const string_t PhoneNumbers[] = {
    "+7 (111) 111-11-11", "+7 (222) 222-22-22", "+7 (333) 333-33-33",
    "+7 (444) 444-44-44", "+7 (555) 555-55-55", "+7 (666) 666-66-66",
    "+7 (777) 777-77-77", "+7 (888) 888-88-88", "+7 (999) 999-99-99",

    "+7 (123) 456-78-99", "+7 (998) 765-43-21", "+7 (123) 455-43-21",

    "+7 (100) 100-10-10", "+7 (200) 200-20-20", "+7 (300) 300-30-30",
    "+7 (400) 400-40-40", "+7 (500) 500-50-50", "+7 (600) 600-60-60",
    "+7 (700) 700-70-70", "+7 (800) 800-80-80", "+7 (900) 900-90-90",

    "+7 (001) 001-01-01", "+7 (002) 002-02-02", "+7 (003) 003-03-03",
    "+7 (004) 004-04-04", "+7 (005) 005-05-05", "+7 (006) 006-06-06",
    "+7 (007) 007-07-07", "+7 (008) 008-08-08", "+7 (009) 009-09-09"
};

const string_t UserNames[] = {
    "Aleksandr", "Kirill", "Boris", "Yuri",
    "Vladimir",  "Viktor", "Vadim", "Oleg",
    "Yevgeniy",  "Andrey", "Denis", "Petr",
    "Anatoliy",  "Maksim", "Pavel",
    "Valentin",  "Nikita", "Roman",
    "Nikolai",   "Ruslan", "Timur",
    "Mikhail",   "Sergey", "Fedor",
    "Aleksey",   "Stepan", "Egor",
    "Dmitriy",   "Eduard", "Ivan",
    "Georgiy",   "Anton",  "Igor",
    "Vasiliy",   "Artem",  "Ilya"
};

const string_t EmailDomens[] = {
    "@yandex.ru",   "@math.msu.ru", "@mail.ru",
    "@rambler.com", "@outlook.com", "@yahoo.com",
    "@gmail.ru",    "@live.com",    "@userdomen.net"
};

const string_t TEMPLATE_ENTRY_NAME_PREFIX = "site_";
const string_t TEMPLATE_USERNAME_PREFIX = "user_";
const string_t TEMPLATE_EMAIL_DOMEN_POSTFIX = "@email.com";
const string_t TEMPLATE_PASSWORD_PREFIX = "password_";

constexpr size_t nEntryNames   = std::size(EntryNames);
constexpr size_t nPhoneNumbers = std::size(PhoneNumbers);
constexpr size_t nUserNames    = std::size(UserNames);
constexpr size_t nEmailDomens  = std::size(EmailDomens);

constexpr size_t nLogins = nPhoneNumbers + nUserNames * nEmailDomens;
constexpr size_t nPredefinedEntries = nEntryNames * nLogins; // = 6768

// clang-format on

} // anonymous namespace

void DataGenerator::generate(const size_t amount, std::function<void(DatabaseEntry::Entry&&)> callback) const
{
    generateUnique(amount, callback);
}

void DataGenerator::generateUnique(const size_t amount, std::function<void(DatabaseEntry::Entry&&)> callback) const
{
    if (amount > nPredefinedEntries)
    {
        generateMoreThanHalfPredefinedEntries(nPredefinedEntries, callback);
        generateTemplateEntries(amount - nPredefinedEntries, callback);
    }
    else if (amount > nPredefinedEntries / 2)
    {
        generateMoreThanHalfPredefinedEntries(amount, callback);
    }
    else
    {
        generateShuffleSequence(amount, callback);
    }
}

void DataGenerator::resetIdCounter() const noexcept
{
    _idCounter = 1;
}

size_t DataGenerator::getMaxPredefinedEntriesAmount() const noexcept
{
    return nPredefinedEntries;
}

void DataGenerator::generateMoreThanHalfPredefinedEntries(const size_t amount,
                                                          std::function<void(Entry&&)> callback) const
{
    const size_t last = amount - 1;
    size_t offset = 0;

    for (size_t _ = 0; _ < amount; ++_)
    {
        if (_ % 2 == 0)
        {
            callback(generateNthPredefinedEntry(offset));
            ++_idCounter;
        }
        else
        {
            callback(generateNthPredefinedEntry(last - offset));
            ++_idCounter;
            offset += 2;
        }
    }
}

namespace
{

entry_name_t generateUniqueEntryName(const DatabaseEntry::id_t id)
{
    return TEMPLATE_ENTRY_NAME_PREFIX + to_string_t(id);
}

login_t generateUniqueLogin(const DatabaseEntry::id_t id)
{
    return TEMPLATE_USERNAME_PREFIX + to_string_t(id) + TEMPLATE_EMAIL_DOMEN_POSTFIX;
}

password_t generateUniquePassword(const DatabaseEntry::id_t id)
{
    return TEMPLATE_PASSWORD_PREFIX + to_string_t(id);
}

} // anonymous namespace

void DataGenerator::generateTemplateEntries(const size_t amount, std::function<void(Entry&&)> callback) const
{
    for (size_t _ = 0; _ < amount; ++_)
    {
        callback(Entry{_idCounter,
                       generateUniqueEntryName(_idCounter),
                       generateUniqueLogin(_idCounter),
                       generateUniquePassword(_idCounter)});

        ++_idCounter;
    }
}

void DataGenerator::generateShuffleSequence(const size_t amount, std::function<void(Entry&&)> callback) const
{
    const size_t last = nPredefinedEntries - 1;
    const size_t delta = last / amount;
    size_t offset = 0;
    for (size_t _ = 0; _ < amount; ++_)
    {
        if (_ % 2 == 0)
        {
            callback(generateNthPredefinedEntry(offset));
            ++_idCounter;
        }
        else
        {
            callback(generateNthPredefinedEntry(last - offset));
            ++_idCounter;
            offset += delta;
        }
    }
}

Entry DataGenerator::generateNthPredefinedEntry(const size_t n) const
{
    const auto& entryName = EntryNames[n / nLogins];
    const auto& login = (n % nLogins < nPhoneNumbers) ? PhoneNumbers[n % nLogins]
                                                      : UserNames[(n % nLogins - nPhoneNumbers) / nEmailDomens] +
                                                          EmailDomens[(n % nLogins - nPhoneNumbers) % nEmailDomens];

    return Entry{_idCounter, entryName, login, generateUniquePassword(_idCounter)};
}

} // namespace UTUtils
