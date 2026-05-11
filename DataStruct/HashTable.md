-   construct the reflection between key and value to archieve element-query with
> get value from hash table through index which calculate the input key with hash function 

### steps of hash(x) implementation
1. what use someone hash-function work out hash-value
2. perform modulo operation in hash values which hash functions work out with buckets number
> Hash Table store key-value pairs in **buckets** that is array which store pairs of (k,v)
### performance for elements

|        | array | link | hashtable |
| :----: | :---: | ---- | --------- |
|  qury  | O(n)  | O(n) | O(1)      |
|  add   | O(1)  | O(1) | O(1)      |
| delete | O(n)  | O(n) | O(1)      |
[[Excalidraw/HashMap|HashMap]]
[![HashTable](./assets/HashTable/file-20260507180010665.png)]

# Hash conflict
- there are many situations that *n*-to-1, namely *N* input keys is reflected to one value

[ ![Hash-conflict]( ./assets/HashTable/file-20260507180001398.png ) ]

#### How to optimize the Hash Table for Hash conflict
- separate chaining
	conbine same index which calculate with hash function as singal link
	[ ![separate-chaining]( ./assets/HashTable/file-20260507175933865.png ) ]

- open addressing
    1. linear detection
    2. square detection
    3. respective detection
	    - use respectively different hash function to calculate hash values 

> the open addressing above have a known issue which can't delete elements

