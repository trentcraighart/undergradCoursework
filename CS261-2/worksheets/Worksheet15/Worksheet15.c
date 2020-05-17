Worksheept 15 Response

Do a similar analysis for 25 consecutive add operations, assuming that the internal array begins with 5 elements (that means, with size =0, capacity=5). What is the cost when averaged over this range?

CurrentStep/TotalCost/Size/Capacity
1/1/1/5
1/2/2/5
1/3/3/5
1/4/4/5
1/5/5/5
6/11/6/10

This pattern will repeat with each resize space costing the current old size + 1.

We will get 25 for the basic additions and we will get 6, 11, 16, and 21 additional operations for resizes

25+6+11+16+21 = 79 operations