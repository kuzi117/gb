#ifndef GB_MEMORYCONTROLLER_H
#define GB_MEMORYCONTROLLER_H

#include "loguru.hpp"

#include <cstdint>
#include <memory>

//! Namespace holding memory defaults.
namespace memdefaults {

struct MemValue {
  //! No default constructor.
  MemValue() = delete;

  //! Construct with value and location.
  constexpr MemValue(uint16_t location, uint8_t value) : location(location), value(value) { }

  //! The memory location for this value.
  const uint16_t location;

  //! The memory value.
  const uint8_t value;
};

//! The default values for the reset-able I/O registers.
constexpr MemValue ioRegs[29] = {
    {0xFF05, 0x00}, {0xFF06, 0x00}, {0xFF07, 0x00}, {0xFF10, 0x80},
    {0xFF11, 0xBF}, {0xFF12, 0xF3}, {0xFF14, 0xBF}, {0xFF16, 0x3F},
    {0xFF17, 0x00}, {0xFF19, 0xBF}, {0xFF1A, 0x7F}, {0xFF1B, 0xFF},
    {0xFF1C, 0x9F}, {0xFF1E, 0xBF}, {0xFF20, 0xFF}, {0xFF21, 0x00},
    {0xFF22, 0x00}, {0xFF23, 0xBF}, {0xFF24, 0x77}, {0xFF25, 0xF3},
    {0xFF40, 0x91}, {0xFF42, 0x00}, {0xFF43, 0x00}, {0xFF45, 0x00},
    {0xFF47, 0xFC}, {0xFF48, 0xFF}, {0xFF49, 0xFF}, {0xFF4A, 0x00},
    {0xFF4B, 0x00}};

//! The NR52 Gameboy value.
constexpr MemValue nr52GB(0xFF26, 0xF1);

//! The NR52 Super Gameboy value.
constexpr MemValue nr52SGB(0xFF26, 0xF0);

//! The default value for the Interrupts Enable register.
constexpr MemValue ie(0xFFFF, 0x00);

} // End namespace memdefaults.

//! Namespace holding memory utilities.
namespace memutil {

//! Performs a 16-bit, little-endian read.
template<std::size_t size>
inline uint16_t leRead16(const std::array<uint8_t, size> &mem, uint16_t address) {
  LOG_IF_F(WARNING, address >= mem.size(), "Read out of bounds: %u > %ul", address, mem.size());
  uint16_t word = mem[address + 1];
  word <<= 8u;
  word |= mem[address];
  return word;
}

//! Performs a 16-bit, little-endian write.
template<std::size_t size>
inline void leWrite16(std::array<uint8_t, size> &mem, uint16_t address, uint16_t value) {
  LOG_IF_F(WARNING, address >= mem.size(), "Write out of bounds: %u > %ul", address, mem.size());
  mem[address] = static_cast<uint8_t>(value & 0xFFu);
  mem[address + 1] = static_cast<uint8_t>((value & 0xFF00u) >> 8u);
}

} // End namespace memutil.

/**
 * \brief Base class for all memory controllers.
 *
 * The base class for all memory controllers, defining all of the read and write
 * methods.
 */
class MemoryController {
protected:
  //! Sixteen kilobytes. Defined for convenience.
  constexpr static size_t kilo16 = 1u << 14u;

  //! Sixteen kilobytes. Defined for convenience.
  constexpr static size_t kilo8 = 1u << 13u;

  //! Sixteen kilobytes. Defined for convenience.
  constexpr static size_t kilo4 = 1u << 12u;

  //! A sixteen kilobyte array.
  typedef std::array<uint8_t, kilo16> array16k;

  //! An eight kilobyte array.
  typedef std::array<uint8_t, kilo8> array8k;

  //! A four kilobyte array.
  typedef std::array<uint8_t, kilo4> array4k;

  //! Sprite attribute table, a 160 byte array.
  typedef std::array<uint8_t, 160> arraySAT;

  //! I/O registers, a 128 byte array.
  typedef std::array<uint8_t, 128> arrayIO;

  //! High RAM sized 128 byte array.
  typedef std::array<uint8_t, 127> arrayHR;

public:
  //! Initialise all memory fields to nullptr.
  MemoryController()
      : ROM0(nullptr), ROM1(nullptr), VRAM(nullptr), ERAM(nullptr),
        WRAM0(nullptr), WRAM1(nullptr), SAT(nullptr), HRAM(nullptr),
        IO(nullptr), IER(nullptr) {}

  virtual ~MemoryController() = default;

  /**
   * \brief Read 8 bits from the specified address.
   *
   * Subclasses should override this to provide correct reading behaviour
   * depending on MCB mode.
   *
   * \param address The address to read from.
   * \return The byte at the address.
   */
  virtual uint8_t read8(uint16_t address) const = 0;

  /**
   * \brief Read 16 bits from the specified address.
   *
   * Subclasses should override this to provide correct reading behaviour
   * depending on MCB mode.
   *
   * \param address The address to read from.
   * \return The byte at the address.
   */
  virtual uint16_t read16(uint16_t address) const = 0;

  /**
   * \brief Write 8 bits to the specified address.
   *
   * Subclasses should override this to provide correct writing behaviour
   * depending on MCB mode.
   *
   * \param address The address to write to.
   * \param data The byte to write.
   * \return The byte at the address.
   */
  virtual void write(uint16_t address, uint8_t data) = 0;

  /**
   * \brief Write a 16-bit word (little endian) to the specified address.
   *
   * Subclasses should override this to provide correct writing behaviour
   * depending on MCB mode.
   *
   * \param address The address to write to.
   * \param data The 16-bit word to write.
   * \return The byte at the address.
   */
  virtual void write(uint16_t address, uint16_t data) = 0;

  /**
   * \brief Reset memory to initial values.
   *
   * Subclasses should override this to provide correct memory reset behaviour.
   */
  virtual void reset() = 0;

protected:
  //! ROM bank 00, fixed.
  std::unique_ptr<std::array<uint8_t, kilo16>> ROM0;

  //! ROM Bank 01-NN, switchable based on MBC mode.
  std::unique_ptr<std::array<uint8_t, kilo16>> ROM1;

  //! VRAM Bank 0-1. Switchable in CGB mode, locked to 0 in non-CGB mode.
  std::unique_ptr<array8k> VRAM;

  //! External Ram.
  std::unique_ptr<array8k> ERAM;

  //! Work ram bank 0.
  std::unique_ptr<array4k> WRAM0;

  //! Work ram bank 1-N. Up to 7 in CGB, locked to 1 in non-CGB mode.
  std::unique_ptr<array4k> WRAM1;

  //! Sprite attribute table.
  std::unique_ptr<arraySAT> SAT;

  //! I/O registers.
  std::unique_ptr<arrayIO> IO;

  //! High RAM;
  std::unique_ptr<arrayHR> HRAM;

  //! Interrupts Enable (IE) register.
  std::unique_ptr<uint8_t> IER;
};

#endif // GB_MEMORYCONTROLLER_H
