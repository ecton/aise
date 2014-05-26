class SyntaxTreeNode
  attr_accessor :token

  def initialize(params = {})
    params.each_pair do |key, value|
      self.send("#{key}=".to_sym,value)
    end
  end
end

class UnaryNode < SyntaxTreeNode
  attr_accessor :node
end

class BinaryNode < SyntaxTreeNode
  attr_accessor :left
  attr_accessor :right
end

class AndNode < BinaryNode

end

class OrNode < BinaryNode

end

class XorNode < BinaryNode

end

class LessThanNode < BinaryNode

end

class LessThanOrEqualNode < BinaryNode

end

class EqualNode < BinaryNode

end

class NotEqualNode < BinaryNode

end

class GreaterThanOrEqualNode < BinaryNode

end

class GreaterThanNode < BinaryNode

end

class AssignNode < BinaryNode

end

class AddNode < BinaryNode
end

class SubtractNode < BinaryNode
end

class MultiplyNode < BinaryNode
end

class DivideNode < BinaryNode
end

class PowerNode < BinaryNode

end

class NotNode < UnaryNode
end


class IdentifierNode < SyntaxTreeNode

end

class LiteralNode < SyntaxTreeNode

end