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

class ArgumentListNode < SyntaxTreeNode
	attr_accessor :arguments
end

class FunctionCallNode < SyntaxTreeNode
	attr_accessor :root
	attr_accessor :arguments
end

class IndexNode < SyntaxTreeNode
	attr_accessor :root
	attr_accessor :arguments
end

class LookupNode < SyntaxTreeNode
	attr_accessor :root
	attr_accessor :field
end

class ArrayLiteral < SyntaxTreeNode
  attr_accessor :nodes
end

class MapLiteral < SyntaxTreeNode
  attr_accessor :nodes
end

class KeyValuePairNode < SyntaxTreeNode
  attr_accessor :key
  attr_accessor :value
end



# Statements

class Statement < SyntaxTreeNode

end

class DeclarationStatement < Statement

end

class CodeStatement < Statement

end

class StatementList < SyntaxTreeNode
  attr_accessor :statements
end

class DeclarationStatementList < StatementList

end

class CodeStatementList < StatementList

end

class IfStatement < CodeStatement
  attr_accessor :condition
  attr_accessor :body
  attr_accessor :else_if_statement # IfStatement or nil
end

class WhileStatement < CodeStatement
  attr_accessor :condition
  attr_accessor :body
end

class ForStatement < CodeStatement
  attr_accessor :variable
  attr_accessor :start
  attr_accessor :end
  attr_accessor :step
  attr_accessor :body
end

class ForEachStatement < CodeStatement
  attr_accessor :variable
  attr_accessor :variable2
  attr_accessor :collection
  attr_accessor :body
end

class FundamentalStatement < CodeStatement
  attr_accessor :if_condition
end

class AssignmentStatement < FundamentalStatement
  attr_accessor :lhs
  attr_accessor :rhs
end

class CallStatement < FundamentalStatement
  attr_accessor :expr
end

class ReturnStatement < FundamentalStatement
  attr_accessor :expr
end

