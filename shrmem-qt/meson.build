qt = import('qt5')
server_dep = dependency('qt5', modules: ['Core', 'Gui'])
client_dep = dependency('qt5', modules: ['Core', 'Widgets'])

moc_files = qt.compile_moc(headers: ['sharedimage.h'],
  dependencies: server_dep)

executable('server', ['server.cpp', 'sharedimage.cpp', moc_files],
           dependencies : server_dep,)

executable('client', ['client.cpp', 'sharedimage.cpp', moc_files],
           dependencies : client_dep,)

