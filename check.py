import sys


def check(a, b):
    
    print("Q: " + hex(a // b))
    print("R: " + hex(a % b))


if __name__ == '__main__':
    
    a = int(input(), 16)
    b = int(input(), 16)

    check(a, b)
