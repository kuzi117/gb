#ifndef GB_INST_INFO_H
#define GB_INST_INFO_H

#include <cstdint>
#include <string>

#include "sim/RegisterInfo.h"

struct InstructionInfo {
  InstructionInfo(std::string mnemonic, uint8_t length, uint8_t cycles) noexcept
      : mnemonic(std::move(mnemonic)), length(length), cycles(cycles),
        longCycles(0) {}

  InstructionInfo(std::string mnemonic, uint8_t length, uint8_t cycles,
                  uint8_t longCycles) noexcept
      : mnemonic(std::move(mnemonic)), length(length), cycles(cycles),
        longCycles(longCycles) {}

  //! The instruction mnemonic.
  const std::string mnemonic;

  //! The instruction length in bytes.
  const uint8_t length;

  //! The instruction duration in cycles.
  const uint8_t cycles;

  /**
   * \brief The conditional duration in cycles.
   *
   * If this instruction is a conditional instruction this is the \e longer
   * instruction duration in cycles.
   *
   * For example 0x20 (JR NZ) on branch taken will use this length.
   */
  const uint8_t longCycles;
};

InstructionInfo instInfos[256] = {
    {"NOP", 1, 4},            // 0x00
    {"LD BC", 3, 12},         // 0x01
    {"LD (BC), A", 1, 8},     // 0x02
    {"INC BC", 1, 8},         // 0x03
    {"INC B", 1, 4},          // 0x04
    {"DEC B", 1, 4},          // 0x05
    {"LD B", 2, 8},           // 0x06
    {"RLCA", 1, 4},           // 0x07
    {"LD (a16), SP", 3, 20},  // 0x08
    {"ADD HL, BC", 1, 8},     // 0x09
    {"LD A, (BC)", 1, 8},     // 0x0A
    {"DEC BC", 1, 8},         // 0x0B
    {"INC C", 1, 4},          // 0x0C
    {"DEC C", 1, 4},          // 0x0D
    {"LD C", 2, 8},           // 0x0E
    {"RRCA", 1, 4},           // 0x0F
    {"STOP", 2, 4},           // 0x10
    {"LD DE", 3, 12},         // 0x11
    {"LD (DE), A", 1, 8},     // 0x12
    {"INC DE", 1, 8},         // 0x13
    {"INC D", 1, 4},          // 0x14
    {"DEC D", 1, 4},          // 0x15
    {"LD D", 2, 8},           // 0x16
    {"RLA", 1, 4},            // 0x17
    {"JR", 2, 12},            // 0x18
    {"ADD HL, DE", 1, 8},     // 0x19
    {"LD A, (DE)", 1, 8},     // 0x1A
    {"DEC DE", 1, 8},         // 0x1B
    {"INC E", 1, 4},          // 0x1C
    {"DEC E", 1, 4},          // 0x1D
    {"LD E", 2, 8},           // 0x1E
    {"RRA", 1, 4},            // 0x1F
    {"JR NZ", 2, 8, 12},      // 0x20
    {"LD HL", 3, 12},         // 0x21
    {"LD (HL+), A", 1, 8},    // 0x22
    {"INC HL", 1, 8},         // 0x23
    {"INC H", 1, 4},          // 0x24
    {"DEC H", 1, 4},          // 0x25
    {"LD H", 2, 8},           // 0x26
    {"DAA", 1, 4},            // 0x27
    {"JR Z", 2, 8, 12},       // 0x28
    {"ADD HL, HL", 1, 8},     // 0x29
    {"LD A, (HL+)", 1, 8},    // 0x2A
    {"DEC HL", 1, 8},         // 0x2B
    {"INC L", 1, 4},          // 0x2C
    {"DEC L", 1, 4},          // 0x2D
    {"LD L", 2, 8},           // 0x2E
    {"CPL", 1, 4},            // 0x2F
    {"JR NC", 2, 8, 12},      // 0x30
    {"LD SP", 3, 12},         // 0x31
    {"LD (HL-), A", 1, 8},    // 0x32
    {"INC SP", 1, 8},         // 0x33
    {"INC (HL)", 1, 12},      // 0x34
    {"DEC (HL)", 1, 12},      // 0x35
    {"LD (HL)", 2, 12},       // 0x36
    {"SCF", 1, 4},            // 0x37
    {"JR C", 2, 8, 12},       // 0x38
    {"ADD HL, SP", 1, 8},     // 0x39
    {"LD A, (HL-)", 1, 8},    // 0x3A
    {"DEC SP", 1, 8},         // 0x3B
    {"INC A", 1, 4},          // 0x3C
    {"DEC A", 1, 4},          // 0x3D
    {"LD A", 2, 8},           // 0x3E
    {"CCF", 1, 4},            // 0x3F
    {"LD B, B", 1, 4},        // 0x40
    {"LD B, C", 1, 4},        // 0x41
    {"LD B, D", 1, 4},        // 0x42
    {"LD B, E", 1, 4},        // 0x43
    {"LD B, H", 1, 4},        // 0x44
    {"LD B, L", 1, 4},        // 0x45
    {"LD B, (HL)", 1, 8},     // 0x46
    {"LD B, A", 1, 4},        // 0x47
    {"LD C, B", 1, 4},        // 0x48
    {"LD C, C", 1, 4},        // 0x49
    {"LD C, D", 1, 4},        // 0x4A
    {"LD C, E", 1, 4},        // 0x4B
    {"LD C, H", 1, 4},        // 0x4C
    {"LD C, L", 1, 4},        // 0x4D
    {"LD C, (HL)", 1, 8},     // 0x4E
    {"LD C, A", 1, 4},        // 0x4F
    {"LD D, B", 1, 4},        // 0x50
    {"LD D, C", 1, 4},        // 0x51
    {"LD D, D", 1, 4},        // 0x52
    {"LD D, E", 1, 4},        // 0x53
    {"LD D, H", 1, 4},        // 0x54
    {"LD D, L", 1, 4},        // 0x55
    {"LD D, (HL)", 1, 8},     // 0x56
    {"LD D, A", 1, 4},        // 0x57
    {"LD E, B", 1, 4},        // 0x58
    {"LD E, C", 1, 4},        // 0x59
    {"LD E, D", 1, 4},        // 0x5A
    {"LD E, E", 1, 4},        // 0x5B
    {"LD E, H", 1, 4},        // 0x5C
    {"LD E, L", 1, 4},        // 0x5D
    {"LD E, (HL)", 1, 8},     // 0x5E
    {"LD E, A", 1, 4},        // 0x5F
    {"LD H, B", 1, 4},        // 0x60
    {"LD H, C", 1, 4},        // 0x61
    {"LD H, D", 1, 4},        // 0x62
    {"LD H, E", 1, 4},        // 0x63
    {"LD H, H", 1, 4},        // 0x64
    {"LD H, L", 1, 4},        // 0x65
    {"LD H, (HL)", 1, 8},     // 0x66
    {"LD H, A", 1, 4},        // 0x67
    {"LD L, B", 1, 4},        // 0x68
    {"LD L, C", 1, 4},        // 0x69
    {"LD L, D", 1, 4},        // 0x6A
    {"LD L, E", 1, 4},        // 0x6B
    {"LD L, H", 1, 4},        // 0x6C
    {"LD L, L", 1, 4},        // 0x6D
    {"LD L, (HL)", 1, 8},     // 0x6E
    {"LD L, A", 1, 4},        // 0x6F
    {"LD (HL), B", 1, 4},     // 0x70
    {"LD (HL), C", 1, 4},     // 0x71
    {"LD (HL), D", 1, 4},     // 0x72
    {"LD (HL), E", 1, 4},     // 0x73
    {"LD (HL), H", 1, 4},     // 0x74
    {"LD (HL), L", 1, 4},     // 0x75
    {"LD (HL), (HL)", 1, 8},  // 0x76
    {"LD (HL), A", 1, 4},     // 0x77
    {"LD A, B", 1, 4},        // 0x78
    {"LD A, C", 1, 4},        // 0x79
    {"LD A, D", 1, 4},        // 0x7A
    {"LD A, E", 1, 4},        // 0x7B
    {"LD A, H", 1, 4},        // 0x7C
    {"LD A, L", 1, 4},        // 0x7D
    {"LD A, (HL)", 1, 8},     // 0x7E
    {"LD A, A", 1, 4},        // 0x7F
    {"ADD A, B", 1, 4},       // 0x80
    {"ADD A, C", 1, 4},       // 0x81
    {"ADD A, D", 1, 4},       // 0x82
    {"ADD A, E", 1, 4},       // 0x83
    {"ADD A, H", 1, 4},       // 0x84
    {"ADD A, L", 1, 4},       // 0x85
    {"ADD A, (HL)", 1, 8},    // 0x86
    {"ADD A, A", 1, 4},       // 0x87
    {"ADC A, B", 1, 4},       // 0x88
    {"ADC A, C", 1, 4},       // 0x89
    {"ADC A, D", 1, 4},       // 0x8A
    {"ADC A, E", 1, 4},       // 0x8B
    {"ADC A, H", 1, 4},       // 0x8C
    {"ADC A, L", 1, 4},       // 0x8D
    {"ADC A, (HL)", 1, 8},    // 0x8E
    {"ADC A, A", 1, 4},       // 0x8F
    {"SUB B", 1, 4},          // 0x90
    {"SUB C", 1, 4},          // 0x91
    {"SUB D", 1, 4},          // 0x92
    {"SUB E", 1, 4},          // 0x93
    {"SUB H", 1, 4},          // 0x94
    {"SUB L", 1, 4},          // 0x95
    {"SUB (HL)", 1, 8},       // 0x96
    {"SUB A", 1, 4},          // 0x97
    {"SBC A, B", 1, 4},       // 0x98
    {"SBC A, C", 1, 4},       // 0x99
    {"SBC A, D", 1, 4},       // 0x9A
    {"SBC A, E", 1, 4},       // 0x9B
    {"SBC A, H", 1, 4},       // 0x9C
    {"SBC A, L", 1, 4},       // 0x9D
    {"SBC A, (HL)", 1, 8},    // 0x9E
    {"SBC A, A", 1, 4},       // 0x9F
    {"AND B", 1, 4},          // 0xA0
    {"AND C", 1, 4},          // 0xA1
    {"AND D", 1, 4},          // 0xA2
    {"AND E", 1, 4},          // 0xA3
    {"AND H", 1, 4},          // 0xA4
    {"AND L", 1, 4},          // 0xA5
    {"AND (HL)", 1, 8},       // 0xA6
    {"AND A", 1, 4},          // 0xA7
    {"XOR B", 1, 4},          // 0xA8
    {"XOR C", 1, 4},          // 0xA9
    {"XOR D", 1, 4},          // 0xAA
    {"XOR E", 1, 4},          // 0xAB
    {"XOR H", 1, 4},          // 0xAC
    {"XOR L", 1, 4},          // 0xAD
    {"XOR (HL)", 1, 8},       // 0xAE
    {"XOR A", 1, 4},          // 0xAF
    {"OR B", 1, 4},           // 0xB0
    {"OR C", 1, 4},           // 0xB1
    {"OR D", 1, 4},           // 0xB2
    {"OR E", 1, 4},           // 0xB3
    {"OR H", 1, 4},           // 0xB4
    {"OR L", 1, 4},           // 0xB5
    {"OR (HL)", 1, 8},        // 0xB6
    {"OR A", 1, 4},           // 0xB7
    {"CP B", 1, 4},           // 0xB8
    {"CP C", 1, 4},           // 0xB9
    {"CP D", 1, 4},           // 0xBA
    {"CP E", 1, 4},           // 0xBB
    {"CP H", 1, 4},           // 0xBC
    {"CP L", 1, 4},           // 0xBD
    {"CP (HL)", 1, 8},        // 0xBE
    {"CP A", 1, 4},           // 0xBF
    {"RET NZ", 1, 8, 20},     // 0xC0
    {"POP BC", 1, 12},        // 0xC1
    {"JP NZ", 3, 12, 16},     // 0xC2
    {"JP", 3, 16},            // 0xC3
    {"CALL NZ", 3, 12, 24},   // 0xC4
    {"PUSH BC", 1, 16},       // 0xC5
    {"ADD A", 2, 8},          // 0xC6
    {"RST x00", 1, 16},       // 0xC7
    {"RET Z", 8, 20},         // 0xC8
    {"RET", 1, 16},           // 0xC9
    {"JP Z", 3, 12, 16},      // 0xCA
    {"PREFIX CB", 1, 4},      // 0xCB
    {"CALL Z", 3, 12, 24},    // 0XCC
    {"CALL", 3, 24},          // 0xCD
    {"ADC A", 2, 8},          // 0xCE
    {"RST x08", 1, 16},       // 0xCF
    {"RET NC", 1, 8, 20},     // 0xD0
    {"POP DE", 1, 12},        // 0xD1
    {"JP NC", 3, 12, 16},     // 0xD2
    {"UNUSED xD3", 255, 255}, // 0xD3
    {"CALL NC", 3, 12, 24},   // 0xD4
    {"PUSH DE", 1, 16},       // 0xD5
    {"SUB", 2, 8},            // 0xD6
    {"RST x10", 1, 16},       // 0xD7
    {"RET C", 8, 20},         // 0xD8
    {"RETI", 1, 16},          // 0xD9
    {"JP C", 3, 12, 16},      // 0xDA
    {"UNUSED xDB", 255, 255}, // 0xDB
    {"CALL C", 12, 24},       // 0xDC
    {"UNUSED xDD", 255, 255}, // 0xDD
    {"SBC A", 2, 8},          // 0xDE
    {"RST x18", 1, 16},       // 0xDF
    {"LDH (a8), A", 2, 12},   // 0xE0
    {"POP HL", 1, 12},        // 0xE1
    {"LD (C), A", 2, 8},      // 0xE2
    {"UNUSED xE3", 255, 255}, // 0xE3
    {"UNUSED xE4", 255, 255}, // 0xE4
    {"PUSH HL", 1, 16},       // 0xE5
    {"AND", 2, 8},            // 0xE6
    {"RST x20", 1, 16},       // 0xE7
    {"ADD SP", 2, 16},        // 0xE8
    {"JP (HL)", 1, 4},        // 0xE9
    {"LD (a16), A", 3, 16},   // 0xEA
    {"UNUSED xEB", 255, 255}, // 0xEB
    {"UNUSED xEC", 255, 255}, // 0xEC
    {"UNUSED xED", 255, 255}, // 0xED
    {"XOR", 2, 8},            // 0xEE
    {"RST x28", 1, 16},       // 0xEF
    {"LDH A", 2, 12},         // 0xF0
    {"POP AF", 1, 12},        // 0xF1
    {"LD A, (C)", 2, 8},      // 0xF2
    {"DI", 1, 4},             // 0xF3
    {"UNUSED xF4", 255, 255}, // 0xF4
    {"PUSH AF", 1, 16},       // 0xF5
    {"OR", 2, 8},             // 0xF6
    {"RST x30", 1, 16},       // 0xF7
    {"LD HL, SP+r8", 2, 12},  // 0xF8
    {"LD SP, HL", 1, 8},      // 0xF9
    {"LD A", 3, 16},          // 0xFA
    {"EI", 1, 4},             // 0xFB
    {"UNUSED xFC", 255, 255}, // 0xFC
    {"UNUSED xFD", 255, 255}, // 0xFD
    {"CP", 2, 8},             // 0xFE
    {"RST x38", 1, 16},       // 0xFF
};

#endif // GB_INST_INFO_H
