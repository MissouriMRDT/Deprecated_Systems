# Deployment Script to delete current contents of IA-GAANN directory and replace with _Site
# NOTE: Make sure you have net-sftp and highline gems installed.
# If not, run "gem install net-sftp" or "gem install highline"
require 'highline/import'
require 'rubygems'
require 'net/ssh'
require 'net/scp'

puts "============ MRDT SFTP Deployment Script ============"

# Connection information
host = "131.151.249.197"
local_directory = "_site/"
remote_directory = "/"

# User input is retrieved using the highline gem
username = ask("Please enter your username: ")
password = ask("Enter password: ") { |q| q.echo = false }

print "Initializing connection to: " + host + " ... "
begin
  Net::SCP.start( host, username, :password => password ) do|scp|
    Dir.foreach(local_directory) do |entry|
      if entry[0] == "." then
        next
      end
      if entry.include? "Gemfile" then
        next
      end
      if entry.include? "README" then
        next
      end
      scp.upload!( local_directory+"/"+entry, ".", :recursive => true )
    end
end
rescue Net::SSH::AuthenticationFailed
  puts "Authentication Failed!"
end
puts "Upload Finished!"
