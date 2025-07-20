# frozen_string_literal: true

require "bundler/gem_tasks"
require "minitest/test_task"

Minitest::TestTask.create


task :compile do
  puts "Compiling extension"
  `cd ext/voronoi-rb && make clean`
  `cd ext/voronoi-rb && ruby extconf.rb`
  `cd ext/voronoi-rb && make`
  puts "Done"
end

task default: :test
