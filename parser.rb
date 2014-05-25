require './lexer.rb'
require './ast.rb'

class Parser
  def initialize(tokens)
    @tokens = tokens
    @pos = 0
  end

  def peek_token(offset = 0)
    @tokens[@pos + offset]
  end

  def take_token!
    token = peek_token
    next_token!
    return token
  end

  def next_token!
    @pos += 1
  end

  def eof?
    @pos >= @tokens.count || peek_token.type == Lexer::EOF
  end

  def parse
    parse_statement_list
  end

  def parse_statement_list
    # TODO: Actual statements
    parse_expression
  end

  def parse_expression
    parse_logical_expression
  end

  def parse_logical_expression
    left = parse_comparison_assignment_expression
    
    while !eof?
      case peek_token.type
      when Lexer::AND
        operator = take_token!
        right = parse_comparison_assignment_expression
        left = AndNode.new(:token => operator, :left => left, :right => right)
      when Lexer::OR
        operator = take_token!
        right = parse_comparison_assignment_expression
        left = OrNode.new(:token => operator, :left => left, :right => right)
      when Lexer::XOR
        operator = take_token!
        right = parse_comparison_assignment_expression
        left = XorNode.new(:token => operator, :left => left, :right => right)
      else
        break
      end
    end
    return left
  end

  def parse_comparison_assignment_expression
    left = parse_addsub_expression
    
    while !eof?
      case peek_token.type
      when Lexer::LESSEQ
        operator = take_token!
        right = parse_addsub_expression
        left = LessThanOrEqualNode.new(:token => operator, :left => left, :right => right)
      when :<
        operator = take_token!
        right = parse_addsub_expression
        left = LessThanNode.new(:token => operator, :left => left, :right => right)
      when "=".to_sym
        operator = take_token!
        right = parse_addsub_expression
        left = EqualNode.new(:token => operator, :left => left, :right => right)
      when Lexer::NOTEQ
        operator = take_token!
        right = parse_addsub_expression
        left = NotEqualNode.new(:token => operator, :left => left, :right => right)
      when :>
        operator = take_token!
        right = parse_addsub_expression
        left = GreaterThanNode.new(:token => operator, :left => left, :right => right)
      when Lexer::GREATEREQ
        operator = take_token!
        right = parse_addsub_expression
        left = GreaterThanOrEqualNode.new(:token => operator, :left => left, :right => right)
      when Lexer::ASSIGN
        operator = take_token!
        right = parse_addsub_expression
        left = AssignNode.new(:token => operator, :left => left, :right => right)
      else
        break
      end
    end
    return left
  end

  def parse_addsub_expression
    left = parse_muldiv_expression
    
    while !eof?
      case peek_token.type
      when :+
        operator = take_token!
        right = parse_muldiv_expression
        left = AddNode.new(:token => operator, :left => left, :right => right)
      when :-
        operator = take_token!
        right = parse_muldiv_expression
        left = SubtractNode.new(:token => operator, :left => left, :right => right)
      else
        break
      end
    end
    return left
  end

  def parse_muldiv_expression
    left = parse_power_expression
    
    while !eof?
      case peek_token.type
      when :*
        operator = take_token!
        right = parse_power_expression
        left = MultiplyNode.new(:token => operator, :left => left, :right => right)
      when :/
        operator = take_token!
        right = parse_power_expression
        left = DivideNode.new(:token => operator, :left => left, :right => right)
      else
        break
      end
    end
    return left
  end

  def parse_power_expression
    left = parse_term
    
    while !eof?
      case peek_token.type
      when "^".to_sym
        operator = take_token!
        right = parse_term
        left = PowerNode.new(:token => operator, :left => left, :right => right)
      else
        break
      end
    end
    return left
  end

  def parse_term
    case peek_token.type
    when Lexer::INTEGER, Lexer::REAL
      return LiteralNode.new(:token => take_token!)
    when Lexer::IDENTIFIER
      return IdentifierNode.new(:token => take_token!)
    else
      raise "Unknown token #{peek_token}" # TODO: Better error handling than this!
    end
  end
end

