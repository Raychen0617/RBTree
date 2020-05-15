# RBTree

Method and solutions: I use a structure to write the tree and a class to write all the functions, 
including inorderoutput , delete (binary search tree delete method, which has 3 cases), deletefixup
(in order to fix up after the binary search tree delete method to deal with the properties in 
red black tree, which has four cases), insert (binary search tree insert method),insertfixup(same as deletefixup) 
and so on. All these methods’ details are in teacher’s ppt, I use ppt’s pseudocode to write my class function.
Then, use string getline to get the inputs, and another getline to delete 多餘的換行字元(原本適用get但因為linux的
換行字元好像不只有/n), then I use substr to 分割insert strings to char and atoi to change char into int. Last, 
we can call the function from class
