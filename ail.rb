# Arithmetic Instructions
# add result, lval, rval
# sub result, lval, rval
# mul result, lval, rval
# div result, lval, rval

# Lookup Instruction, lval is optional
# lookup result, lval, rval


class Instruction
  attr_accessor :file, :line, :range

  def initialize(params = {})
    params.each_pair do |key, value|
      self.send("#{key}=".to_sym,value)
    end
  end
end

class Value

end

class LiteralValue < Value
  attr_accessor :token
  def initialize(token)
    self.token = token
  end
end

class LocalValue < Value
  attr_accessor :id
  def initialize(id)
    self.id = id
  end
end

class BinaryInstruction < Instruction
  attr_accessor :result, :lval, :rval
end

class AddInstruction < BinaryInstruction

end

class SubtractInstruction < BinaryInstruction
  
end

class MultiplyInstruction < BinaryInstruction
  
end

class DivideInstruction < BinaryInstruction
  
end