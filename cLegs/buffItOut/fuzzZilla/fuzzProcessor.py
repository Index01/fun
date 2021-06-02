import subprocess
import os
import glob


class Processor:
    def __init__(self, fuzzable):
        self.fuzzable = fuzzable

    def compile(self):
        pass

    def execute(self):
        pass

    def verify(self):
        pass

    def run(self):
        self.compile()
        if self.compiled:
            print("[+] Compiled")
            self.execute()
            if self.executed:
                print("[+] Executed")
                self.verify()
                if self.verified:
                    print("[+] Veriried crash")


class LLVMProcessor(Processor):
    def __init__(self, fuzzable):
        self.fuzzable = fuzzable
        self.compiled = False
        self.executed = False
        self.verified = False

    def autogen_llvm_shim(self):
        """Ugh, never seen autogen code that I liked"""
        c_fstr = (
            f"""#include <stdint.h>\n""",
            f"""#include \"{self.fuzzable.function_header}.h\"\n""",
            f"""int LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size){{\n""",
            f"""    {self.fuzzable.function_to_fuzz}({self.fuzzable.function_args});\n""",
            f"""}}""",
        )
        with open(f"llvm_shim.{self.fuzzable.c_or_cpp}", "w") as genc:
            genc.write("".join(c_fstr))

    def compile(self):
        if not glob.glob("llvm_shim.c"):
            self.autogen_llvm_shim()

        san_opts = "fuzzer"
        comp_str = f"clang -g -fsanitize={san_opts} ./llvm_shim.c {' '.join(self.fuzzable.targets)}"
        completed = subprocess.run(comp_str.split(" "))

        if completed.returncode == 0:
            self.compiled = True

    def execute(self):
        subprocess.run(f"rm {' '.join(glob.glob('crash*'))}".split(" "))
        try:
            subprocess.run(["./a.out"], check=True)
        except subprocess.CalledProcessError as e:
            pass

        if glob.glob("crash*"):
            self.executed = True

    def verify(self):
        subprocess.run(
            f"gcc {' '.join(self.fuzzable.targets)} ./llvm_shim.c ./main.c".split(" ")
        )
        lout = []
        with open(" ".join(glob.glob("crash*")), "rb") as file:
            while True:
                abyte = file.read(1)
                if abyte:
                    try:
                        lout.append(abyte.decode())
                    except UnicodeDecodeError as e:
                        pass
                else:
                    break

        bits = "".join(lout)
        try:
            subprocess.run(
                f"./a.out -i {repr(bits[:-2])}".split(" "), timeout=5, check=True
            )
        except subprocess.CalledProcessError as e:
            self.verified = True
        except subprocess.TimeoutExpired as e:
            print("[-] Failed to reproduce the crash. Please review crash file")


class AFLProcessor(Processor):
    def __init__(self, fuzzable):
        self.fuzzable = fuzzable

    def compile(self):
        compiler = "afl-gcc-fast"
        comp_str = f"{compiler} ./main.c {' '.join(self.fuzzable.targets)}"
        completed = subprocess.run(comp_str.split(" "))

        if completed.returncode == 0:
            self.compiled = True
