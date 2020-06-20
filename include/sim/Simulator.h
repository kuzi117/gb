#ifndef GB_SIMULATOR_H
#define GB_SIMULATOR_H

#include "sim/RegisterInfo.h"

class Simulator {

private:
  //! The simulator's current program counter.
  uint16_t PC;

  //! The simulator's current stack pointer.
  uint16_t SP;

  //! The simulator's registers.
  uint16_t regs[4];

};

#endif // GB_SIMULATOR_H
