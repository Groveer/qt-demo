qt = import('qt5')
qt_dep = dependency('qt5', modules: ['Core'])
systemd_dep = dependency('libsystemd')

executable('qt-demo', 'main.cpp',
           dependencies : [qt_dep, systemd_dep])
