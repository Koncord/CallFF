#ifndef CALLFF_OPCODES_X86_HPP
#define CALLFF_OPCODES_X86_HPP

#define EAX 0
#define ECX 1
#define EDX 2
#define EBX 3
#define ESP 4
#define EBP 5
#define ESI 6
#define EDI 7

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

#define OP_PUSH_DS 0x1E
#define OP_POP_ES 0x07
#define OP_CLD 0xFC
#define OP_REP 0xF3
#define OP_MOVSB 0xA4
#define OP_MOV_TO_REG(reg) 0xB8+reg
#define OP_MOV_IMM_TO_REG 0xC7
#define OP_MOV_TO_DEST 0x89    // from op2 to op1
#define OP_MOV_FROM_DEST 0x8B // from op1 to op2
#define OP_NOP 0x90
#define OP_CALL_SHORT 0xE8
#define OP_RETN 0xC3
#define OP_LEAVE 0xC9
#define OP_PUSH_REG(reg) 0x50+reg
#define OP_POP_REG(reg) 0x58+reg
#define OP_CALL 0xFF
#define OP_IMM8_OPERATION 0x83  // r/m16/32
#define OP_IMM16_OPERATION 0x81 // r/m16/32
#define OP_IMM32_OPERATION 0x81 // r/m16/32

#define OP_MOV_FROM_EAX 0xA3

#define PUSH(reg)0x50+reg
#define POP(reg)0x58+reg
#define CALL_REG(reg) {OP_CALL, MODRM_BYTE(MODRM_REG(reg), 2)}

#endif //CALLFF_OPCODES_X86_HPP
