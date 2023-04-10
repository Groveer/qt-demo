# QtDemo

qt demo and test

# Dependencies

## Build dependencies

- pkg-config
- meson
- Qt6(>= 6.2.0) with modules:
  - qt6-base

## Runtime dependencies

# Installation

## Build from source code

1. Make sure you have installed all dependencies.

2. Build:

```
$ cd qt-demo
$ meson setup build
$ meson compile -C build
```

3. Install:

```
$ meson configure build --prefix=/usr
$ meson install -C build
```

# License

qt-demo is licensed under GPLv3.
