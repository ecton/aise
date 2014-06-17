# Lexical Syntax

Below are the rules for how text is tokenized. While the lexer will not use regular expressions, a RegEx rule is provided to show the intent of how a token is composed.

## Reserved Words

* `CLASS`: class
* `FUNCTION`: function
* `LAMBDA`: lambda
* `DO`: do
* `END`: end
* `FOR`: for
* `WHILE`: while
* `NOT`: not
* `AND`: and
* `OR`: or
* `XOR`: xor

## "Compound" Operators (more than one character)

* `NOTEQ`: <>
* `GREATEREQ`: >=
* `LESSEQ`: <=
* `ASSIGN`: :=

## `IDENTIFIER`: Identifiers

An identifier must start with a lowercase letter, uppercase letter, or underscore and then is followed by zero or more of the same set of characters or numbers. An identifier can optionally end in a question mark or exclamation mark.

`[a-zA-Z_][a-zA-Z0-9]*[!?]?`

## Numbers

Numeric literals are either integral or decimal in nature. Integral numbers can take several different forms, and each rule is explained independently below:

### `INTEGER`: Integer

One or more number character represents a base-10 number. Optionally, a `-` character can be used to denote a negative value.

`[-]?[0-9]+`

Additional common base literals are permitted by using the following notations:

* Hexadecimal: `0x[0-9a-fA-F]+`
* Binary: `0b[01]+`
* Octal (base 8): `0o[0-7]+`

### `REAL`: Decimal

One or more number characters followed by a dot and then followed by additional numbers denotes a floating point number. Optionally, a `-` character an be used to denote a negative value.

`[-]?[0-9]+.[0-9]+`


## Strings

String literals are enclosed by double-quotes. The allowed escape sequences are:

* `\r`: Carriage Return (ASCII 13)
* `\n`: New Line (ASCII 10)
* `\\`: Backslash character
* `\0`: "Null" character (ASCII 0)
* `\t`: Tab (ASCII 9)
* `\ux[X+]`: Unicode codepoint represented by hexadecimal characters, e.g. `\ux[2603]` is ☃
* `\u[0+]`: Unicode codepoint in decimal, e.g. `\u[9731]` is ☃