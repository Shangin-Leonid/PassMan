#pragma once

#include <optional>

#include "Database_entry/header/DBE_Types_Fwd.h"

namespace DatabaseEntry
{

/*
** Programm (not source data) description of single 'PassMan' database entry.
*/
class Entry final
{
  public:

    // TODO: add all methods needed to use this class with 'std::set' and 'std::map'.

    Entry() = delete;
    Entry(const Entry& origin) = default;
    Entry(Entry&& rvalRef) noexcept;
    Entry(const id_t id,
          const entry_name_t& entryName,
          const login_t& login,
          const password_t& password,
          const std::optional<date_t> lastPasswordEditDate = std::nullopt);
    Entry(const id_t id,
          entry_name_t&& entryName,
          login_t&& login,
          password_t&& password,
          const std::optional<date_t> lastPasswordEditDate = std::nullopt) noexcept;

    Entry& operator=(const Entry& another) = default;
    Entry& operator=(Entry&& rvalRef) noexcept;

    // Returns string representation of chosen entry fields.
    string_t getAsString(const Fields& fields = Fields{ALL_FIELDS}) const;

    void setEntryName(const string_t& newEntryName);
    void setEntryName(string_t&& newEntryName) noexcept;

    void setLogin(const string_t& newLogin);
    void setLogin(string_t&& newLogin) noexcept;

    void setPassword(const string_t& newPassword);
    void setPassword(string_t&& newPassword) noexcept;

  private:

    size_t getFieldsLength(const Fields& fields = Fields{ALL_FIELDS}) const noexcept;

    void updateLastEditDate() noexcept;

  private:

    id_t _id;
    entry_name_t _entryName; // Name of organization / site / service.
    login_t _login; // Phone number / email / etc..
    password_t _password;
    bool _isOutdated; // Does password need update?

    date_t _lastPasswordEditDate;
};

} // namespace DatabaseEntry
