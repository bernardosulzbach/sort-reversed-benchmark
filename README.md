# Sort Reversed C++ Benchmark

If you can't use std::greater<>, how do you sort backwards?

I've compared using reverse iterators, reversing after sorting, and writing a
custom comparator using < and !=, but the results were too noisy to be of any
significance. So I'd say it simply does not matter.
