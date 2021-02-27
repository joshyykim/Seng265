#!/usr/bin/env python3

import string
import sys
import re
from collections import OrderedDict

def main():
    #pass #You can delete this one once you start coding your solution 
    #TODO
    type = typeChoice(sys.argv)
    if type == 0:
        return
    try:
        text = open(sys.argv[sys.argv.index("--infile")+1], "r")
    except FileNotFoundError as e:
        print('Error message : Provide proper filename')
        return
    words = readFile(text)
    length = countLength(words)
    #print(words, length)    
    printResult(words, length, type)
    
    text.close()


def typeChoice(argv):
    if  "--print-words" in argv and "--sort" in argv  and "--infile" in argv:
        return 4 #argv.index("--infile")
    elif "--print-words" in argv and "--infile" in argv:
        return 3
    elif "--sort" in argv and "--infile" in argv:
        return 2
    elif "--infile" in argv:
        return 1
    else:
        print("Error message : Provide proper argument")
        return 0


def readFile(text):
    line = text.read()
    words = {}
    while (line):
        #line = line.split(" ")
        line = re.split(';|\.|\,|\(|\)|\n| ', line)
        for word in line:
            if word != '':
                if word in words:
                    words[word] += 1
                else:
                    words[word] = 1
        line = text.read()
    #print(words)
    return words
    
def countLength (words):
    length = {}
    for word in words:
        n = len(word)
        if n in length:
            length[n] += words[word]
        else:
            length[n] = words[word]
    return length

def printResult (words, length, type):
    sortedLength = OrderedDict(sorted(length.items()))
    if type == 1:
        for i in sortedLength:
            print("Count[{0:02d}]={1:02d};".format(i, sortedLength[i]))
    elif type == 2:
        sortedLengthByFreq = {key: value for key, value in sorted(sortedLength.items(), key = lambda item: item[1], reverse = True)}
        for i in sortedLengthByFreq:
            print("Count[{0:02d}]={1:02d};".format(i, sortedLengthByFreq[i]))
        print("Median word length: {0:.1f}".format(medianLength(sortedLength)))
    elif type == 3:
        for i in sortedLength:
            print("Count[{0:02d}]={1:02d};".format(i, sortedLength[i]), end='')
            uniqueWords(words,i) 
    elif type == 4:
        sortedLengthByFreq = {key: value for key, value in sorted(sortedLength.items(), key = lambda item: item[1], reverse = True)}
        for i in sortedLengthByFreq:
            print("Count[{0:02d}]={1:02d};".format(i, sortedLengthByFreq[i]), end='')
            uniqueWords(words,i)

def medianLength(length):
    lengthList = list(length.keys())
    n = len(lengthList)
    if n < 1:
        return 0
    if n % 2 == 0:
        return (lengthList[(n//2)]+lengthList[(n//2)-1]) / 2
    else:
        return lengthList[(n//2)]
        

def uniqueWords(words, l):
    words = OrderedDict(sorted(words.items()))
    count = 0
    times = 0
    for word in words:
        if l == len(word):
            times += 1
    print(" (words: ",end='')
    for word in words:
        if l == len(word):
            count += 1
            if times == 1:
                print('"',word,'")', sep = "")
                break
            if count == times:
                print('and "', word, '")', sep = "")
            elif count == (times-1):
                print('"',word,'" ', sep = "", end = "")
            else:
                print('"',word,'", ', sep = "", end ="")


#Do not change this
if __name__ == "__main__":
    main()

    
