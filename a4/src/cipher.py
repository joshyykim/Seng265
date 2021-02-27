"""
In this file, you need to add your FileDecoder class
See a4 PDF for details

WE WILL EVALUATE YOUR CLASS INDIVIDUAL, SO MAKE SURE YOU READ
THE SPECIFICATIONS CAREFULLY.
"""

import re
import string


class FileDecoder:
    def __init__(self, filename, key, alphabet):
        self.filename = filename
        self.key = key
        self.alphabet = alphabet
        self.decoded = ""
        self.length = 0
        index = 0
        key_index = 0
        
        text = open(self.filename, "r")
        encrypted = text.read()
        while True:
            try:                            # keep loop until reach EOF
                temp = alphabet.index(encrypted[index])
            except:
                break
            try:
                temp -= alphabet.index(key[key_index])
            except:
                key_index = 0               # when reached end of key, reset to first character of key
                temp -= alphabet.index(key[key_index])
            self.decoded += alphabet[temp]
            index += 1
            key_index += 1
        text.close()
        self.decoded = self.decoded.split('\n')     # store decpryted text into list line by line
        # count of first line of file
        count = 0
        # each line of text split by commas(,)
        for word in self.decoded[0]:
            if word == ',':
                count += 1
        if count != 17:
            # first line of successfully decrypted file has 18 elements, since it has 17 commas(,)
            raise DecryptException("Entered key is invaild to decode")
        while self.decoded[self.length]:
            self.decoded[self.length] = self.decoded[self.length].split(',')
            self.length += 1
 
    def __iter__(self):
        index = 0
        while self.decoded[index]:
            yield self.decoded[index]
            index += 1

    def __str__(self):
        return 'FileDecoder: FileDecoder(key=\'{self.key}\', file=\'{self.filename}\')'.format(self=self)
    def __len__(self):
        return self.length;

class DecryptException(Exception):
    def __init__(self, message):
       self.message = message
