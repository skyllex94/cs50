from cs50 import get_string
from math import ceil

letter_count, word_count, sentence_count = 0, 1, 0


def main():
    global letter_count, word_count, sentence_count
    try:
        text = get_string("Text: ")
    except:
        print("Incorrect Text!")
    for i in text:
        count_letters(i)
    average_letters = float((letter_count / word_count) * 100)
    # print(f"{average_letters}")
    average_words = float((sentence_count / word_count) * 100)
    # print(f"{average_words}")
    liau_formula = (0.0588 * average_letters) - (0.296 * average_words) - 15.8
    rounded = int(ceil(liau_formula))
    # print(letter_count)
    # print(word_count)
    # print(sentence_count)
    if (rounded < 1):
        print("Before Grade 1...")
    elif (rounded > 16):
        print("Grade 16+")
    else:
        print(f"Grade: {rounded}")


def count_letters(chr):
    global letter_count, word_count, sentence_count
    if (ord(chr.lower()) >= 97 and ord(chr.lower()) <= 121):
        letter_count += 1
    elif (ord(chr) == 32):
        word_count += 1
    elif (ord(chr) == 33 or ord(chr) == 63 or ord(chr) == 46):
        sentence_count += 1
    else:
        return 0


if __name__ == "__main__":
    main()
