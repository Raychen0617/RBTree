# RBTree

Method and solutions: I use a structure to write the tree and a class to write all the functions,<br>
including inorderoutput , `delete`(binary search tree delete method, which has 3 cases), <br>
`deletefixup` (in order to fix up after the binary search tree delete method to deal <br>
with the properties in red black tree, which has four cases), `insert`<br>
(binary search tree insert method),`insertfixup`(same as deletefixup) and so on. <br>
All these methods’ details are in teacher’s ppt, I use ppt’s pseudocode to write my class function.<br>                     
Then, use string getline to get the inputs, and another getline to delete<br>
多餘的換行字元(原本適用get但因為linux的換行字元好像為/n/r), then I use substr to 分割insert<br>
strings to char and atoi to change char into int. Last, we can call the function from class                   

# RBtree implementation

## RBtree insert and insertfixup:
[reference](http://alrightchiu.github.io/SecondRound/red-black-tree-insertxin-zeng-zi-liao-yu-fixupxiu-zheng.html)
## RBtree delete and deletefixup:
[reference](http://alrightchiu.github.io/SecondRound/red-black-tree-deleteshan-chu-zi-liao-yu-fixupxiu-zheng.html)
