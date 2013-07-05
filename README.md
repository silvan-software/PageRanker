Page Rank implementation by Joseph P. Silva

Based on "Searching the web"
in ACM Transactions on Internet Technology, Vol. 1, No. 1, August 2001

And also WikiPedia article on PageRank algorithm at http://en.wikipedia.org/wiki/PageRank

- duplicate links are ignored after the first one seen
- links that go to same page are ignored
- leak sinks handled via decay factor per the documents listed above
- leak nodes are treated as if they link out to all other pages

1: Use the standard *nix make file to build executable "PageRanker"

2: Usage: PageRanker filename num_iterations decay_factor

3: Run it against the test data files:

PageRanker testBadInput 1 1
PageRanker test13a 100 1
PageRanker test13b 100 .8
PageRanker testWikiExample 100 .85


testBadInput should report:

line 2 page links to itself...ignored
line 3 missing second page...ignored
line 4 no pages...ignored
INITIAL RANKS 
C 0.333333
B 0.333333
A 0.333333
*** ITERATION 1***
C 0.333333
B 0.5
A 0.166667


test13a and test13b based on similarly named diagram in the ACM paper

Expected final results for 13a:

*** ITERATION 100***
5 0.142857
4 0.142857
3 0.142857
2 0.285714
1 0.285714

values exactly match the paper


Expected final results for 13b:

*** ITERATION 100***
5 0.290177
4 0.312721
3 0.101449
2 0.153623
1 0.142029

values match the paper except the latter clearly has a typo where r(1) and r(2) are swapped


testWikiExample expected results:

*** ITERATION 100***
J 0.0162111
I 0.0162111
H 0.0162111
F 0.0391877
K 0.0162111
G 0.0162111
E 0.081094
A 0.0302911
D 0.0391877
C 0.343793
B 0.385391

testWikiExample based on http://en.wikipedia.org/wiki/File:PageRanks-Example.svg
note the values differ slightly from the diagram, perhaps they did some rounding slightly differently
or handled leak pages slightly differently

The Diagram has:

A  3.3%
B 38.4%
C 34.3%
D  3.9%
E  8.1%
F  3.9%
The other 5 unnamed nodes (G-K in test file): 1.6% each


Code design thoughts:

1: The code is probably recomputing string hashes for the URLs as each link is looked up and then stored in the unsorted maps

If instead of URLs the input is a numeric page ID coming from the Page Repository, the hash computation could be much quicker
for instance just a cast to size_t

2: Iterating through the unsorted map contents during ranking *may* be slower then iterating through a simple array

It *might* be worth building a simple array for the page list and maybe links lists just before page ranking and
use those rather than an iterator from the unsorted maps

3: It might be worth writing unit tests with for instance GoogleTest, based on the test files per above

If one were to be changing this code over time could be worthwhile

4: Per the ACM paper and also Wiki page 100 iterations is probably more than needed for convergence close to the Eigenvector




