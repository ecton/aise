class Token
  attr_accessor :type
  attr_accessor :text, :value

  attr_accessor :file
  attr_accessor :line
  attr_accessor :column

  def initialize(args)
    self.type = args[:type]
    self.text = args[:text]
    self.value = args[:value]

    self.file = args[:file]
    self.line = args[:line]
    self.column = args[:column]
  end

  def to_h
    {
      :type => type,
      :text => text,
      :value => value,
      :file => file,
      :line => line,
      :column => column
    }
  end
end

class Lexer
  def self.enumerate(sym)
    const_set(sym, sym)
  end

  def report_error(message)
    raise message + " (#{@file}##{@line}:#{@column})"
  end

  def self.enumerate_keyword(sym, word)
    enumerate(sym)
    @keywords ||= {}
    @keywords[word] = sym
  end

  def self.lookup_keyword(word)
    return @keywords[word]
  end

  enumerate :EOF
  enumerate :EOL
  enumerate :IDENTIFIER
  enumerate :INTEGER
  enumerate :REAL
  enumerate :STRING
  enumerate :NOTEQ
  enumerate :GREATEREQ
  enumerate :LESSEQ
  enumerate :ASSIGN
  enumerate_keyword :LAMBDA, "lambda"
  enumerate_keyword :DO, "do"
  enumerate_keyword :END, "end"
  enumerate_keyword :FOR, "for"
  enumerate_keyword :WHILE, "while"
  enumerate_keyword :NOT, "not"
  enumerate_keyword :AND, "and"
  enumerate_keyword :OR, "or"
  enumerate_keyword :XOR, "xor"
  enumerate_keyword :TRUE, "true"
  enumerate_keyword :FALSE, "false"
  enumerate_keyword :NIL, "nil"

  def initialize(src)
    @line = 1
    @column = 1
    @pos = 0
    @src = src
  end

  def newline!
    @line += 1
    @column = 1
  end

  def is_numeric?(char)
    return char && char >= '0' && char <= '9'
  end

  def is_binary?(char)
    return char && char >= '0' && char <= '1'
  end

  def is_octal?(char)
    return char && char >= '0' && char < '8'
  end

  def is_hexadecimal?(char)
    return char && (char >= '0' && char <= '9') ||
      (char >= 'a' && char <= 'f') ||
      (char >= 'A' && char <= 'F')
  end

  def is_whitespace?(char)
    return char == "\t" || char == " "
  end

  def next_char!
    @pos += 1
    @column += 1
  end

  def get_char(offset = 0)
    @src[@pos + offset]
  end

  def start_token!
    @token_start = {
      :pos => @pos,
      :line => @line,
      :column => @column
    }
  end

  def current_token_text
    @src[@token_start[:pos], @pos - @token_start[:pos]]
  end

  def eof?
    @src.length == @pos
  end

  def parse_identifier
    while !eof? && (
          (get_char >= 'a' && get_char <= 'z') ||
          (get_char >= 'A' && get_char <= 'Z') ||
          (get_char >= '0' && get_char <= '9') ||
           get_char == '_' || 
           get_char.ord > 128)
      next_char!
    end
    # An identifier can end in a few special characters
    if ['?','!'].include?(get_char)
      next_char!
    end

    type = self.class.lookup_keyword(current_token_text) || IDENTIFIER

    # Some words are special values
    value = nil
    case type
    when TRUE
      value = true
    when FALSE
      value = false
    when NIL
      value = nil
    else
      value = current_token_text
    end

    return new_token_with_value(type, value)
  end

  def parse_numeric
    sign = 1
    if get_char == '-'
      sign = -1
      next_char!
    end

    value = 0
    while !eof? && is_numeric?(get_char)
      value = value * 10 + get_char.to_i
      next_char!
    end

    if get_char == '.' && is_numeric?(get_char(1)) # Decimal
      next_char!
      decimal_place = 1
      while !eof? && is_numeric?(get_char)
        value += get_char.to_f / (10 ** decimal_place)
        decimal_place += 1
        next_char!
      end
    elsif value == 0 && get_char == 'b' && is_binary?(get_char(1)) # Binary
      next_char!
      while !eof? && is_binary?(get_char)
        value = value * 2 + get_char.to_i
        next_char!
      end
    elsif value == 0 && get_char == 'o' && is_octal?(get_char(1)) # Octal
      next_char!
      while !eof? && is_octal?(get_char)
        value = value * 8 + get_char.to_i
        next_char!
      end
    elsif value == 0 && get_char == 'x' && is_hexadecimal?(get_char(1)) # Hexadecimal
      next_char!
      while !eof? && is_hexadecimal?(get_char)
        value = value * 16 + get_char.to_i(16)
        next_char!
      end
    end
    return new_token_with_value(INTEGER, value * sign)
  end

  def parse_string
    next_char! # Skip the opening quote
    value = ""
    while !eof? && get_char != '"'
      if get_char == '\\'
        next_char!
        escape_qualifier = get_char
        next_char!

        case escape_qualifier
        when "r"
          value += "\r"
        when "n"
          value += "\n"
        when "\\"
          value += "\\"
        when "0"
          value += "\0"
        when "b"
          value += "\b"
        when "f"
          value += "\f"
        when "t"
          value += "\t"
        when "v"
          value += "\v"
        when "u"
          codepoint = 0
          hexadecimal = false
          if get_char == 'x'
            hexadecimal = true
            next_char!
          end
          if get_char == '['
            next_char!
            while !eof? && get_char != ']'
              if !hexadecimal && is_numeric?(get_char)
                codepoint = codepoint * 10 + get_char.to_i
                next_char!
              elsif hexadecimal && is_hexadecimal?(get_char)
                codepoint = codepoint * 16 + get_char.to_i(16)
                next_char!
              else
                report_error "Unexpected character in unicode codepoint #{get_char}"
              end
            end
            if get_char != ']'
              report_error "Expected ] to close unicode codepoint. Got #{get_char}"
            end
            next_char!
          else
            report_error "Invalid unicode codepoint specification: #{get_char}"
          end
          value += codepoint.chr('UTF-8')
        else
          report_error "Invalid string escape character: #{escape_qualifier}"
        end
      else
        value += get_char
        next_char!
      end
    end
    if get_char != '"'
      report_error "Expected end of string. Got #{get_char}"
    end
    next_char!
    return new_token_with_value(STRING, value)
  end

  def new_token_with_value(type, value)
    Token.new(
        :type => type,
        :text => current_token_text,
        :value => value,

        :file => @file,
        :line => @token_start[:line],
        :column => @token_start[:column]
      )
  end

  def new_token(type)
    Token.new(
        :type => type,
        :text => current_token_text,
        :value => current_token_text,

        :file => @file,
        :line => @token_start[:line],
        :column => @token_start[:column]
      )
  end

  def parse
    tokens = []
    while @pos < @src.length
      start_token!
      if is_whitespace?(get_char)
        next_char!
      elsif get_char == "\n" || get_char == "\r"
        if get_char == "\r"
          next_char!
          if get_char == "\n" # Treat CRLF as one line ending
            next_char!
          end
        else
          next_char!
        end
        newline!
        tokens << new_token(EOL)
      elsif is_numeric?(get_char) || (get_char == '-' && is_numeric?(get_char(1)))
        tokens << parse_numeric
      elsif get_char == '"'
        tokens << parse_string
      elsif (get_char >= 'a' && get_char <= 'z') ||
            (get_char >= 'A' && get_char <= 'Z') ||
             get_char == '_' || 
             get_char.ord > 128
          tokens << parse_identifier
      elsif get_char == '<' && get_char(1) == '>'
        next_char!
        next_char!
        tokens << new_token(NOTEQ)
      elsif get_char == '<' && get_char(1) == '='
        next_char!
        next_char!
        tokens << new_token(LESSEQ)
      elsif get_char == '>' && get_char(1) == '='
        next_char!
        next_char!
        tokens << new_token(GREATEREQ)
      elsif get_char == ':' && get_char(1) == '='
        next_char!
        next_char!
        tokens << new_token(ASSIGN)
      else
        char = get_char
        next_char!
        tokens << new_token(char.to_sym)
      end
    end
    start_token!
    tokens << new_token(EOF)
    return tokens
  end
end