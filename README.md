# kimchi
Python2 & 3 C Extension for serializing certain built-in Python types

`kimchi` offers functionality very similar to the default `pickle` module.  Unlike `pickle` though, `kimchi` cannot serialize generic Python objects and classes.  `kimchi` can only serialize built in Python objects - in particular:
* Integers (only in Python2)
* Floats
* Longs
* Strings (Bytes in Python3)
* Unicodes (Strings in Python3)
* Lists
* Tuples
* Sets
* Frozensets
* Dictionaries
* None objects
* Booleans

However, for most objects `kimchi` performs serialization faster than the built-in `pickle` library, and more importantly, produces more compact objects.

## Usage
kimchi has two single argument functions, `loads` and `dumps`.  `dumps` is used to create serializations of objects, and `loads` is used to recreate the original object given its serialization.

## Installation
#### Using git
```
$ git clone https://github.com/warrenspe/kimchi.git
$ cd kimchi
$ sudo python3 setup.py install
```

## Examples
```
>>> import kimchi
>>> serialization = kimchi.dumps(123)
>>> serialization
'\x01\x81{'
>>> kimchi.loads(serialization)
123

>>> serialization = kimchi.dumps('123')
>>> serialization
'\x05\x83123'
>>> kimchi.loads(serialization)
'123'

>>> serialization = kimchi.dumps([1, 2, 3, ('4', '5', '6')])
>>> serialization
'\x08\x96\x84\x01\x81\x01\x01\x81\x02\x01\x81\x03\t\x8a\x83\x05\x814\x05\x815\x05\x816'
>>> kimchi.loads(serialization)
[1, 2, 3, ('4', '5', '6')]
```

## Speed and size comparisons to the built-in pickle
Note that all tests were done in Python2, comparing to its cPickle module

### Integers
![Alt text](https://drive.google.com/uc?id=0BwLoYm538Nb6OTZSeDAyOWxCRms "")
### Floats
![Alt text](https://drive.google.com/uc?id=0BwLoYm538Nb6aHd1MmFiT3ZjZTA "")
Note: constant size, might be revisited later
### Longs
![Alt text](https://drive.google.com/uc?id=0BwLoYm538Nb6SnZoSHg1c29xb00 "")
### Strings (Bytes in Python3)
![Alt text](https://drive.google.com/uc?id=0BwLoYm538Nb6aEpwZ2hKMVIwSjg "")
Note that the final string was not included in the size comparison, as the size skews the axis of the graph.  The serialized sizes are:
kimchi: 1003, pickle: 1008
### Unicodes (Strings in Python3)
![Alt text](https://drive.google.com/uc?id=0BwLoYm538Nb6dTRZd0lGS0V2Qkk "")

Note that the final unicode string was not included in the size comparison, as the size skews the axis of the graph.  The serialized sizes are:
kimchi: 1003, pickle: 1006
### None objects
![Alt text](https://drive.google.com/uc?id=0BwLoYm538Nb6NGJCclhpSzdobTQ "")

### Boolean objects
![Alt text](https://drive.google.com/uc?id=0BwLoYm538Nb6ZDhjQnhDLXpoR0k "")

***
**Note**: Speed and size for the following types is largely influenced by the items within them, to give the best results they have been filled with the data type which gives the most similar serialization times and sizes between pickle and kimchi, string/bytes objects.  
***
### Dictionaries
![Alt text](https://drive.google.com/uc?id=0BwLoYm538Nb6YUNEck5ubGt4WHM "")
### Lists
![Alt text](https://drive.google.com/uc?id=0BwLoYm538Nb6NmJiOUNleElZUVE "")
### Tuples
![Alt text](https://drive.google.com/uc?id=0BwLoYm538Nb6NFdLNTdkTFlZVzA "")
### Sets
![Alt text](https://drive.google.com/uc?id=0BwLoYm538Nb6LW5kUVU1eGIzODQ "")
