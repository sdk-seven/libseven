project('libseven', 'c',
  version: '0.23.0',
  license: 'MPL-2.0',
  meson_version: '>=0.64.0',
  default_options: ['warning_level=2', 'c_std=c99'])

if not meson.is_subproject()
  subdir('meson/toolchain')
else
  add_project_arguments('-masm-syntax-unified', language: 'c')
endif

sources = [
  'src/bios.c',
  'src/bios.s',
  'src/dma.s',
  'src/input.c',
  'src/irq.c',
  'src/irq_entry.s',
  'src/sram.s',
  'src/timer.c',
  'src/video/oam.s',
  'src/video/vram.c',
]

includes = ['include']

libseven = static_library(
  'seven',
  sources,
  include_directories: includes + ['src'],
  install: true)

install_subdir('include/seven', install_dir: get_option('includedir'))

libseven_dep = declare_dependency(
  include_directories: includes,
  link_with: libseven)

meson.override_dependency('libseven', libseven_dep)
