#pragma once

#include <string>
#include <unordered_map>

/**
 * @brief Задаёт поле, по которому сортируется список студентов.
 */
enum class SortField { FirstName, LastName, TicketNumber, Grade };

inline const std::unordered_map<std::string, SortField> SORT_FIELDS = {
    {"first_name", SortField::FirstName},
    {"last_name", SortField::LastName},
    {"ticket_number", SortField::TicketNumber},
    {"grade", SortField::Grade},
};
