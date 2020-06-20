#ifndef GB_REGISTER_INFO_H
#define GB_REGISTER_INFO_H

#include <cstdint>

//! Flag register bit masks.
enum Flags : uint8_t {
  UNUSED = 0x07, //< Unused and always zero.
  C = 0x10, //< The carry flag.
  H = 0x20, //< The half carry flag.
  N = 0x40, //< The subtract flag.
  Z = 0x80 //< The zero flag.
};

//! Register information for the 8-bit registers.
struct Register8Info {
  //! No default constructor.
  constexpr Register8Info() = delete;

  //! Construct with register info.
  constexpr Register8Info(const uint8_t regNum, const uint8_t position) noexcept: regNum(regNum),
                                                                                  position(
                                                                                      position) { }

  //! Which 16-bit register this is part of. Valid values are 0-3.
  const uint8_t regNum;

  //! Which position in the full 16-bit register this is. Valid values are 0-1.
  const uint8_t position;
};

//! Indices into ::R8Infos.
enum struct R8Indices : uint8_t {
  A = 0, F = 1, B = 2, C = 3, D = 4, E = 5, H = 6, L = 7
};

//! The 8-bit register information.
constexpr Register8Info R8Infos[8] = {
    {0, 1}, // Register A.
    {0, 0}, // Register F.
    {1, 1}, // Register B.
    {1, 0}, // Register C.
    {2, 1}, // Register D.
    {2, 0}, // Register E.
    {3, 1}, // Register J.
    {2, 0}, // Register L.
};

//! Register info for the 16 bit registers.
struct Register16Info {
  //! No default constructor.
  constexpr Register16Info() = delete;

  //! Construct with register info.
  constexpr explicit Register16Info(const uint8_t regNum) noexcept: regNum(regNum) { }

  //! Which 16-bit register this is. Valid values are 0-3.
  const uint8_t regNum;
};

//! Indices into ::R16Infos.
enum struct R16Indices : uint8_t {
  AF = 0, BC = 1, DE = 2, HL = 3
};

//! The 16-bit register information.
constexpr Register16Info R16Infos[4] = {
    Register16Info(0),
    Register16Info(1),
    Register16Info(2),
    Register16Info(3)
};

#endif // GB_REGISTER_INFO_H
