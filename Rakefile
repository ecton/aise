require 'yaml'
require './lexer.rb'
require './parser.rb'
require 'pp'

task :test => [:test_lexer] do |task, args|

end

task :test_lexer do |task, args|
  Dir["./tests/lexer/*.yaml"].each do |file|
    test = YAML.load(open(file).read)
    puts "Running test #{test[:name]}"
    tokens = Lexer.new(test[:src]).parse
    if test[:tokens]
      pass = true
      tokens.each_with_index do |tk, idx|
        if tk.to_h != test[:tokens][idx]
          puts "Expected #{tk.to_h} but got #{test[:tokens][idx]}"
          pass = false
          break
        end
      end
      if pass
        puts "- Passed."
      else
        puts "- Failed!"
      end
    else
      puts "- No tokens... here they are"
      puts YAML.dump(tokens.collect{|t| t.to_h})
    end
  end
end

task :test_parser do |task, args|
  tokens = Lexer.new("a and 3 or 4.5 < 3 <= 4 >= a > 4 <> 2 := 3 xor false ^ 2 * 3 and").parse
  p = Parser.new(tokens)
  PP.pp(p.parse)
end