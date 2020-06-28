# 3Dhistech

My main design goal when I initially started solving the problem was allocating the images in a contiguous memory pool. Upon initializing the Cache, memory is allocated, and if we dont exceed the allocated memory no allocation for images takes place again. For bookkeeping the Cache only uses a "pointer" to know where it can place the next image. The cache contains a simplistic linked list, the nodes of list containt the information needed for lookup. This means that a small amount of memory is allocated in the list when you put an image in the Cache. Removing an image is as follows: we lookup the entry in the list, remove it from the chain, and free the memory allocated for the node. After this, we shift all the byte entries in the cache forward by the amount the deleted image took up. So no new allocation is needed for the images, only shuffling around some bytes. 

The main problem I see with my implementation is that the node search is in linear time. If we are allocating many hundreds or thousands of images and want to access them fast, this could be a bottleneck. This problem could be reduced or minimized by using some kind of a tree structure (binary red-black tree maybe) instead of the linked list. This would make the lookup time logarithmic which is obviously much better. However I feel like implementing this tree is outside of the scope of this homework exercise, but I could do it if deemed necessary.

The main upside of this implementation is the contiguous allocation: this means that if we are careful about the order of the insertion of our pictures they will be right next to eachother in memory. Since the use of the pictures will be most likely sequential we could write a function to give us access to the memory chunk in the cache in which we are interested (e.g.: the memory chunk belonging to a given slide), and this would mean that the memory access is very cache-miss optimal, and we dont have to deal with the linear lookup time too much: just lookup the first image and you get the rest by knowing the size of the region we are interested in.

Summary:

cons:
- linear lookup time (can be improved with a better underlying bookkeeper structure)
- no proper error handling because of the exercise limitations
- code is not trivial to reason about or debug

pros:
- one allocation for images
- very cache-friendly access if we know what we are doing
- removing an image does not mean we need to free memory, just copy a block



My test cases can be found in the main.cpp.
