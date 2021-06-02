

## Welcome to all things fuzzy

C/C++ binary fuzzing orchestrator. Run AFL and LibFuzzer(and others) all under one roof. All fuzzers want things compiled or instrumented a little differently so do what is necessary to make these things run together, discover crashes, verify, determine exploitablity and general severity of a crash. 



## Primary components
- Fuzzables - object describing what is to be fuzzed, targets, depends, etc
- Processors - the thing doing the fuzzing. what is necessary for the fuzzer to compile(), execute(), verify()




## Narrative
1) Generate adapters
    - llvmFuzzerTestOneInput with functions we want to test
    - afl-fuzzer main shim to read stdin
    - afl-fuzzer ./inputs/in files
2) Startup, run against control, verify crash
    - compile list of inputs for both afl and libfuzz
    - parse crash report for each processor.
        - needs standard format, use to replicate crash.
    - processor.compile, processor.execute, processor.verify.
5) Run afl-fuzz and libFuzzer in conjunction
    - multiprocess.process/pool
6) Compile with normal gcc, verify crash with result as input
7) Drop into gdb, perform exploitable check
8) More to come
