#!/bin/bash

echo "Running all python tests ..."

echo "========== START PART A ==============="
python test/test_A.py
echo "========== END PART A ==============="

echo "========== START PART B ==============="
python test/test_B.py
echo "========== END PART B ==============="

echo "========== START PART C ==============="
python test/test_C.py
echo "========== END PART C ==============="
