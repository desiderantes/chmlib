test_exe = executable('test_exe', 'test.c',
	include_directories : inc,
	dependencies: chmlib_deps,
	link_with : chmlib_lib)
#Disabled, current code includes no test files
php_test_files = files('data/php_manual_en.chm')
jquery_test_files = files('data/jquery-ui-1.7-reference.chm')
test('mid_size_test', test_exe, args: php_test_files)
test('small_size_test', test_exe, args: jquery_test_files)

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

