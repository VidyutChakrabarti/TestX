## TestX
A test generation framework which uses gcov to produce data structures that can be used to test long files of code. 
Current support includes generation framework for 3 data structures: linked-lists, graphs, trie. 

### A basic class diagram
<pre><code>
+---------------------------------------------------+
|                   TestGenerator<T>                |
|---------------------------------------------------|
| +generateTest(): T                                |
| +deleteTest(T): void                              |
| +toContinue(): bool                               |
|---------------------------------------------------|
|                      ^                            |
|                      |                            |
|                      |                            |
|    +------------------------------------+         |
|    |           Graphtg : TestGenerator  |         |
|    |------------------------------------|         |
|    | +generateTest(): Graph*            |         |
|    | +deleteTest(Graph*): void          |         |
|    | +toContinue(): bool                |         |
|    +------------------------------------+         |
|                  ^                                  |
|                  |                                  |
|                  |                                  |
|  +------------------------------------+             |
|  |   Graphtg_userfunction : Graphtg   |             |
|  |------------------------------------|             |
|  | +callPUT(Graph*): void             |             |
|  +------------------------------------+             |
|                                                   |
+---------------------------------------------------+

+---------------------------------------------------+
|                      Graph                        |
|---------------------------------------------------|
| +nodes: vector<Graphnode*>                        |
| +edges: vector<vector<int>>                       |
| +weights: vector<vector<float>>                   |
|---------------------------------------------------|
| +print_graph(): void                              |
| +connected_components(): vector<set<int>>         |
|---------------------------------------------------+
</pre></code>
