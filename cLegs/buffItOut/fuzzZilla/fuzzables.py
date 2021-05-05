class FuzzableException(Exception):
    pass


class Fuzzable:
    def __init__(self, targets=[]):
        self.targets = targets
        self.function_to_fuzz = None
        self.function_header = None
        self.function_args = None
        self.c_or_cpp = None

    def fuzz_function(self, func_name, func_head, func_args, target_type):
        self.function_to_fuzz = func_name
        self.function_header = func_head
        self.c_or_cpp = target_type

        if "Data" in func_args:
            self.function_args = func_args
        else:
            print(
                "[-] Your function must contain arg named 'Data', and optionally 'Size'"
            )
            print(f"{func_args}")
            raise FuzzableException

    def __repr__(self):
        return (
            self.function_header,
            self.function_to_fuzz,
            self.function_args,
            self.c_or_cpp,
        )
