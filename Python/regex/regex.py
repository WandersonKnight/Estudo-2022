#! python3

import re

test_file = open("regex/text_file.txt")
text = test_file.read()
test_file.close()

four_letters_regex = re.compile(r"\b[^\s\d]{4}\b")
print(four_letters_regex.findall(text))

print(four_letters_regex.sub("REDACTED", text))