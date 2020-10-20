project('chmlib', 'c',
          version: '0.41.0',
    meson_version: '>= 0.49.0',
  default_options: [ 'warning_level=2',
                     'c_std=gnu11',
                   ],
)


config_h = configuration_data()
config_h.set_quoted('PACKAGE_VERSION', meson.project_version())
configure_file(
  output: 'chmlib-config.h',
  configuration: config_h,
)
add_project_arguments([
  '-I' + meson.build_root(),
], language: 'c')

if meson.get_compiler('c').get_id() == 'clang'
  add_global_arguments('-g' ,'-fsanitize=address', '-O0', '-Weverything', '-Wno-format-nonliteral', '-Wno-padded', '-Wno-conversion', language : 'c')
elif meson.get_compiler('c').get_id() == 'gcc'
  add_global_arguments('-g', '-O3', '-Wall', '-Wextra', '-Wpedantic', language: 'c')
endif

inc = include_directories('include')

subdir('include')
subdir('src')
subdir('tools')
subdir('test')

