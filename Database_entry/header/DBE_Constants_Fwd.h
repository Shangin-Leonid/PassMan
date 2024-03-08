#pragma once

#include <type_traits>

#include "Database_entry/header/DBE_Types_Fwd.h"

namespace DatabaseEntry
{

// TODO: move it to 'Utils' component.
template <typename Enum>
constexpr auto enumToValue(const Enum enumToValue) -> typename std::underlying_type_t<Enum>
{
    static_assert(std::is_enum_v<Enum>);

    return static_cast<typename std::underlying_type_t<Enum>>(enumToValue);
}

enum class FieldIndex : uint8_t
{
    // clang-format off
    ID                   = 0,
    NAME                 = 1,
    LOGIN                = 2,
    PASSWORD             = 3,
    IS_PASSWORD_OUTDATED = 4
    // clang-format on
};

enum class Field : uint8_t
{
    // clang-format off
    ID                   = 1 << enumToValue(FieldIndex::ID),
    NAME                 = 1 << enumToValue(FieldIndex::NAME),
    LOGIN                = 1 << enumToValue(FieldIndex::LOGIN),
    PASSWORD             = 1 << enumToValue(FieldIndex::PASSWORD),
    IS_PASSWORD_OUTDATED = 1 << enumToValue(FieldIndex::IS_PASSWORD_OUTDATED)
    // clang-format on
};

inline Field operator|(const Field field1, const Field field2)
{
    return static_cast<Field>(enumToValue(field1) | enumToValue(field2));
}

const string_t FIELD_SEPARATOR_SYMBOL = "|";
const string_t FIELD_SEPARATOR = " " + FIELD_SEPARATOR_SYMBOL + " ";

constexpr size_t PASSWORD_UPDATING_PERIOD_IN_DAYS = 180;
constexpr time_t PASSWORD_UPDATING_PERIOD = 86400 * PASSWORD_UPDATING_PERIOD_IN_DAYS;
constexpr symbol_t PASSWORD_NOT_OUTDATED_SYMBOL = '+';
constexpr symbol_t PASSWORD_OUTDATED_SYMBOL = '-';

} // namespace DatabaseEntry
