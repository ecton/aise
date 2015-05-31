# Grammar

The syntax of this document is reminiscent of [Backus-Naur Form](http://en.wikipedia.org/wiki/Backus%E2%80%93Naur_Form). If you are familiar with that form, this file should be fairly readable. To briefly attempt to document how to read this document, the notations used in this document:

* `rulename := ...`: Defines a grammar rule named `rulename` with the _pattern_ that matches it being after the `:=` symbol.
* `lowercase_word`: A reference to a grammar rule.
* `UPPERCASE_WORD` or `'characters'`: A token returned from [the lexer](./lexical-syntax.md).
* `( ... )`: Terms wrapped in square brackets are grouped.
* `*`: The term or group preceeding the asterisk can be repeated 0, 1, or multiple times.
* `+`: The term or group preceeding the plus sign can be repeated 1 or multiple times, but is required to occur at least once.
* `?`: The term or group preceeding the question mark is optional but can at most be specified once.
* `x | y`: Within the group or rule, either x or y may be used to fulfill the pattern.

## Expressions

### `expression`: Intro

The expressions listed below are in order of precedence. It may look backwards to begin with, but the lowest precedent is the first rule because it should be parsed last. So, to begin with, expression is a result of parsing addsub_expression. For example, a + b * c should result `AddNode(a,MulNode(b,c))`.

`expression := logical_expression`

### Logical or Bitwise operators

`logical_expression := comparison_assignment_expression ((AND | OR | XOR) expression)*`

### Comparison operators

`comparison_assignment_expression := addsub_expression ((EQ | ASSIGN | LESS | GREATER | LESSEQ | GREATEREQ | NOTEQ) expression)*`

### Addition and Subtraction

`addsub_expression := muldiv_expression (('-' | '+') expression)*`

### Multiplication and Division

`muldiv_expression := power_expression (('*' | '/') expression)*`

### Power (exponentiation)

`power_expression := negate_expression ('^' expression)*`

#### Negate (not)
`negate_expression := 'NOT' term`

### Terms

Term is the most complex rule because there are a lot of options and there's recursion. To express it best, it is presented as a list of options

* `'(' expression ')'`
* `'[' argument_list ']'`
* `'{' (key_value_pair (',' key_value_pair)*)* '}'` with `key_value_pair := expression ':' expression`
* `INTEGER | REAL | TRUE | FALSE | NIL | STRING`
* `CONTINUE | BREAK`
* `IDENTIFIER` optionally, recursively followed by:
  * `'(' argument_list ')'`
  * `'[' value_list ']'` with `value_list := (expression (',' expression)*)?`
  * `'.' IDENTIFIER`

#### Parenthesis
`parenthesis_term := '(' expression ')'`

#### Lambdas
`lambda_expression := short_form_lambda | long_form_lambda`

##### Inline / Short form lambdas
`short_form_lambda := '$' '(' parameter_list ')' '-' '>' '(' expression ')'`

##### Multi-statement / Long form lambdas
`long_form_lambda := DO '(' parameter_list ')' EOL code_statement_list END`

# Module Body

`module := declaration_statement_list`

## Declaration Statements

`declaration_statement_list := EOL* (declaration_statement_line EOL*)*`

`declaration_statement_line := declaration_statement (EOL | EOF)`

### Namespaces

`class := CLASS IDENTIFIER (INHERITS IDENTIFIER ('.' IDENTIFIER)*)? EOL declaration_statement_list END`

`module := MODULE IDENTIFIER EOL declaration_statement_list END`

### Methods

`method := (METHOD | FUNCTION) IDENTIFIER '(' parameter_list ')' EOL code_statement_list END`

### Properties and Constants



## Code Statements

`code_statement_list := EOL* (code_statement_line EOL*)*`

`code_statement_line := (flow_statement | fundamental_statement (IF expression)?) (EOL | EOF)`

### Fundamental Statements

* `assignment_statement := term ':=' expression`
* `call_statement := term`
* `return_statement := RETURN expression`

### Flow Control

`if_statement := IF expression THEN EOL code_statement_list (ELSE IF expression THEN EOL code_statement_list)* (ELSE EOL code_statement_list)? END`

`while_loop := WHILE expression EOL code_statement_list END`

`for_loop := FOR IDENTIFIER ':='' expression TO expression (STEP expression) EOL code_statement_list END`

`for_each_loop := FOR EACH IDENTIFIER (',' IDENTIFIER)? IN expression EOL statement_list END`