This program includes a method that takes in a specifically formatted graph - called a polytree - in a text file and subsequently compresses the tree.  

The main.cpp is only used for testing purposes. The algorithm itself is found in Poly.cpp and its included imports.  

This program is written in C++.  

The poly tree is formatted such that it is a non-directed graph, and each node has a particular numerical value. The compression works such that it performs a lossless compression so connected nodes with the same values are reduced into a single node.  

The time complexity of this algorithm sits at the most optimal O(V+E), where V is the number of nodes and E is the number of edges.  

This algorithm is useful in any instance where data is represented by connected un-directed graphs and if analyses, like machine learning, wants to be performed on it. It is useful because for extremely large polytree representations, ML algorithms (as well as other analytical algorithms) are very computationally expensive, so this offers a way of optimizing the number of computations needed.
