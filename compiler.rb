require './ail.rb'

class Compiler
  def initialize(trees)
    @trees = trees
  end

  def compile
    instructions = []

    @trees.each do |tree|
      instructions += compile_tree(tree)
    end
    return instructions
  end

  def newid!
    @id = @id.to_i + 1
  end

  def compile_tree(tree)
    instructions, _ = compile_expression(tree)
    return instructions
  end

  def compile_binary_operation(node, instruction_class)
    instructions = []
    linstructions, lval = compile_expression(node.left)
    instructions += linstructions
    rinstructions, rval = compile_expression(node.right)
    instructions += rinstructions
    new_value = LocalValue.new(newid!)
    instructions << instruction_class.new(
      :result => new_value, 
      :lval => lval,
      :rval => rval
    )
    return instructions, new_value
  end

  def compile_expression(tree)
    puts "Compiling #{tree}"
    instructions = []
    result = nil
    case tree
    when AddNode
      oinstructions, result = compile_binary_operation(tree, AddInstruction)
      instructions += oinstructions
    when SubtractNode
      oinstructions, result = compile_binary_operation(tree, SubtractInstruction)
      instructions += oinstructions

    when MultiplyNode
      oinstructions, result = compile_binary_operation(tree, MultiplyInstruction)
      instructions += oinstructions

    when DivideNode
      oinstructions, result = compile_binary_operation(tree, DivideInstruction)
      instructions += oinstructions

    when LiteralNode
      result = LiteralValue.new(tree.token)
    else
      raise "Unimplemented #{tree}"
    end
    return instructions, result
  end
end