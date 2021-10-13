from cs50 import get_int


def main():
    card_num = get_int("Enter card number: ")
    N = num_of_digits(card_num)  # Total number of digits in card number.
    starting_dig = card_num // (10 ** (N - 2))  # starting two digits
    # adding both sum.
    SUM = product_sum(card_num, N) + sum_of_other_digit(card_num, N)

    # Condition for checksum.
    if ((SUM % 10) == 0):
        # condition for american express card.
        if ((starting_dig == 34 or starting_dig == 37) and N == 15):
            print("AMEX")

        # condtion for Mastercard
        elif (starting_dig in range(51, 56) and N == 16):
            print("MASTERCARD")

        # condition for visa
        elif ((starting_dig // 10) == 4 and (N == 13 or N == 16)):
            print("VISA")

        else:
            print("INVALID")

    else:
        print("INVALID")


# this function will calculate the nummber of digits in the card.
def num_of_digits(num):
    return len(str(num))

# This function will multiply every other digits by 2,
# starting with number's second-to-last digits, add those product's digit togather


def product_sum(num, N):
    s = str(num)
    SUM = 0
    for i in range(N - 2, -1, -2):
        digit = 2 * int(s[i])
        SUM += ((digit // 10) + digit % 10)

    return SUM


# this function will give, sum of digits that are not multipliy by 2
def sum_of_other_digit(num, N):
    s = str(num)
    SUM = 0
    for j in range(N - 1, -1, - 2):
        SUM += int(s[j])

    return SUM


# Calling main function
main()

