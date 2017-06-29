#ifdef __x86_64__

#include "callgen.hpp"
#include "opcodes_x86_64.hpp"
#include "utils.hpp"

using namespace std;

// http://chamilo2.grenet.fr/inp/courses/ENSIMAG3MM1LDB/document/doc_abi_ia64.pdf
size_t GenerateCode(Func &fCpp, CallArgs &data, unsigned char *code) noexcept
{
    const int align = 8;
    size_t codeOffset = 0;

    unsigned char stack;
    auto movToStack = [&codeOffset, &code, &stack](uint64_t value)
    { // faster than regular pushq
        codeOffset += utils::braceToString({REX_W, OP_MOV_TO_REG(RAX)}, &code[codeOffset]);
        utils::Value64ToString(value, code, codeOffset);
        stack -= 8;
        codeOffset += utils::braceToString(MOV_TO_STACK(RAX, stack), &code[codeOffset]);

    };

    code[codeOffset++] = OP_PUSH_REG(RBP);
    codeOffset += utils::braceToString(MOV_RSP_RBP, &code[codeOffset]);

    int stackSize = 0;
    int floatValues = 0;
    int regularValues = 0;

    { // calculate stack
        for (auto v : data)
        {
            if (v.first == 'f')
                floatValues++;
            else
                regularValues++;
        }
        if (regularValues > 6)
            stackSize += regularValues - 6;
        if (floatValues > 16)
            stackSize += floatValues - 16;
    }

    if (stackSize > 0) // allocate stack
    {
        if (stackSize % 2) // align stack
        {
            stack -= 8;
            stackSize += 1;
        }
        codeOffset += utils::braceToString(SUB_IMM8_REG((unsigned char) (stackSize * align), RSP), &code[codeOffset]);

        for (size_t i = data.size() - 1; i >= 6; --i)
        {
            if (data[i].first != 'f' || floatValues > 16)
                movToStack(data[i].second);
        }
    }

    int argn = 0;
    int argfn = 0;
    for (auto v : data)
    {
        if (v.first != 'f' && argn < 6) // pointers and regular arguments
        {
            switch (argn)
            {
                case 0:
                    // copy data from stack to RDI register
                    codeOffset += utils::braceToString({REX_W, OP_MOV_TO_REG(RDI)}, &code[codeOffset]);
                    break;
                case 1:
                    codeOffset += utils::braceToString({REX_W, OP_MOV_TO_REG(RSI)}, &code[codeOffset]);
                    break;
                case 2:
                    codeOffset += utils::braceToString({REX_W, OP_MOV_TO_REG(RDX)}, &code[codeOffset]);
                    break;
                case 3:
                    codeOffset += utils::braceToString({REX_W, OP_MOV_TO_REG(RCX)}, &code[codeOffset]);
                    break;
                case 4:
                    codeOffset += utils::braceToString({REX_WB, OP_MOV_TO_REG(R8)}, &code[codeOffset]);
                    break;
                case 5:
                    codeOffset += utils::braceToString({REX_WB, OP_MOV_TO_REG(R9)}, &code[codeOffset]);
                    break;
                default:
                    break;
            }
            utils::Value64ToString(v.second, code, codeOffset);
            argn++;
        }
        else if (v.first == 'f' && argfn < 16) // regular float arguments to XMM0-XMM15
        {
            codeOffset += utils::braceToString({REX_W, OP_MOV_TO_REG(RAX)}, &code[codeOffset]);
            utils::Value64ToString(v.second, code, codeOffset);
            codeOffset += utils::braceToString(MOVQ_MMX(argfn, RAX), &code[codeOffset]); // argfn is XMM0-XMM15
            argfn++;
        }
    }

    //movabs fCpp, %r10
    codeOffset += utils::braceToString({REX_WB, OP_MOV_TO_REG(R10)}, &code[codeOffset]);
    utils::Value64ToString((uintptr_t) fCpp, code, codeOffset);
    // call *%r10
    code[codeOffset++] = REX_B;
    codeOffset += utils::braceToString(CALL_REG(R10), &code[codeOffset]);

    if (stackSize > 0) // deallocate stack
        codeOffset += utils::braceToString(ADD_IMM8_REG((unsigned char) (stackSize * align), RSP), &code[codeOffset]);

    code[codeOffset++] = OP_LEAVE; // pop rbp; mov rbp, rsp
    code[codeOffset++] = OP_RETQ;
    while (codeOffset % align)
        code[codeOffset++] = OP_NOP;

    return codeOffset + 1;
}

#endif // __x86_64__
