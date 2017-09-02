// cdecl convention

#if defined(__i386__) || defined(__i686__) || defined(_M_IX86)

#include "callgen.hpp"
#include "opcodes_x86.hpp"
#include "utils.hpp"

using namespace std;

size_t GenerateCode(Func &fCpp, CallArgs &data, unsigned char *code) noexcept
{
    vector<uintptr_t> newSource;
    for(auto &&d : data)
        newSource.push_back(d.second);

    uintptr_t source = reinterpret_cast<uintptr_t>(&newSource[0]);
    uintptr_t size = data.size() * 4;

    size_t codeOffset = 0;

    code[codeOffset++] = PUSH(EBP);
    code[codeOffset++] = PUSH(EDI);
    code[codeOffset++] = PUSH(ESI);


    codeOffset += utils::braceToCString({OP_MOV_TO_DEST, MODRM_BYTE(MODRM_REG(EBP), ESP)}, &code[codeOffset]);

    codeOffset += utils::braceToCString({OP_MOV_TO_DEST, MODRM_BYTE(MODRM_REG(EDI), ESP)}, &code[codeOffset]);

    codeOffset += utils::braceToCString({OP_IMM32_OPERATION, MODRM_BYTE(MODRM_REG(EDI), 5)}, &code[codeOffset]); //alloc on stack
    utils::Value32ToString(size, code, codeOffset);

    codeOffset += utils::braceToCString({OP_MOV_TO_REG(ESI)}, &code[codeOffset]); // move ptr of source to ESI.
    utils::Value32ToString(source, code, codeOffset);

    codeOffset += utils::braceToCString({OP_MOV_TO_REG(ECX)}, &code[codeOffset]); // length of data.
    utils::Value32ToString(size, code, codeOffset);

    code[codeOffset++] = OP_PUSH_DS; // move DS
    code[codeOffset++] = OP_POP_ES; // to ES.

    code[codeOffset++] = OP_CLD; // clear direction flag.

    codeOffset += utils::braceToCString({OP_REP, OP_MOVSB}, &code[codeOffset]); // Move bytes at address DS:ESI to address ES:EDI (move to stack).

    codeOffset += utils::braceToCString({OP_MOV_TO_DEST, MODRM_BYTE(MODRM_REG(ESI), ESP)}, &code[codeOffset]); // stack pointer.

    codeOffset += utils::braceToCString({OP_IMM32_OPERATION, MODRM_BYTE(MODRM_REG(ESP), 5)}, &code[codeOffset]);
    utils::Value32ToString(size, code, codeOffset);

    //mov fCpp, %eax
    codeOffset += utils::braceToCString({OP_MOV_TO_REG(EAX)}, &code[codeOffset]);
    utils::Value32ToString((uintptr_t) fCpp, code, codeOffset);
    // call *%eax
    codeOffset += utils::braceToCString(CALL_REG(EAX), &code[codeOffset]);

    codeOffset += utils::braceToCString({OP_MOV_TO_DEST, MODRM_BYTE(MODRM_REG(ESP), EDI)}, &code[codeOffset]);


    code[codeOffset++] = POP(ESI);
    code[codeOffset++] = POP(EDI);
    code[codeOffset++] = POP(EBP);
    code[codeOffset++] = OP_RETN;

    return codeOffset + 1;
}

#endif