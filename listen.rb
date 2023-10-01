# frozen_string_literal: true

require 'listen'

listener = Listen.to('.') do |modified, _added, _removed|
  if modified.index("#{__dir__}/listen.rb")
    puts 'listen.rb modified, reloading...'
    exit system("ruby #{__dir__}/listen.rb")
  end

  modified = modified.filter { |f| f =~ /.*\.c/ }.map { |f| File.absolute_path(f) }
  next if modified.empty?

  modified.each do |file|
    puts '-' * 20
    puts "Modified: #{File.basename(file)} at #{Time.now.strftime('%H:%M:%S')}"
    # Build, run and remove the file.
    system("cd #{File.dirname(file)} && gcc #{file} -o #{File.basename(file, '.c')} && #{File.dirname(file)}/#{File.basename(file, '.c')}; rm #{File.dirname(file)}/#{File.basename(file, '.c')}")
    puts '-' * 20
    puts "\n"
  end
end

listener.start

puts "\nReady..."

sleep
