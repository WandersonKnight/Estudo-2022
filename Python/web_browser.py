#! python3

import webbrowser
import sys

if len(sys.argv) < 2:
    raise ValueError("Invalid Input, adress argument missing")
   
address = " ".join(sys.argv[1:])

webbrowser.open(f'https://www.google.com.br/maps/place/{address}')