#! python3

import sys
from pymath import Math

try:
    math_operation = int(sys.argv[1])
    first_value = sys.argv[2]
    second_value = sys.argv[3]
except:
    print("""Invalid arguments. Arguments: 1 -> Operation, 2 -> 1st value, 3 -> 2nd value.
            Operations: 0 -> Multiplication, 1 -> Addition, 2 -> Subtraction, 3 -> Exponentiation""")

if math_operation == 0:
    result = Math.Multiply(first_value, second_value)
elif math_operation == 1:
    result = Math.Add(first_value, second_value)
elif math_operation == 2:
    result = Math.Subtract(first_value, second_value)
elif math_operation == 3:
    result = Math.Power(first_value, second_value)

print(result)
