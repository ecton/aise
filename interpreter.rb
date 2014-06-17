class Interpreter
  def initialize(instructions)
    @instructions = instructions
    @state = {}
  end

  def get_value(value)
    if value.is_a?(LiteralValue)
      return value.token.value
    else
      return @state[value.id]
    end
  end

  def interpret_add(instruction)
    lval = get_value(instruction.lval)
    rval = get_value(instruction.rval)
    @state[instruction.result.id] = lval + rval
  end

  def interpret_div(instruction)
    lval = get_value(instruction.lval)
    rval = get_value(instruction.rval)
    @state[instruction.result.id] = lval / rval
  end

  def interpret_sub(instruction)
    lval = get_value(instruction.lval)
    rval = get_value(instruction.rval)
    @state[instruction.result.id] = lval - rval
  end

  def interpret_mul(instruction)
    lval = get_value(instruction.lval)
    rval = get_value(instruction.rval)
    @state[instruction.result.id] = lval * rval
  end

  def interpret
    last_result = nil
    @instructions.each do |instruction|
      case instruction
      when AddInstruction
        last_result = interpret_add(instruction)
      when SubtractInstruction
        last_result = interpret_sub(instruction)
      when MultiplyInstruction
        last_result = interpret_mul(instruction)
      when DivideInstruction
        last_result = interpret_div(instruction)
      else
        raise "Unimplemented #{instruction}"
      end
    end
    return last_result
  end
end