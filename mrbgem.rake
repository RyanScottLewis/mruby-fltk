MRuby::Gem::Specification.new('mruby-fltk') do |spec|
  spec.authors = 'Ryan Scott Lewis <ryanscottlewis@lewis-software.com>'
  spec.license = 'MIT'
  spec.summary = 'FLTK 1.3.2 GUI binding.'

  spec.cxx.flags << "-std=c++0x -fpermissive #{`fltk-config --cflags`.delete("\n\r")}"
  if ENV['OS'] == 'Windows_NT'
    fltk_libs = "#{`fltk-config --use-images --ldflags`.delete("\n\r").gsub(/ -mwindows /, ' ')} -lgdi32 -lstdc++".split(" ")
  else
    fltk_libs = "#{`fltk-config --use-images --ldflags`.delete("\n\r")} -lstdc++".split(" ")
  end
  flags = fltk_libs.reject {|e| e =~ /^-l/ }
  libraries = fltk_libs.select {|e| e =~ /-l/ }.map {|e| e[2..-1] }
  spec.linker.flags << flags
  spec.linker.libraries << libraries
end
