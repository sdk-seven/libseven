# Stability

Written for: libseven 0.24.0

Libseven follows [semver], but due to the large amount of different, independent
modules, stability will be tiered.

This page aims to document the current state of libseven's APIs with regards to stability.
The information here comes without any guarantee of being or remaining true.

## 1.0.0

For libseven 1.0.0, all public definitions present in the following headers will be considered
stable and subject to the typical semver rules.

Any definitions using the `_LIBSEVEN` prefix are not subject to stability rules.

Items with a filled checkbox are semi-stable and will receive only minimal changes before 1.0.0.

- [x] `<seven/attributes.h>`
- [x] `<seven/base.h>`
- [ ] `<seven/bios.h>`
- [x] `<seven/dma.h>`
- [ ] `<seven/input.h>`
- [x] `<seven/irq.h>`
- [x] `<seven/memory.h>`
- [x] `<seven/prelude.h>`
- [x] `<seven/timer.h>`
- [x] `<seven/types.h>`
- [ ] `<seven/video.h>`
- [ ] `<seven/waitstate.h>`

Anything not listed above will continue to be subject to pre-1.0.0 semver rules.

[semver]: https://semver.org
