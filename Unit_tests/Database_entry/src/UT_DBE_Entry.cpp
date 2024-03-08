#include <gtest/gtest.h>

#include "Database_entry/DBE_DatabaseEntry.h"
#include "Database_entry/header/DBE_Constants_Fwd.h"

using namespace DatabaseEntry;

TEST(DatabaseEntry, Compilation)
{
    Entry entry{};
}

TEST(DatabaseEntry, Constructors)
{
    Entry entry_1{};

    const auto Timestamp = std::time(0);
    auto entry_2 = Entry{2, "Shop", "User@login.com", "123456", Timestamp};

    EXPECT_EQ("2 | Shop | User@login.com | 123456 | +", entry_2.getAsString());

    const auto entry_3 = entry_2;
    const auto entry_4 = std::move(entry_2);

    EXPECT_EQ("2 | Shop | User@login.com | 123456 | +", entry_3.getAsString());
    EXPECT_EQ("2 | Shop | User@login.com | 123456 | +", entry_4.getAsString());
}

TEST(DatabaseEntry, GetAsString)
{
    const auto Timestamp = std::time(0);
    const auto entry = Entry{10, "Shop", "User@login.com", "123456", Timestamp};

    EXPECT_EQ("10 | Shop | User@login.com | 123456 | +", entry.getAsString());
    EXPECT_EQ("Shop", entry.getAsString(enumToValue(Field::NAME)));
    EXPECT_EQ("10 | 123456", entry.getAsString(enumToValue(Field::ID | Field::PASSWORD)));
    EXPECT_EQ("User@login.com | 123456 | +",
              entry.getAsString(enumToValue(Field::LOGIN | Field::PASSWORD | Field::IS_PASSWORD_OUTDATED)));
}

TEST(DatabaseEntry, AssignmentOperators)
{
    const auto Timestamp_1 = std::time(0);
    const auto Timestamp_2 = Timestamp_1 - 2 * PASSWORD_UPDATING_PERIOD;

    auto entry_1 = Entry{1, "Shop1", "User1@login.com", "111", Timestamp_1};
    auto entry_2 = Entry{2, "Shop2", "User2@login.com", "222", Timestamp_2};
    auto entry_3 = Entry{};

    EXPECT_EQ("1 | Shop1 | User1@login.com | 111 | +", entry_1.getAsString());
    EXPECT_EQ("2 | Shop2 | User2@login.com | 222 | -", entry_2.getAsString());

    std::swap(entry_1, entry_2);

    EXPECT_EQ("2 | Shop2 | User2@login.com | 222 | -", entry_1.getAsString());
    EXPECT_EQ("1 | Shop1 | User1@login.com | 111 | +", entry_2.getAsString());

    entry_2 = entry_1;

    EXPECT_EQ("2 | Shop2 | User2@login.com | 222 | -", entry_2.getAsString());

    entry_3 = std::move(entry_1);

    EXPECT_EQ("2 | Shop2 | User2@login.com | 222 | -", entry_3.getAsString());
}

TEST(DatabaseEntry, Setters)
{
    auto OutdatedTimestamp = std::time(0);
    OutdatedTimestamp -= 2 * PASSWORD_UPDATING_PERIOD;
    auto entry = Entry{10, "Shop", "User@login.com", "123456", OutdatedTimestamp};
    EXPECT_EQ("10 | Shop | User@login.com | 123456 | -", entry.getAsString());

    const entry_name_t expectedName = "Not shop";
    entry.setEntryName(expectedName);
    EXPECT_EQ(expectedName + " | -", entry.getAsString(enumToValue(Field::NAME | Field::IS_PASSWORD_OUTDATED)));

    const login_t expectedLogin = "No login";
    entry.setLogin(expectedLogin);
    EXPECT_EQ(expectedLogin + " | -", entry.getAsString(enumToValue(Field::LOGIN | Field::IS_PASSWORD_OUTDATED)));

    const password_t expectedPassword = "654321";
    entry.setPassword(expectedPassword);
    EXPECT_EQ(expectedPassword + " | +", entry.getAsString(enumToValue(Field::PASSWORD | Field::IS_PASSWORD_OUTDATED)));
}
