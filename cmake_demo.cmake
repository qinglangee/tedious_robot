function (argument_tester arg)
 
message(STATUS "ARGN: ${ARGN}")
 
message(STATUS "ARGC: ${ARGC}")
 
message(STATUS "ARGV: ${ARGV}")
 
message(STATUS "ARGV0: ${ARGV0}")
 
 
list(LENGTH ARGV argv_len)
 
message(STATUS "length of ARGV: ${argv_len}")
 
set(i 0)
 
while( i LESS ${argv_len})
 
list(GET ARGV ${i} argv_value)
 
message(STATUS "argv${i}: ${argv_value}")

if(i LESS 2)
  # then section.
  message(STATUS "i less 2")
elseif(i LESS 3)
  # elseif section.
  message(STATUS "i less 3")
else()
  # else section.
  message(STATUS "i not less 3")
endif()
 
 
math(EXPR i "${i} + 1")
 
endwhile()


 
 
 
endfunction ()


# test
# argument_tester(arg0 arg1 arg2 arg3)