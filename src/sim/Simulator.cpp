#include "sim/Simulator.h"

#include "sim/mem/MBC0.h"

#include "loguru.hpp"

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace regdefaults;

namespace {


} // End anonymous namespace.

// Init values to 0 so as to avoid undefined behaviour in calling member
// functions (i.e. reset).
Simulator::Simulator(const char *romLoc) : PC(0), SP(0), regs{0}, mem(nullptr) {
  load(romLoc);
  reset();
}

void Simulator::reset() {
  LOG_F(INFO, "Resetting simulator.");

  // Reset registers.
  DLOG_F(1, "Resetting physical registers.");
  PC = 0;
  SP = 0xFFFE;
  std::memcpy(regs, physRegs, sizeof physRegs);
  DLOG_F(1, "Done resetting physical registers.");

  // Reset memory.
  assert(mem != nullptr && "Memory controller was null.");
  mem->reset();

  LOG_F(INFO, "Finished resetting simulator.");
}

void Simulator::load(const char *romLoc) {
}

void Simulator::run() {
}

