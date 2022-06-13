from re import *
from cs50 import get_string

text = get_string("Text: ")
i = round(0.0588 * (len(findall('[a-zA-Z]', text)) / (len(text.split()) / 100)) - 0.296 * (len(findall(r'[.!?]+', text)) / (len(text.split()) / 100)) - 15.8)
if i < 1:
    print("Before Grade 1")
elif i >= 16:
    print("Grade 16+")
else:
    print(f"Grade {i}")