#pragma once

#include <cstddef>
#include <iosfwd>
#include <map>
#include <string>

/**
 * @brief Представляет сведения об одном студенте.
 */
class Student {
 public:
  /**
   * @brief Создаёт студента с указанными персональными данными и оценками.
   * @param first_name имя студента
   * @param last_name фамилия студента
   * @param ticket_number номер студенческого билета
   * @param subject_average_grades средние оценки по номерам предметов
   */
  Student(const std::string& first_name, const std::string& last_name,
          const std::string& ticket_number,
          const std::map<std::size_t, double>& subject_average_grades);

  /**
   * @brief Возвращает имя студента.
   * @return имя студента
   */
  const std::string& FirstName() const;

  /**
   * @brief Возвращает фамилию студента.
   * @return фамилия студента
   */
  const std::string& LastName() const;

  /**
   * @brief Возвращает номер студенческого билета.
   * @return номер студенческого билета
   */
  const std::string& TicketNumber() const;

  /**
   * @brief Возвращает средние оценки студента по предметам.
   * @return соответствие номеров предметов и средних оценок
   */
  const std::map<std::size_t, double>& SubjectAverageGrades() const;

 private:
  std::string _first_name;
  std::string _last_name;
  std::string _ticket_number;
  std::map<std::size_t, double> _subject_average_grades;
};

/**
 * @brief Выводит сведения о студенте в поток.
 * @param output поток вывода
 * @param student студент для вывода
 * @return поток вывода
 */
std::ostream& operator<<(std::ostream& output, const Student& student);
