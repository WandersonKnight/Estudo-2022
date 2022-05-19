#! python3

import re

open_file = open("regex/text_file.txt")
text = open_file.read()

four_word_regex = re.compile(r"\b[^\s\d]{4}\b")
print(four_word_regex.findall(text))