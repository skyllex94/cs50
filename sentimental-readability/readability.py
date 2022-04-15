from cs50 import get_string

letter_count, word_count, sentence_count = 0, 1, 0


def main():
    # Adjust the global amounts to keep track
    global letter_count, word_count, sentence_count
    try:
        text = get_string("Enter Text: ")
    except:
        print("Incorrect Text!")
    # Go through each letter and identify what it is
    for i in text:
        count_letters(i)
    average_letters = float((letter_count / word_count) * 100)
    average_words = float((sentence_count / word_count) * 100)
    # Calculate the grade based on the formula and store it in a float
    liau_formula = (0.0588 * average_letters) - (0.296 * average_words) - 15.8
    rounded = round(liau_formula)
    # print(letter_count)
    # print(word_count)
    # print(sentence_count)
    if (rounded < 1):
        print("Before Grade 1...")
    elif (rounded > 16):
        print("Grade 16+")
    else:
        print(f"Grade: {rounded}")


# Function that takes the currect letter and updates the count
def count_letters(chr):
    global letter_count, word_count, sentence_count
    if (chr.isalpha()):
        letter_count += 1
    elif (chr.isspace()):
        word_count += 1
    elif (ord(chr) == 33 or ord(chr) == 63 or ord(chr) == 46):
        sentence_count += 1
    else:
        return


if __name__ == "__main__":
    main()
