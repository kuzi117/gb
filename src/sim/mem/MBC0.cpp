#include "sim/mem/MBC0.h"

#include "loguru.hpp"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <memory>

using namespace memutil;

MBC0::MBC0(std::ifstream &rom) : MemoryController() {
  LOG_F(INFO, "Initialising MBC0.");

  // Seek to beginning.
  rom.seekg(0, std::ifstream::beg);

  // Allocate ROM space.
  DLOG_F(1, "Allocating ROM0.");
  ROM0 = std::make_unique<array16k>();
  DLOG_F(1, "ROM0 allocated.");
  DLOG_F(1, "Allocating ROM1.");
  ROM1 = std::make_unique<array16k>();
  DLOG_F(1, "ROM1 allocated.");

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
  // ROM0.
  if (address < 0x4000u) {
    return (*ROM0)[address];
  }
  // ROM1.
  else if (address < 0x8000u) {
    return (*ROM1)[address - 0x4000u];
  }
  // VRAM.
  else if (address < 0xA000u) {
    LOG_F(WARNING, "Read from VRAM unimplemented.");
  }
  // ERAM.
  else if (address < 0xC000u) {
    LOG_F(WARNING, "Read from ERAM unimplemented.");
  }
  // WRAM0.
  else if (address < 0xD000u) {
    LOG_F(WARNING, "Read from WRAM0 unimplemented.");
  }
  // WRAM1.
  else if (address < 0xE000u) {
    LOG_F(WARNING, "Read from WRAM1 unimplemented.");
  }
  // Echo RAM/unused.
  else if (address < 0xFE00u) {
    LOG_F(WARNING, "Read from Echo RAM unimplemented.");
  }
  // Sprite attribute table.
  else if (address < 0xFEA0u) {
    LOG_F(WARNING, "Read from sprite attribute table unimplemented.");
  }
  // Unusable range.
  else if (address < 0xFF00u) {
    LOG_F(WARNING, "Read from unusable: ignored.");
  }
  // I/O registers.
  else if (address < 0xFF80u) {

  }
  // HRAM.
  else if (address < 0xFFFFu) {
    LOG_F(WARNING, "Read from Echo RAM unimplemented.");
  }
  // Interrupts enable register.
  else if (address == 0xFFFFu) {
    LOG_F(WARNING, "Read from IE unimplemented.");
  }
  return 0;
}

uint16_t MBC0::read16(uint16_t address) const {
  DLOG_F(2, "Read16 mem[0x%04X]", address);
  // ROM0.
  if (address < 0x4000u) {
    return leRead16(*ROM0, address);
  }
  // ROM1.
  else if (address < 0x8000u) {
    return leRead16(*ROM1, address - 0x4000u);
  }
  // VRAM.
  else if (address < 0xA000u) {
    LOG_F(WARNING, "Read from VRAM unimplemented.");
  }
  // ERAM.
  else if (address < 0xC000u) {
    LOG_F(WARNING, "Read from ERAM unimplemented.");
  }
  // WRAM0.
  else if (address < 0xD000u) {
    LOG_F(WARNING, "Read from WRAM0 unimplemented.");
  }
  // WRAM1.
  else if (address < 0xE000u) {
    LOG_F(WARNING, "Read from WRAM1 unimplemented.");
  }
  // Echo RAM/unused.
  else if (address < 0xFE00u) {
    LOG_F(WARNING, "Read from Echo RAM unimplemented.");
  }
  // Sprite attribute table.
  else if (address < 0xFEA0u) {
    LOG_F(WARNING, "Read from sprite attribute table unimplemented.");
  }
  // Unusable range.
  else if (address < 0xFF00u) {
    LOG_F(WARNING, "Read from unusable: ignored.");
  }
  // I/O registers.
  else if (address < 0xFF80u) {

  }
  // HRAM.
  else if (address < 0xFFFFu) {
    LOG_F(WARNING, "Read from Echo RAM unimplemented.");
  }
  // Interrupts enable register.
  else if (address == 0xFFFFu) {
    ABORT_F("Reading 16 bit value from interrupts enable register.");
  }
  return 0;
}

