# Expressions

### `expression`: Intro

The expressions listed below are in order of precedence. It may look backwards to begin with, but the lowest precedent is the first rule because it should be parsed last. So, to begin with, expression is a result of parsing addsub_expression.

`expression := logical_expression`

### Logical or Bitwise operators

`logical_expression := comparison_assignment_expression [(AND | OR | XOR) expression`

### Comparison operators

`comparison_assignment_expression := addsub_expression [(EQ | ASSIGN | LESS | GREATER | LESSEQ | GREATEREQ | NOTEQ ) expression`

### Addition and Subtraction

`addsub_expression := muldiv_expression [('-' | '+') expression]`

### Multiplication and Division

`muldiv_expression := power_expression [('*' | '/') expression]`

### Power (exponentiation)

`power_expression := logical_expression ['^' expression]`

### Terms
`term := parenthesis_term | negate_term | lambda_term | INTEGER | REAL | IDENTIFIER [('(' argument_list ')' | '[' argument_list ']')]`

#### Parenthesis
`parenthesis_term := '(' expression ')'`

#### Negate (not)
`negate_expression := 'NOT' expression`

#### Lambdas
`lambda_expression := short_form_lambda | long_form_lambda`

##### Inline / Short form lambdas
`short_form_lambda := '$' '(' parameter_list ')' '-' '>' '(' expression ')'`

##### Multi-statement / Long form lambdas
`long_form_lambda := DO '(' parameter_list ')' EOL statement_list END`

# Statements

`statement_list := [EOL+] statement EOL+ [statement_list]`

`statement := `