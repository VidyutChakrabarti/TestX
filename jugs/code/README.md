Program under test (PUT) - Jugs
-------------------------------
The program under test is a solution to a simple programming puzzle: Given
two jugs of capacity c1 and c2, and a final volume f, the program should
find the shortest sequence of steps to be followed to achieve a volume of
f in either of the jugs the other being empty.

To compile the Jugs program, run:
	make jugs

To run the Jugs program, run:
	./jugs c1 c2 f

For example, running:
	./jugs 9 15 3
will yield:
(0, 0)
(9, 0)
(0, 9)
(9, 9)
(3, 15)
(3, 0)

each line showing the volume of water in each jug in each subsequent step.

Testing Jugs
------------
We have implemented a basic test automation system as a warm up exercise.

To compile the test program, run:
	make test_jugs

To run the test, run:
	./test_jugs

The output of executing the test will appears somewhat as follows:
Coverage: 
Testcase1 : , 0, 2, 4, 5
Testcase2 : , 0, 1, 2, 4, 5, 2, 4, 5
Testcase3 : , 0, 1, 19, 20, 22, 23, 19, 21, 24, 2, 4, 5, 2, 4, 5
Testcase4 : , 0, 30, 31, 32, 31, 32, 33, 36, 37, 2, 4, 5
covered locations : , 0, 1, 2, 4, 5, 19, 20, 21, 22, 23, 24, 30, 31, 32, 33, 36, 37

This shows that four test cases were run: Testcase1, Testcase2, Testcase3 and 
Testcase4. Against each test case, the program locations that were covered 
by that test case are list.
The last line of the output shows the list of all locations that were covered by all
the test cases.

Cleanup
-------
Run:
	make clean

If required, to clean the directory of binaries to begin the building process afresh.

Design of the Tester
--------------------
Instrumentation: The program under test jugs.cpp has been instrumented for
labelling the program locations to be covered with numbers and inserting
logging instruction at these locations. The instrumented version of jugs.cpp
is jugs_instrumented.cpp.
Testcases and Test harness: The key part of the test automation is implemented
in the file tester.cpp and tester.h. This module implements two classes:
TestHarness provides the capability of running test cases in sequence, recording
and outputing the coverage report. Testcase is the test case class.

Test case Design
----------------
As this is the first cut attempt in getting some hands on experience with unit testing,
we have written the test cases automatically. But, we have followed a somewhat
systematic approach in this. We have drawn a function call graph (doc/dep.dot).
This gives us an idea about the functions which are independent and easier to
test and about those which make calls to other functions. We have chosen to 
first write test cases for testing the functions which are lower down in the
dependency graph (i.e. they are independent).

What has been achieved?
------------------------
Automated execution of test cases and recording coverage.

What next?
----------
- Automatic test generation
- Automated instrumentation
- Automated function call graph generation