void MBC0::write(uint16_t address, uint8_t data) {
  DLOG_F(2, "Write8: mem[0x%04X] <- 0x%02X", address, data);
  // ROM0.
  if (address < 0x4000u) {
    LOG_F(WARNING, "Write to ROM0: ignored.");
  }
  // ROM1.
  else if (address < 0x8000u) {
    LOG_F(WARNING, "Write to ROM1: ignored.");
  }
  // VRAM.
  else if (address < 0xA000u) {
    LOG_F(WARNING, "Write to VRAM unimplemented.");
  }
  // ERAM.
  else if (address < 0xC000u) {
    LOG_F(WARNING, "Write to ERAM unimplemented.");
  }
  // WRAM0.
  else if (address < 0xD000u) {
    LOG_F(WARNING, "Write to WRAM0 unimplemented.");
  }
  // WRAM1.
  else if (address < 0xE000u) {
    LOG_F(WARNING, "Write to WRAM1 unimplemented.");
  }
  // Echo RAM/unused.
  else if (address < 0xFE00u) {
    LOG_F(WARNING, "Write to Echo RAM unimplemented.");
  }
  // Sprite attribute table.
  else if (address < 0xFEA0u) {
    LOG_F(WARNING, "Write to sprite attribute table unimplemented.");
  }
  // Unusable range.
  else if (address < 0xFF00u) {
    LOG_F(WARNING, "Write to unusable: ignored.");
  }
  // I/O registers.
  else if (address < 0xFF80u) {
    LOG_F(WARNING, "Write to IO registers unimplemented.");
  }
  // HRAM.
  else if (address < 0xFFFFu) {
    LOG_F(WARNING, "WRITE TO Echo RAM unimplemented.");
  }
  // Interrupts enable register.
  else if (address == 0xFFFFu) {
    if (IER == nullptr)
      IER = std::make_unique<uint8_t>();
    *IER = data;
  }
}

void MBC0::write(uint16_t address, uint16_t data) {
  DLOG_F(2, "Write16: mem[0x%04X] <- 0x%02X", address, data);
  // ROM0.
  if (address < 0x4000u) {
    LOG_F(WARNING, "Write16 to ROM0: ignored.");
  }
  // ROM1.
  else if (address < 0x8000u) {
    LOG_F(WARNING, "Write16 to ROM1: ignored.");
  }
  // VRAM.
  else if (address < 0xA000u) {
    LOG_F(WARNING, "Write to VRAM unimplemented.");
  }
  // ERAM.
  else if (address < 0xC000u) {
    LOG_F(WARNING, "Write to ERAM unimplemented.");
  }
  // WRAM0.
  else if (address < 0xD000u) {
    LOG_F(WARNING, "Write to WRAM0 unimplemented.");
  }
  // WRAM1.
  else if (address < 0xE000u) {
    LOG_F(WARNING, "Write to WRAM1 unimplemented.");
  }
  // Echo RAM/unused.
  else if (address < 0xFE00u) {
    LOG_F(WARNING, "Write to Echo RAM unimplemented.");
  }
  // Sprite attribute table.
  else if (address < 0xFEA0u) {
    LOG_F(WARNING, "Write to sprite attribute table unimplemented.");
  }
  // Unusable range.
  else if (address < 0xFF00u) {
    LOG_F(WARNING, "Write to unusable: ignored.");
  }
  // I/O registers.
  else if (address < 0xFF80u) {

  }
  // HRAM.
  else if (address < 0xFFFFu) {
    LOG_F(WARNING, "WRITE TO Echo RAM unimplemented.");
  }
  // Interrupts enable register.
  else if (address == 0xFFFFu) {
    ABORT_F("Writing 16 bit value to interrupts enable register.");
  }
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
