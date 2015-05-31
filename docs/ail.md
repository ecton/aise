# Aise Intermediate Language (AIL)

This is the documentation of the intermediate language instruction set. This instruction set is a VM-like bytecode that the interpretters on the various platforms will implement in a standardized method.

## File Format

The binary file format for AIL is a streamed file format of instructions. Each instruction is variable length due to the variable length of arguments, especially in the case of function calls. The header of the file contains a mapping of instruction offsets, although implementors are encouraged to parse and load the entire file and pre-adjust for endianness. One method of doing this would be a threaded approach by streaming the adjustment of the endianness and other pre-loading mechanisms, while beginning to interpret the first sets of instructions and pausing to wait if jumps were made that hadn't been loaded yet.

Multiple decisions of this file format are made in part due to popular processor architectures of today, but should remain viable for the foreseeable future. First, all integer values are stored in little endian. Mext, the word size of integer values except for the initial 8 bytes of the file are 8 bytes long. In a way, however, the first 8 bytes can be considered a single value depending on the compatability provided by the interpretter in question across multiple file versions.

### Header

The header of is 64 bytes long.

* Magic code, 4 bytes, `Aise`
* Version number, 4 bytes, current version is 1
* Instruction Count, 8 bytes
* Instruction Offset Table Start, 8 bytes, absolute
* Instruction Table Start, 8 bytes
* Literal Table Start, 8 bytes, absolute
* Reserved space, 24 bytes

### Instruction Offsets Table

The table is a consecutive string of 8 byte integers of offsets into the instruction table. The offsets are relative to the start of the Instruction Table. The table should be read for precisely the number of instructions in the header, and extra space should be ignored.

### Instruction Table

The general instruction format is as follows:

* Opcode, 4 bytes
* Instruction Length, 4 bytes
* Operator data

The format of each argument is detailed under the specific instruction.

Each instruction is aligned to 16 byte offsets.

#### Instruction Arguments

Each argument has a header:

* Type, 4 bytes
* Length, 4 bytes

Each argument is padded out to 8 byte offsets

##### Integer literals

Integer literals are expressed as 8 byte values.

##### Floating Point literals

Floating point literals are expressed as 8 byte values in [IEEE 754 format](http://en.wikipedia.org/wiki/IEEE_floating_point). Note that these are also [dependent on endianness](http://en.wikipedia.org/wiki/Endianness#Floating-point_and_endianness).

##### String literals

Strings are always UTF-8 chunks of data. However, string data is not stored inline, but instead this is represented with an 8 byte offset relative to the start of the Literal Table.

##### Value ID

Value IDs are 8-byte integers representing a unique value reference in the current state of the program. IDs are generated at compile time.

> Random thoughts that influence values. Each method gets passed a context comprised of up to 3 scopes: global, instance, and inherited. Global is the top level declarations. instance is the immediate containing instance (in the case of a class, the class itself is an instance of Class), and inherited is if this method is a lamba, a reference to the locally created context in the containing method. Even lambdas within lambdas all share the original parent context. 

> A value reference is a combination of context reference + field id, both 8 byte values. The lookup opcodes instructions are only used to find and cache in the local execution cache the value references. The actual values are stored in contexts or objects and references and IDs are only used to aide in how the IL works efficiently.

## Arithmetic Operations

### add result, lval, rval

Performs addition between the two arguments `lval` and `rval` and stores it in `result`.

`result = lval - rval`

### subtract result, lval, rval

Performs subtraction between the two arguments `lval` and `rval` and stores it in `result`.

`result = lval - rval`

### multiply result, lval, rval

Performs multiplication between the two arguments `lval` and `rval` and stores it in `result`.

`result = lval * rval`

### divide result, lval, rval

Performs division between the two arguments `lval` and `rval` and stores it in `result`.

`result = lval / rval`

### pow result, lval, rval

Performs exponentiation between the two arguments `lval` and `rval` and stores it in `result`.

`result = lval ^ rval`

## Logical / Bitwise Operations

### and result, lval, rval

Performs a logical or bitwise and operation between the two arguments `lval` and `rval` and stores it in `result`.

`result = lval and rval`

### or result, lval, rval

Performs a logical or bitwise or operation between the two arguments `lval` and `rval` and stores it in `result`.

`result = lval or rval`

### xor result, lval, rval

Performs a logical exclusive or or bitwise exclusive or operation between the two arguments `lval` and `rval` and stores it in `result`.

`result = lval xor rval`

### not result, rval

Performs a logical or bitwise negate operation on the argument `rval` and stores it in `result`.

`result = not rval`

## Comparison

### compare result, lval, rval

Performs a comparison between the two arguments `lval` and `rval` and stores it in `result`.

`result = compare(lval, rval)`

## Assignment 

### assign destination, rval

Assigns a reference of the the argument `rval` to the location of `destination`.

`destination := rval`

### indexassign destination, root, arguments, rval

Assigns a reference of the argument `rval` to the object `root` at the destination described by `arguments`

`root[arguments] := rval`

## Invocation Operations

### lookup result, name

Looks up `name` in current contexts and stores the found value reference in `result`.

### fieldlookup result, root, name

Looks up `name` on  `root` and stores the found value reference in `result`.

### index result, root, arguments

Calls the index operator (for arrays, maps) on `root` and stores the returned value in `result`

### call result, root, arguments

Calls the function `root` passing `arguments` to it, storing the returned value in `result`

## Context and state management

> TODO: pushing and popping contexts