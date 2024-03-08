#pragma once

#include <bitset>
#include <string>
#include <string_view>
#include <ctime>

namespace DatabaseEntry
{

// std::basic_string<symbol_t>
constexpr bool IS_WCHAR_ELSE_CHAR = false;
using symbol_t = std::conditional_t<IS_WCHAR_ELSE_CHAR, wchar_t, char>;
using string_t = std::conditional_t<IS_WCHAR_ELSE_CHAR, std::wstring, std::string>;
using string_view_t = std::conditional_t<IS_WCHAR_ELSE_CHAR, std::wstring_view, std::string_view>;

template <typename T>
constexpr string_t to_string_t(const T number)
{
    static_assert(std::is_arithmetic_v<T> && !std::is_same_v<bool, T>);

    if constexpr (std::is_same_v<std::wstring, string_t>)
        return std::to_wstring(number);
    else
        return std::to_string(number);
}

using id_t = size_t;

using entry_name_t = string_t;
using name_view_t = string_view_t;

using login_t = string_t;
using login_view_t = string_view_t;

using password_t = string_t;
using password_view_t = string_view_t;

using date_t = time_t;

constexpr size_t AMOUNT_OF_DB_FIELDS = 5;
using Fields = std::bitset<AMOUNT_OF_DB_FIELDS>;
constexpr size_t ALL_FIELDS = (2 << AMOUNT_OF_DB_FIELDS) - 1;

} // namespace DatabaseEntry
