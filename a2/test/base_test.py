#import pytest
import unittest
import sys
import io
import contextlib
import argparse
from unittest.mock import patch

sys.path.append("src")
import word_count

class WordCountTest(unittest.TestCase):
    import word_count
    def __init__(self, test_case, extra_args, test_part):
        super(WordCountTest, self).__init__(test_case) 
        self.arguments = ["word_count.py"] + extra_args + ["--infile"]
        self.test_part = test_part
        self.maxDiff = None

    def _test_case(self, arguments, solution):
        with unittest.mock.patch('sys.argv', arguments):
            buf = io.StringIO()
            with contextlib.redirect_stdout(buf):
                self.word_count.main()
            expected = open(solution, "r").read() 
            self.assertEqual(expected, buf.getvalue(), msg=f"--> {solution}")

    def test_t01_empty_file(self):
        self._test_case(self.arguments + ["cases/t01.txt"], f"cases/{self.test_part}/c01.txt")
    def test_t02_single_word(self):
        self._test_case(self.arguments + ["cases/t02.txt"], f"cases/{self.test_part}/c02.txt")
    def test_t03_long_word(self):
        self._test_case(self.arguments + ["cases/t03.txt"], f"cases/{self.test_part}/c03.txt")
    def test_t04_multi_words(self):
        self._test_case(self.arguments + ["cases/t04.txt"], f"cases/{self.test_part}/c04.txt")
    def test_t05_multi_line(self):
        self._test_case(self.arguments + ["cases/t05.txt"], f"cases/{self.test_part}/c05.txt")
    def test_t06_special_characters(self):
        self._test_case(self.arguments + ["cases/t06.txt"], f"cases/{self.test_part}/c06.txt")
    def test_t07_extra_spaces(self):
        self._test_case(self.arguments + ["cases/t07.txt"], f"cases/{self.test_part}/c07.txt")
    
    @unittest.skip("during evaluation marking only")
    def test_t08_long_paragraph(self):
        self._test_case(self.arguments + ["cases/t08.txt"], f"cases/{self.test_part}/c08.txt")
    
    @unittest.skip("during evaluation marking only")
    def test_t09_long_paragraphs(self):
        self._test_case(self.arguments + ["cases/t09.txt"], f"cases/{self.test_part}/c09.txt")
    
    @unittest.skip("during evaluation marking only")
    def test_t10_super_long(self):
        self._test_case(self.arguments + ["cases/t10.txt"], f"cases/{self.test_part}/c10.txt")
    
