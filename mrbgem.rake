MRuby::Gem::Specification.new('mruby-fltk') do |spec|
  spec.authors = 'Ryan Scott Lewis <ryanscottlewis@lewis-software.com>'
  spec.license = 'MIT'
  spec.summary = 'FLTK 1.3.2 GUI binding.'

  spec.cxx.flags << "#{`fltk-config --cflags`.delete("\n\r")}"
  if ENV['OS'] == 'Windows_NT'
    fltk_libs = "#{`fltk-config --use-images --ldflags`.delete("\n\r").gsub(/ -mwindows /, ' ')} -lgdi32 -lstdc++".split(" ")
  else
    fltk_libs = "#{`fltk-config --use-images --ldflags`.delete("\n\r")} -lstdc++".split(" ")
  end
  flags = fltk_libs.reject {|e| e =~ /^-l/ }
  libraries = fltk_libs.select {|e| e =~ /-l/ }.map {|e| e[2..-1] }
  
  spec.linker.flags << flags
  spec.linker.libraries << libraries
  
  # Compile mrb_fltk before any others
  # source_files = Dir.glob("#{dir}/src/*.{c,cpp,m,asm,S}")
  # mrb_fltk_path = source_files.find { |path| path =~ /mrb_fltk\.cpp$/ }
  # source_files.delete(mrb_fltk_path)
  # source_files.unshift( mrb_fltk_path )
  # 
  # spec.objs = source_files.map { |f| objfile(f.relative_path_from(dir).pathmap("#{build_dir}/%X")) }
  
end
