project('prothesis-2', 'cpp')

add_global_arguments('--std=c++11', '-Werror', '-Wall', '-pedantic', '-g', language : 'cpp')
cxx_win = 'i686-w64-mingw32-g++'

source_files = files('src/data_manager.cpp', 'src/data_panel.cpp', 'src/main_frame.cpp', 'src/prothesis_app.cpp', 'src/utilities.cpp', 'src/panels/details_panel.cpp')

if meson.is_cross_build() == false

  message('Linux---------------------------------------------------------')
  wx_cxx_flags = run_command('wx-config', '--toolkit=gtk3 --cxxflags').stdout().strip().split(' ')
  wx_libs_tmp = run_command('wx-config', '--toolkit=gtk3 --libs').stdout().strip().split(' ')

  # wx-config --libs returns whitespace, which are split into empty elements
  # so we need to clean the wx_libs_tmp array
  wx_libs = []
  foreach item : wx_libs_tmp
    if item != ''
      wx_libs += item
    endif
  endforeach

  message('------------------- LINUX FLAGS START -----------------------------')
  message(wx_cxx_flags)
  message(wx_libs)
  message('------------------- LINUX FLAGS END   -----------------------------')

  executable('linux', source_files, cpp_args: wx_cxx_flags, link_args: [wx_libs, '-o', 'prothesis-2'])

else

  message('WINDOWS---------------------------------------------------------')
  wx_msw_config_file = '.win_wx_static_config'
  wx_msw_static_path = run_command('cat', wx_msw_config_file).stdout().strip()
  message(wx_msw_static_path)

  wx_win_cxx_flags = run_command(wx_msw_static_path + '/wx-config', '--cxxflags').stdout().strip().split(' ')
  wx_win_libs_tmp = run_command(wx_msw_static_path + '/wx-config', '--libs').stdout().strip().split(' ')

  wx_win_libs = []
  foreach item : wx_win_libs_tmp
    if item != ''
      wx_win_libs += item
    endif
  endforeach

  message('------------------- WINDOWS FLAGS START -----------------------------')
  message(wx_win_cxx_flags)
  message(wx_win_libs)
  message('------------------- WINDOWS FLAGS END   -----------------------------')

  executable('windows', source_files, cpp_args: [wx_win_cxx_flags], link_args: ['--static', wx_win_libs, '-o', 'prothesis-2.exe'])

endif
