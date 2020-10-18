test_exe = executable('test_exe', 'test.c',
	include_directories : inc,
	dependencies: chmlib_deps,
	link_with : chmlib_lib)
#Disabled, current code includes no test files
#test('main_test', test_exe)

valgrind = find_program('valgrind', required : false)
if valgrind.found()
  add_test_setup('valgrind',
    exe_wrapper : [valgrind,
      '--tool=memcheck',
      '--leak-check=full',
      '--trace-children=yes',
      '--show-possibly-lost=no',
      '--leak-resolution=high',
      '--num-callers=20',
      '--error-exitcode=1',
      ])
endif

