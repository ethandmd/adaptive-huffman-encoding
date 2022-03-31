# csci2-hw7

## Usage:
```
$ make
$ make test
```

## Design:

#### HTree: 
Must have a key and value input to its constructor. The interesting function is ```path_to()``` which is effectively just a reproduction of the same function for a struct instead of a class. They key here is to check that the left / right child exists before attempting to recurse to that subtree while searching for a node.

#### HForest:
+ The underlying datastructure is a ```std::vector``` to facilitate adding and removing items easily.
+ The data is internally treated as a min-heap, relying on the standard library heap methods.
+ To achieve a min-heap, a custom comparator function checks the values of the roots of two trees to see which is larger.
+ Passing this function to ```std::make_heap``` was a nightmare until I realized I needed to wrap the function in a struct and overload the function operator to create a functor like in the example.
+ Note: when ```pop_tree()``` is called, the min tree is not only removed from the heap to the end of the underlying vector, but it is also removed from the vector itself.
+ This behavior allows the class to rely on the standard library vector methods size as ```size()``` to calculate the size of the heap.
+ I chose not to have private data for the heap size. Instead of incrementing and decrementing an private value everytime a tree is popped or added, I chose to just calculate the size with the standard vector method on each call.
# csci2-hw8
