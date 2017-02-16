#include <llvm/IR/Instruction.h>
#include <llvm/Pass.h>
#include <llvm/IR/Function.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

namespace {

// A simple hello world pass that prints hello: <name of function>
struct HelloWorldPass : FunctionPass {
    static char ID;

    HelloWorldPass() : FunctionPass(ID)
    { }

    bool runOnFunction(Function &function) override {
        errs() << "Hello: " << function.getName() << "\n";
    }
};

}
