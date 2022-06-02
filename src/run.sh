#!/bin/bash

gcc vector.c test_vector.c -o test_vector && ./test_vector
rm test_vector