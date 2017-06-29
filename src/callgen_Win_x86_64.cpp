#if defined (__x86_64__) || defined(_M_X64)

#include "callgen.hpp"
#include "opcodes_x86_64.hpp"
#include "utils.hpp"

using namespace std;

size_t GenerateCode(Func &fCpp, CallArgs &data, unsigned char *code) noexcept
{
    const int align = 8;
    size_t codeOffset = 0;

    unsigned char stack;
    auto movToStack = [&codeOffset, &code, &stack](int64_t value)
    { // faster than regular pushq
        codeOffset += utils::braceToString({REX_W, OP_MOV_TO_REG(RAX)}, &code[codeOffset]);
        utils::Value64ToString(value, code, codeOffset);
        stack -= 8;
        codeOffset += utils::braceToString(MOV_TO_STACK(RAX, stack), &code[codeOffset]);

    };

    // todo: https://msdn.microsoft.com/en-us/library/tawsa7cb.aspx
    /*code[codeOffset++] = OP_PUSH_REG(RBP);
    codeOffset += utils::braceToString(MOV_RSP_RBP, &code[codeOffset]);*/

    int stackSize = 0;

    if(stackSize > 0) // allocate stack
    {
        stack -= 32; // Shadow space
        stackSize += 4;

        if(stackSize % 2) // align stack
        {
            stack -= 8;
            stackSize += 1;
        }
        //codeOffset += utils::braceToString(SUB_IMM8_REG((unsigned char) (shadow + (stackSize * align)), RSP), &code[codeOffset]);

        /*for (size_t i = data.size() - 1; i >= 4; --i)
        {
            if (data[i].first != 'f' || (data[i].first == 'f' && stackFloats > 0))
                movToStack(data[i].second);
        }*/
    }

    int argn = 0;
    for(const auto &v : data)
    {
        if(argn < 4)
        {
            if (v.first != 'f') // pointers and regular arguments
            {
                switch (argn)
                {
                    case 0:
                        // copy data from stack to RDI register
                        codeOffset += utils::braceToString({REX_W, OP_MOV_TO_REG(RCX)}, &code[codeOffset]);
                        break;
                    case 1:
                        // rdx
                        codeOffset += utils::braceToString({REX_W, OP_MOV_TO_REG(RDX)}, &code[codeOffset]);
                        break;
                    case 2:
                        // r8
                        codeOffset += utils::braceToString({REX_WB, OP_MOV_TO_REG(R8)}, &code[codeOffset]);
                        break;
                    case 3:
                        // r9
                        codeOffset += utils::braceToString({REX_WB, OP_MOV_TO_REG(R9)}, &code[codeOffset]);
                        break;
                    default:
                        break;
                }
                utils::Value64ToString(v.second, code, codeOffset);
                argn++;
            }
            else if (v.first == 'f')
            {
                codeOffset += utils::braceToString({REX_W, OP_MOV_TO_REG(RAX)}, &code[codeOffset]);
                utils::Value64ToString(v.second, code, codeOffset);
                codeOffset += utils::braceToString(MOVQ_MMX(argn, RAX), &code[codeOffset]); // argn is XMM0-XMM3
            }
        }
        else
            break;
    }


    //movabs fCpp, %r10
    codeOffset += utils::braceToString({REX_WB, OP_MOV_TO_REG(R10)}, &code[codeOffset]);
    utils::Value64ToString((uintptr_t) fCpp, code, codeOffset);
    // call *%r10
    code[codeOffset++] = REX_B;
    codeOffset += utils::braceToString(CALL_REG(R10), &code[codeOffset]);

    //todo: https://msdn.microsoft.com/en-us/library/tawsa7cb.aspx
    /*if (stackSize > 0) // deallocate stack
        codeOffset += utils::braceToString(ADD_IMM8_REG((unsigned char)(stackSize*align), RSP), &code[codeOffset]);

    code[codeOffset++] = OP_LEAVE; // pop rbp; mov rbp, rsp*/
    code[codeOffset++] = OP_RETQ;
    while (codeOffset % align)
        code[codeOffset++] = OP_NOP;

    return codeOffset + 1;
}

#endif // __x86_64__ || _M_X64