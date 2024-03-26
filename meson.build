project('libseven', 'c',
  version: '0.22.3',
  license: 'MPL-2.0',
  meson_version: '>=0.64.0',
  default_options: ['warning_level=2', 'c_std=c99'])

if not meson.is_subproject()
  subdir('meson/toolchain')
else
  add_project_arguments('-masm-syntax-unified', language: 'c')
endif

sources = [
  'src/hw/bios.c',
  'src/hw/bios.s',
  'src/hw/dma.s',
  'src/hw/input.c',
  'src/hw/irq.c',
  'src/hw/isr.s',
  'src/hw/sram.s',
  'src/hw/timer.c',
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
