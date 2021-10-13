from cs50 import get_int


def main():
    n = get_height()
    # this loop will create first stair pattern
    for i in range(1, n + 1, 1):
        print("", end=" " * (n - i))  # space befor #
        print("#" * i, end="")
        print("  ", end="")  # this space give space between two stair pattern
        print("#" * i, end="")  # this  will create second pattern

        print()


def get_height():
    while True:
        n = get_int("Enter the height: ")
        if (0 < n and n < 9):
            break
    return n


main()