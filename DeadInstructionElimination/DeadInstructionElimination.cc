#include <llvm/IR/Function.h>
#include <llvm/Pass.h>
#include <llvm/IR/Instruction.h>
#include <llvm/Analysis/TargetLibraryInfo.h>
#include <llvm/Transforms/Utils/Local.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/InstIterator.h>

// reference used : llvm/lib/Transforms/Scalar/DCE.cpp

namespace {
using namespace llvm;

struct DeadInstructionEliminationPass : public BasicBlockPass {
public:
    static char ID;

    DeadInstructionEliminationPass() : BasicBlockPass(ID) { }

    bool runOnBasicBlock(BasicBlock &bb) {
        bool changed = false;
        auto counter = 0;

        auto *analysis = 
            getAnalysisIfAvailable<TargetLibraryInfoWrapperPass>();

        TargetLibraryInfo *tli = analysis ? &analysis->getTLI() : nullptr;
        for (auto it = bb.begin(); it != bb.end(); ) {
            Instruction *instruction = &*it;

            // we do not want to point to the removed instruction
            it++;
            if (isInstructionTriviallyDead(instruction, tli)) {
                instruction->eraseFromParent();
                changed = true;
                counter++;
            }
        }

        errs() << counter << " instructions eliminated\n";

        return changed;
    }

    void getAnalysisUsage(AnalysisUsage &usage) const override {
        usage.setPreservesCFG();
    }
};

}

char DeadInstructionEliminationPass::ID;

RegisterPass<DeadInstructionEliminationPass> X("remove-dead",
                    "Removes dead instruction from IR",
                    false,
                    false);
