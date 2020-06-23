#ifndef GB_MEMORYCONTROLLER_H
#define GB_MEMORYCONTROLLER_H

#include <cstdint>
#include <memory>

namespace memdefaults {
//! The default values for the first part of the reset-able I/O registers.
constexpr uint8_t ioRegs1[20] = {0x00, 0x00, 0x00, 0x80, 0xBF, 0xF3, 0xBF,
                                 0x3F, 0x00, 0xBF, 0x7F, 0xFF, 0x9F, 0xBF,
                                 0xFF, 0x00, 0x00, 0xBF, 0x77, 0xF3};

//! The NR52 Gameboy value.
constexpr uint8_t nr52GB = 0xF1;

//! The NR52 Super Gameboy value.
constexpr uint8_t nr52SGB = 0xF0;

//! The default values for the second part of the reset-able I/O registers.
constexpr uint8_t ioRegs2[9] = {0x91, 0x00, 0x00, 0x00, 0xFC,
                                0xFF, 0xFF, 0x00, 0x00};
} // End namespace memdefaults.

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
