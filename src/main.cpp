#include "loguru.hpp"

int main(int argc, char **argv) {
  loguru::Options opts {"-v", "main", true};
  loguru::init(argc, argv, opts);

  loguru::shutdown();
  return 0;
}
