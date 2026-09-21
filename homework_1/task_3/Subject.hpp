#pragma once

#include <cstddef>
#include <memory>
#include <vector>

class Student;

/**
 * @brief Представляет предмет и связанных с ним студентов.
 */
class Subject {
 public:
  /**
   * @brief Создаёт предмет с указанным номером.
   * @param number номер предмета
   */
  explicit Subject(std::size_t number);

  /**
   * @brief Возвращает номер предмета.
   * @return номер предмета
   */
  std::size_t Number() const;

  /**
   * @brief Проверяет, привязан ли студент к предмету.
   * @param student проверяемый студент
   * @return `true`, если студент привязан к предмету
   */
  bool HasStudent(const std::shared_ptr<Student>& student) const;

  /**
   * @brief Привязывает студента к предмету.
   * @param student привязываемый студент
   * @throw std::invalid_argument если студент уже привязан к предмету
   */
  void AddStudent(const std::shared_ptr<Student>& student);

  /**
   * @brief Удаляет привязку студента к предмету.
   * @param student удаляемый студент
   * @throw std::invalid_argument если студент не привязан к предмету
   */
  void RemoveStudent(const std::shared_ptr<Student>& student);

  /**
   * @brief Возвращает студентов, привязанных к предмету.
   * @return слабые указатели на студентов
   */
  const std::vector<std::weak_ptr<Student>>& Students() const;

 private:
  std::size_t _number;
  std::vector<std::weak_ptr<Student>> _students;
};
