qt = import('qt5')
qt_dep = dependency('qt5', modules: ['Core'])
dtk_dep = dependency('dtkwidget')

lib = library('demo', 'lib/demo.cpp',
             dependencies : qt_dep,)

executable('qt-demo', 'main.cpp',
           dependencies : [qt_dep, dtk_dep],
           link_with : lib)
