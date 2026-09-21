#include <iostream>
#include <memory>
#include <sstream>

#include "fun.hpp"

namespace {

// MARK: Redirect program output
// --------------------------------------------------

std::streambuf* RedirectOutput(std::streambuf* replacement_buffer) {
  return std::cout.rdbuf(replacement_buffer);
}

// --------------------------------------------------

void RestoreOutput(std::streambuf* previous_buffer) {
  std::cout.rdbuf(previous_buffer);
}

}  // namespace

// MARK: Program entry point
// --------------------------------------------------

int main() {
  auto ignored_output = std::make_unique<std::ostringstream>();

  std::streambuf* previous_buffer = RedirectOutput(ignored_output->rdbuf());

  fun();

  RestoreOutput(previous_buffer);

  std::cout << "main () successfully called fun ()\n";

  return 0;
}
