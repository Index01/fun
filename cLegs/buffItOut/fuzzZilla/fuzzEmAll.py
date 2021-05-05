import fuzzProcessor
import fuzzables


def main():

    afl_fuzzable = fuzzables.Fuzzable(["fuzzControlCase.c", "main.c"])
    llvm_fuzzable = fuzzables.Fuzzable(["fuzzControlCase.c"])

    llvm_fuzzable.fuzz_function(
        "iOverflowAndAllocate", "fuzzControlCase", "(char*)Data, Size", "c"
    )

    afl_processor = fuzzProcessor.AFLProcessor(afl_fuzzable)
    llvm_processor = fuzzProcessor.LLVMProcessor(llvm_fuzzable)

    llvm_processor.run()


if __name__ == "__main__":
    main()
