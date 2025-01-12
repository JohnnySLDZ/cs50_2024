import string
import re

def main():
    text = input("Text: ")
    words = len(get_words(text))
    L = average(get_letters(text), words)
    S = average(get_sentences(text), words)
    level = round(0.0588 * L - 0.296 * S - 15.8)
    if level < 1:
        print("Before Grade 1")
    elif level > 16:
        print("Grade 16+")
    else:
        print(f"Grade {level}")


def get_letters(text):
    letters = 0
    words = get_words(text)
    for i in words:
        translation_table = str.maketrans('', '', string.punctuation)
        result = i.translate(translation_table)
        letters += len(result)
    return letters


def get_sentences(text):
    dots = text.count(".")
    exclamations = text.count("!")
    interrogations = text.count("?")
    sentences = dots + exclamations + interrogations
    return sentences


def get_words(text):
    words = text.split()
    for i in range(len(words)):
        words[i] = words[i].strip(string.punctuation)
    return words

def average(numbers, words):
    x = (100 * numbers)/words
    return x

main()

