#ifndef CALLFF_OPCODES_X86_64_HPP
#define CALLFF_OPCODES_X86_64_HPP

#define RAX 0
#define RCX 1
#define RDX 2
#define RBX 3
#define RSP 4
#define RBP 5
#define RSI 6
#define RDI 7

// REX.B == 1 in SIB or REX.R == 1 in ModR/M
#define R8  0
#define R9  1
#define R10 2
#define R11 3
#define R12 4
#define R13 5
#define R14 6
#define R15 7

#define XMM0 0
#define XMM1 1
#define XMM2 2
#define XMM3 3
#define XMM4 4
#define XMM5 5
#define XMM6 6
#define XMM7 7

#define XMM8 0  // REX.R == 1
#define XMM9 1
#define XMM10 2
#define XMM11 3
#define XMM12 4
#define XMM13 5
#define XMM14 6
#define XMM15 7


#define TWOBYTE_PREFIX 0x0F
#define FS_PREFIX 0x64 //FS segment override prefix

#define REX_W      0x48
#define REX_WR     0x4C
#define REX_B      0x41 // Extension of r/m field, base field, or opcode reg field
#define REX_WB     0x49 // W+B

#define MODRM_R10_R10 0x12

#define MODRM_MOD_MEM 0
#define MODRM_MOD_MEM16 1
#define MODRM_MOD_MEM32 2
#define MODRM_MOD_REG 3

#define MODRM_BASE(opcode) opcode
#define MODRM_DISP16(opcode) ((1 << 6) + opcode)
#define MODRM_DISP32(opcode) ((2 << 6) + opcode)
#define MODRM_REG(opcode) ((3 << 6) + opcode)
#define MODRM_DISP32_RIP 5 // RIP + displacement (disp32)


#define MODRM_BYTE(RMMode, opcode) ((unsigned char)(RMMode+(opcode<<3))) // opcode can be a register
#define SIB_BYTE(scale, reg, regBase) ((scale<<6)+(reg<<3)+regBase)


#define OP_MOV_TO_REG(reg) 0xB8+reg
#define OP_MOV_IMM_TO_REG 0xC7
#define OP_MOV_TO_DEST 0x89    // from op2 to op1
#define OP_MOV_FROM_DEST 0x8B // from op1 to op2
#define OP_NOP 0x90
#define OP_PUSH_RBP 0x55
#define OP_POP_RBP 0x5D
#define OP_CALL_SHORT 0xE8
#define OP_RETN 0xC2
#define OP_RETQ 0xC3
#define OP_LEAVE 0xC9
#define OP_PUSH_REG(reg) 0x50+reg
#define OP_POP_REG(reg) 0x58+reg
#define OP_CALL 0xFF
#define OP_IMM8_OPERATION 0x83  // r/m16/32/64
#define OP_IMM16_OPERATION 0x81 // r/m16/32/64
#define OP_IMM32_OPERATION 0x81 // r/m16/32/64

#define CALL_REG(reg) {OP_CALL, MODRM_BYTE(MODRM_REG(reg), 2)}
#define CALLFAR(addr16) {OP_CALL,  MODRM_BYTE(MODRM_BASE(addr16), 3)}

#define PUSHQ(imm){0xFF, MODRM_BYTE(MODRM_BASE(0), 6)}

#define MOVSD(reg0, reg1) {0xF2, TWOBYTE_PREFIX, 0x10, MODRM_BYTE(MODRM_BASE(reg0), reg1)}

#define MOVQ_MMX(xmmReg, reg) {0x66, REX_W, TWOBYTE_PREFIX, 0x6E, MODRM_BYTE(MODRM_REG(reg), xmmReg)}

#define ADD_IMM8_REG(val, reg) {REX_W, OP_IMM8_OPERATION, MODRM_BYTE(MODRM_REG(reg), 0), val}
#define SUB_IMM8_REG(val, reg) {REX_W, OP_IMM8_OPERATION, MODRM_BYTE(MODRM_REG(reg), 5), val}

#define SUB_VAL_RSP (val) {REX_W, OP_IMM8_OPERATION, MODRM_BYTE(MODRM_REG(RSP), 5), val}
#define MOV_RSP_RBP {REX_W, OP_MOV_TO_DEST, MODRM_BYTE(MODRM_REG(RBP), RSP)}


#define MOV_TO_STACK(reg, shift) {REX_W, OP_MOV_TO_DEST, MODRM_BYTE(MODRM_DISP16(RBP), reg), (unsigned char )shift}

#endif //CALLFF_OPCODES_X86_64_HPP
