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
  DLOG_S(INFO) << "Opening ROM at " << romLoc;
  std::ifstream rom(romLoc, std::ifstream::in | std::ifstream::binary);

  if (!rom.is_open())
    ABORT_F("ROM failed to open.");

  mem = std::make_unique<MBC0>(rom);

#ifndef DNDEBUG
  rom.seekg(0, std::ifstream::end);
  std::streampos trueSize = rom.tellg();
  rom.seekg(0, std::ifstream::beg);
  DLOG_S(1) << "ROM true size: " << trueSize;
#endif

  rom.seekg(0x148, std::ifstream::beg);

  uint8_t byte;
  rom >> byte;
  DLOG_IF_F(1, rom.bad(), "ROM read failure!");

  uint32_t size = 1u << (15u + byte);
  DLOG_F(1, "ROM calculated size: %u", size);

#ifndef DNDEBUG
  DLOG_IF_F(WARNING, trueSize != size,
            "True and calculated ROM size mismatch! True: %u, calculated: %u",
            static_cast<unsigned>(trueSize), size);
#endif

}

void Simulator::run() {
}

