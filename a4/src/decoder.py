"""
Provided for you is the encryption alphabet used to encrypt the provided files.
This inclues: a-z, A-Z, 0-9, punctuation like .(); (not the same as in a1-a3), space and newline
"""
#!/usr/bin/env python3
import string
import re
import datetime
from cipher import FileDecoder, DecryptException

def delay_convert(delay, length):
    average = delay/length
    #print(average, average.seconds, average.microseconds, average.seconds + average.microseconds / 1000000)
    return '{:.2f}'.format((average.seconds+average.microseconds/1000000)/60)

def print_result(file_decoder):
    print("RESULTS")
    print(file_decoder)
    print('Entries: {}'.format(len(file_decoder)))
    delay_dic = {}                                                          # key = month, value = sum of delay
    count_dic = {}                                                          # key = month, value = the number of row(schedule) of each month
    for row in file_decoder:
        if not row[3].isdigit():                                            # check if the row stores schedules. if not move on to next row
            continue
        scheduled = datetime.datetime(int(row[3]),int(row[4]),int(row[5]),int(row[6]),int(row[7]))
        actual = datetime.datetime(int(row[8]),int(row[9]),int(row[10]),int(row[11]),int(row[12]))
        if scheduled.strftime("%b") in delay_dic:
            delay_dic[scheduled.strftime("%b")] += (actual - scheduled)
            count_dic[scheduled.strftime("%b")] += 1
        else:
            delay_dic[scheduled.strftime("%b")] = actual - scheduled
            count_dic[scheduled.strftime("%b")] = 1            
    for month in delay_dic:
        print('    Average delay for {}: {}'.format(month, delay_convert(delay_dic[month], count_dic[month])))
    print("END")


def main():

    alphabet = string.ascii_lowercase + string.ascii_uppercase + string.digits + string.punctuation + " \n"
    p1 = r'(?:[a-z0-9!@#$&*_.-]*[A-Z][a-z0-9!@#$&*_.-]*)+'
    p2 = r'[A-Za-z0-9]*(?:[!@#$&*_.-][A-Za-z0-9]*){2}'
    p3 = r'[A-Za-z!@#$&*_.-]*\d(?:[A-Za-z!@#$&*_.-]*\d[A-Za-z!@#$&*_.-]*)+'
    p4 = r'[A-Za-z0-9!@#$&*_.-]{6,8}'

    while True:
        filename = input("Enter file name or to exit enter 'q' \n")
        if filename == 'q':
            break
        key = input("Enter key or to exit enter 'q' \n")
        if key == 'q':
            break
        try:                                                                # check if key contains at least one uppercase letter
            if re.match(p1,key).group(0) != key:
                print("key has to contain at least one upper case letter")
                continue
        except:
            print("key has to contain at least one upper case letter")
            continue
        try:                                                                # check if key contains just two of special character(!@#$&*-_.)
            if re.match(p2, key).group(0) != key:
                print("key has to contain just two special chracters")
                continue
        except:
            print("key has to contain just two special characters")
            continue
        try:
            if re.match(p3,key).group(0) != key:                            # check if key contains at least two numeric character
                print("key has to contain two or more numeric character")
                continue
        except:
            print("key has to contain two or more numeric character")
            continue
        try:                                                                # check if the length of key is 6 to 8
            if re.match(p4, key).group(0) != key:
                print("length of key has to be 6 to 8")
                continue
        except:
            print("length of key has to be 6 to 8") 
        try:
            temp = open(filename,"r")
        except:
            print("Incorrect filename or path entered")
            continue
        try:                                                                # initialize file_decoder
            file_decoder = FileDecoder(filename, key, alphabet)
        except DecryptException as e:                                       # when fail to pass key validity check, raise DecrpyException 
            print(e)
            continue
        print_result(file_decoder)
        
        break

if __name__ == "__main__":
    main()
