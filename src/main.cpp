#include "sim/Simulator.h"

#include "loguru.hpp"

int main(int argc, char **argv) {
  loguru::Options opts {"-v", "main", true};
  loguru::init(argc, argv, opts);

  LOG_F(INFO, "Creating simulator.");
  Simulator sim(argv[1]);

  sim.run();

  loguru::shutdown();
  return 0;
}
