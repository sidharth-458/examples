import subprocess
import sys
import os
import pytest

# Path to the calculator executable
elf = os.path.join(os.path.dirname(__file__), "calc")

def run_calc(input_data: str) -> str:
    """Run the calculator program with given stdin and return its stdout."""
    # On Windows, the executable might be calculator.exe
    result = subprocess.run(
        [elf],
        input=input_data.encode(),
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        check=False,
    )
    # Combine stdout and stderr if you want to see error messages too
    output = result.stdout.decode()
    return output

@pytest.mark.parametrize(
    "op, a, b, expected_part",
    [
        ("+", 4, 5, "Result: 9.00"),
        ("-", 10, 3, "Result: 7.00"),
        ("*", 2, 6, "Result: 12.00"),
        ("/", 8, 2, "Result: 4.00"),
    ],
)
def test_basic_operations(op, a, b, expected_part):
    user_input = f"{op}\n{a} {b}\n"
    output = run_calc(user_input)
    assert expected_part in output

def test_division_by_zero():
    user_input = "/\n5 0\n"
    output = run_calc(user_input)
    assert "Division by zero" in output

def test_modulus_operation():
    # modulus prints integer result (as per your C program)
    user_input = "%\n10 3\n"
    output = run_calc(user_input)
    assert "Result: 1" in output

def test_invalid_operator():
    user_input = "x\n4 5\n"
    output = run_calc(user_input)
    assert "Invalid operator" in output

