#ifndef GB_MBC0_H
#define GB_MBC0_H

#include "sim/mem/MemoryController.h"

class MBC0 : public MemoryController {
public:
  /**
   * \brief Construct with ROM to map to memory.
   */
    MBC0(std::ifstream &rom);

  /**
   * \brief Read 8 bits from the specified address.
   *
   * Subclasses should override this to provide correct reading behaviour
   * depending on MCB mode.
   *
   * \param address The address to read from.
   * \return The byte at the address.
   */
  uint8_t read8(uint16_t address) const override;

  /**
   * \brief Read 16 bits from the specified address.
   *
   * Subclasses should override this to provide correct reading behaviour
   * depending on MCB mode.
   *
   * \param address The address to read from.
   * \return The byte at the address.
   */
  uint16_t read16(uint16_t address) const override;

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
  void write(uint16_t address, uint8_t data) override;

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
  void write(uint16_t address, uint16_t data) override;

  /**
   * \brief Reset memory to initial values.
   *
   * Subclasses should override this to provide correct memory reset behaviour.
   */
  void reset() override;
};

#endif // GB_MBC0_H
