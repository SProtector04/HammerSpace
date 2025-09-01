def sum():
    return a + b

def sutr():
    return a - b

def prod():
    return a * b

def div():
    if b != 0:
        return a / b
    else:
        return "Division by zero is not allowed"

def input_numbers():
    global a, b
    a = float(input("Enter first number: "))
    b = float(input("Enter second number: "))
    while a == "" or b == "":
        print("Please enter valid numbers.")
        continue

def output_numbers():
    print(f"The sum is: {sum()}")
    print(f"The sustraction is: {sutr()}")  
    print(f"The product is: {prod()}")
    print(f"The divition is: {div()}")    
    
input_numbers()
output_numbers()
