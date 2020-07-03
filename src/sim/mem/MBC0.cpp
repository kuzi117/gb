#include "sim/mem/MBC0.h"

#include "loguru.hpp"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <memory>

MBC0::MBC0(std::ifstream &rom) : MemoryController() {
  LOG_F(INFO, "Initialising MBC0.");

  // Seek to beginning.
  rom.seekg(0, std::ifstream::beg);

  // Allocate ROM space.
  DLOG_F(1, "Allocating ROM0.");
  ROM0 = std::make_unique<array16k>();
  DLOG_F(1, "ROM0 Allocated.");
  DLOG_F(1, "Allocating ROM1.");
  ROM1 = std::make_unique<array16k>();
  DLOG_F(1, "ROM1 Allocated.");

  // Copy ROM data.
  DLOG_S(1) << "Copying to ROM0: " << rom.tellg() << ", " << std::boolalpha << rom.good();
  rom.read(reinterpret_cast<char *>(ROM0->begin()), kilo16);
  DLOG_S(1) << "Copied to ROM0: " << rom.tellg() << ", " << std::boolalpha << rom.good();
  DLOG_F(1, "Copying to ROM0: %lu", static_cast<uint64_t>(rom.tellg()));
  DLOG_S(1) << "Copying to ROM1: " << rom.tellg() << ", " << std::boolalpha << rom.good();
  rom.read(reinterpret_cast<char *>(ROM1->begin()), kilo16);
  DLOG_F(1, "Copied to ROM1: %lu", static_cast<uint64_t>(rom.tellg()));
}

uint8_t MBC0::read8(uint16_t address) const {
  DLOG_F(2, "Read8: mem[0x%04X]", address);
  return 0;
}

uint16_t MBC0::read16(uint16_t address) const {
  DLOG_F(2, "Read16 mem[0x%04X]", address);
  return 0;
}

void MBC0::write(uint16_t address, uint8_t data) {
  DLOG_F(2, "Write8: mem[0x%04X] <- 0x%02X", address, data);
}

void MBC0::write(uint16_t address, uint16_t data) {
  DLOG_F(2, "Write16: mem[0x%04X] <- 0x%02X", address, data);
}

void MBC0::reset() {
  LOG_F(INFO, "Memory (MBC0) resetting.");

  // Reset the I/O registers.
  DLOG_F(1, "Resetting I/O registers.");
  for (const memdefaults::MemValue mv : memdefaults::ioRegs)
    write(mv.location, mv.value);
  DLOG_F(1, "Finished resetting I/O registers.");

  // Reset the interrupt enable register.
  DLOG_F(1, "Resetting IE register.");
  const memdefaults::MemValue &ie = memdefaults::ie;
  write(ie.location, ie.value);
  DLOG_F(1, "Finished resetting IE register.");

  LOG_F(INFO, "Memory (MBC0) finished resetting.");
}
