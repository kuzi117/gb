#ifndef GB_SIMULATOR_H
#define GB_SIMULATOR_H

#include "sim/mem/MemoryController.h"
#include "sim/RegisterInfo.h"

#include <memory>

namespace regdefaults {

//! The default value for the 4 physical registers.
constexpr uint16_t physRegs[4] = {0x01B0, 0x0013, 0x00D8, 0x014D};

}

class Simulator {
public:
  //! Simulator must be loaded with a ROM.
  Simulator() = delete;

  //! Simulator doesn't support copy construction.
  Simulator(const Simulator &) = delete;

  /**
   * \brief Initialise the simulator.
   *
   *
   * This initialises the simulator with the ROM located at the provided
   * filepath.
   *
   * \param romLoc Filepath to ROM.
   */
  Simulator(const char *romLoc);

  //! Run the simulation.
  void run();

private:
  //! Reset the simulator's internal state (registers, RAM, stack, etc.).
  void reset();

  /**
   * \brief Load the ROM located at the filepath provided.
   * \param romLoc The filepath for the ROM.
   */
  void load(const char *romLoc);

private:
  //! The simulator's current program counter.
  uint16_t PC;

  //! The simulator's current stack pointer.
  uint16_t SP;

  //! The simulator's registers.
  uint16_t regs[4];

  //! The memory controller for the simulator, created based on ROM.
  std::unique_ptr<MemoryController> mem;
};

#endif // GB_SIMULATOR_H
