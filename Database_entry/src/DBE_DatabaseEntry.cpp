#include <ctime>

#include "Database_entry/DBE_DatabaseEntry.h"
#include "Database_entry/header/DBE_Constants_Fwd.h"

namespace DatabaseEntry
{

// public

Entry::Entry(Entry&& rvalRef) noexcept :
    _id(rvalRef._id),
    _entryName(std::move(rvalRef._entryName)),
    _login(std::move(rvalRef._login)),
    _password(std::move(rvalRef._password)),
    _isOutdated(rvalRef._isOutdated),
    _lastPasswordEditDate(rvalRef._lastPasswordEditDate)
{
}

Entry::Entry(const id_t id,
             const entry_name_t& entryName,
             const login_t& login,
             const password_t& password,
             const std::optional<date_t> lastPasswordEditDate) :
    _id(id),
    _entryName(entryName),
    _login(login),
    _password(password),
    _lastPasswordEditDate(lastPasswordEditDate.value_or(std::time(0)))
{
    _isOutdated = (lastPasswordEditDate ? (std::time(0) - _lastPasswordEditDate > PASSWORD_UPDATING_PERIOD) : false);
}

Entry::Entry(const id_t id,
             entry_name_t&& entryName,
             login_t&& login,
             password_t&& password,
             std::optional<date_t> lastPasswordEditDate) noexcept :
    _id(id),
    _entryName(std::move(entryName)),
    _login(std::move(login)),
    _password(std::move(password)),
    _lastPasswordEditDate(lastPasswordEditDate.value_or(std::time(0)))
{
    _isOutdated = (lastPasswordEditDate ? (std::time(0) - _lastPasswordEditDate > PASSWORD_UPDATING_PERIOD) : false);
}

Entry& Entry::operator=(Entry&& rvalRef) noexcept
{
    _id = rvalRef._id;
    _entryName = std::move(rvalRef._entryName);
    _login = std::move(rvalRef._login);
    _password = std::move(rvalRef._password);
    _isOutdated = rvalRef._isOutdated;
    _lastPasswordEditDate = rvalRef._lastPasswordEditDate;

    return *this;
}

void Entry::setEntryName(const string_t& newEntryName)
{
    _entryName = newEntryName;
}

void Entry::setEntryName(string_t&& newEntryName) noexcept
{
    _entryName = std::move(newEntryName);
}

void Entry::setLogin(const string_t& newLogin)
{
    _login = newLogin;
}

void Entry::setLogin(string_t&& newLogin) noexcept
{
    _login = std::move(newLogin);
}

void Entry::setPassword(const string_t& newPassword)
{
    _password = newPassword;
    _isOutdated = false;
}

void Entry::setPassword(string_t&& newPassword) noexcept
{
    _password = std::move(newPassword);
    _isOutdated = false;
}

string_t Entry::getAsString(const Fields& fields) const
{
    string_t fieldsAsStr;

    fieldsAsStr.reserve(getFieldsLength(fields) + (fields.count() - 1) * std::size(FIELD_SEPARATOR));

    const auto addFieldIfNeeded = [&fieldsAsStr, &fields](const FieldIndex fieldIndex, const string_t& fieldAsStr)
    {
        //constexpr symbol_t FIELD_SEPARATOR_XXX[] = {' ', /*FIELD_SEPARATOR_SYMBOL*/ '|', ' '};

        if (!fields.test(enumToValue(fieldIndex)))
            return;

        if (fieldsAsStr.empty())
            fieldsAsStr += fieldAsStr;
        else
            fieldsAsStr += FIELD_SEPARATOR + fieldAsStr;
    };

    addFieldIfNeeded(FieldIndex::ID, to_string_t(_id));
    addFieldIfNeeded(FieldIndex::NAME, _entryName);
    addFieldIfNeeded(FieldIndex::LOGIN, _login);
    addFieldIfNeeded(FieldIndex::PASSWORD, _password);
    addFieldIfNeeded(FieldIndex::IS_PASSWORD_OUTDATED,
                     string_t{_isOutdated ? PASSWORD_OUTDATED_SYMBOL : PASSWORD_NOT_OUTDATED_SYMBOL});

    return fieldsAsStr;
}

// private

namespace
{

size_t countDigits(const id_t id) noexcept
{
    // clang-format off
    return (id < 10 ? 1 :
           (id < 100 ? 2 :
           (id < 1000 ? 3 :
           (id < 10000 ? 4 :
           (id < 100000 ? 5 :
           (id < 1000000 ? 6 :
           (id < 10000000 ? 7 :
           (id < 100000000 ? 8 :
           (id < 1000000000 ? 9 : 10)))))))));
    // clang-format on
}

} // anonymous namespace

size_t Entry::getFieldsLength(const Fields& fields) const noexcept
{
    size_t length = 0;

    if (fields.test(enumToValue(FieldIndex::ID)))
        length += countDigits(_id);
    if (fields.test(enumToValue(FieldIndex::NAME)))
        length += _entryName.size();
    if (fields.test(enumToValue(FieldIndex::LOGIN)))
        length += _login.size();
    if (fields.test(enumToValue(FieldIndex::PASSWORD)))
        length += _password.size();
    if (fields.test(enumToValue(FieldIndex::IS_PASSWORD_OUTDATED)))
        length += 1;

    return length;
}

void Entry::updateLastEditDate() noexcept
{
    _lastPasswordEditDate = std::time(0);
}

} // namespace DatabaseEntry
