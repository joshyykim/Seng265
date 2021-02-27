import unittest
import inspect

from base_test import WordCountTest

if __name__ == '__main__':
    suite = unittest.TestSuite()
    all_test_funcs = sorted(filter(lambda x: x[0].startswith("test_"), 
                        inspect.getmembers(WordCountTest, predicate=inspect.isfunction)), 
                        key=lambda x: x[0])
  
    for _test_fnc, _ in all_test_funcs:
        suite.addTest(WordCountTest(_test_fnc, ["--sort", "--print-words"], "C"))
    unittest.TextTestRunner(verbosity=2).run(suite)
   
