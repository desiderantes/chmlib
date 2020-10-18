api_version = '0.1'

chmlib_sources = files(
  'chm_lib.c',
  'lzx.c',
)

chmlib_deps = [
  dependency('glib-2.0', version: '>= 2.50'),
  dependency('threads'),
]

chmlib_lib = library('chmlib-' + api_version,
  chmlib_sources,
  include_directories : inc,
  dependencies: chmlib_deps,
  install: true,
)

pkg = import('pkgconfig')

pkg.generate(
  description: 'A small library designed for accessing MS ITSS files (CHM)',
    libraries: chmlib_lib,
         name: 'chmlib',
     filebase: 'chmlib-' + api_version,
      version: meson.project_version(),
      subdirs: 'chmlib',
     requires: 'glib-2.0',
  install_dir: join_paths(get_option('libdir'), 'pkgconfig')
)
gnome = import('gnome')
gnome.generate_gir(chmlib_lib,
  sources : chmlib_sources + chmlib_headers,
  nsversion : '1.0',
  namespace : 'Chm',
  symbol_prefix : 'chm_',
  identifier_prefix : 'Chm',
  include_directories: inc,
  export_packages : 'chm-glib',
  includes : ['GObject-2.0'],
  install : true
)
