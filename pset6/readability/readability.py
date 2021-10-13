from cs50 import get_string


def main():
    text = get_string("Text: ")
    L = num_letters(text) * 100 / num_words(text)  # Average number of letters per 100 words.
    S = num_sentences(text) * 100 / num_words(text)  # Average number of sentences per 100 words
    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index < 1:
        print("Before Grade 1")

    elif (1 <= index and index <= 16):
        print("Grade ", index)

    elif index > 16:
        print("Grade 16+")


# this function will return number of letters in the text.
def num_letters(text):
    n = len(text)
    letters = 0
    for i in range(n):
        if text[i].isalpha():
            letters += 1
    return letters


# function will calculate number of words in the text.
def num_words(text):
    return len(text.split(" "))


# function will find number of sentences in the text
def num_sentences(text):
    count = 0
    for i in range(len(text)):
        if text[i] in ['!', '?', '.']:
            count += 1
    return count


# calling main function
main()

