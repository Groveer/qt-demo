qt = import('qt5')
qt_dep = dependency('qt5', modules: ['Core','Concurrent'])
systemd_dep = dependency('libsystemd')
dtk_dep =dependency('dtkcore')

moc_files = qt.compile_moc(headers: 'logger.h',dependencies: qt_dep)

executable('qt-demo', ['main.cpp','logger.cpp', moc_files],
           dependencies : [qt_dep, systemd_dep, dtk_dep])
