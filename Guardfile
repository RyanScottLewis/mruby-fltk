guard :shell do
  watch(%r{(src|include)/.+\.(c|cpp|h)$}) do |match|
    file = match[0]
    puts "Formatting #{file}"
    system("clang-format -i #{file}")
  end
end
