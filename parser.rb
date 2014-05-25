require './lexer.rb'

class Parser
  def initialize(tokens)
    @tokens = tokens
    @pos = 0
  end

  def peek_token(offset = 0)
    @token[@pos + offset]
  end

  def next_token!
    @pos += 1
  end

  def eof?
    @pos >= @token.count || peek_token.type == Lexer.EOF
  end

  def parse
    parse_statement_list
  end

  def parse_statement_list
    
  end
end