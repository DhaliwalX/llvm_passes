#define DEBUG_TYPE "counter"
#include <llvm/Pass.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/ADT/Statistic.h>

using namespace llvm;

STATISTIC(counter, "Number of instructions");

namespace {
// simple pass that counts the number of instructions in the IR
// use -stats option to print the number
struct CountInstructionsPass : public BasicBlockPass {
    static char ID;

    CountInstructionsPass() : BasicBlockPass(ID) { }

    bool runOnBasicBlock(BasicBlock &bb) override {
        for (const auto &i : bb) {
            counter++;
        }
        return false;
    }
};

char CountInstructionsPass::ID = 0;

}

RegisterPass<CountInstructionsPass> X("count_instructions",
                                    "Counts the number of instructions",
                                    false,
                                    false);

