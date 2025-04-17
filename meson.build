project(
    'pacman',
    ['c', 'cpp'],
    default_options: [
        # 'cpp_std=gnu++20',
        'warning_level=2',
    ],
)

host = host_machine.system()

cmake = import('cmake')
cpp = meson.get_compiler('cpp')

sdl_opts = cmake.subproject_options()
sdl_opts.add_cmake_defines({
    'CMAKE_POSITION_INDEPENDENT_CODE': 'ON',
    # 'CMAKE_BUILD_TYPE': buildtype,
    'SDL_TESTS': 'OFF',
    'SDL_SHARED': 'OFF',
    'SDL_STATIC': 'ON',
    'SDL_STATIC_PIC': 'ON',
    'SDL_TEST_LIBRARY': 'OFF',

    'SDL_AUDIO': 'ON',
    'SDL_VIDEO': 'ON',
    'SDL_RENDER': 'ON',
    'SDL_HIDAPI': 'ON',

    'SDL_OPENGL': 'ON',
    'SDL_OPENGLES': 'ON',
    'SDL_VULKAN': 'ON',
    'SDL_RENDER_VULKAN': 'ON',

    'SDL_CAMERA': 'OFF',
    'SDL_JOYSTICK': 'OFF',
    'SDL_HAPTIC': 'OFF',
    'SDL_POWER': 'OFF',
    'SDL_SENSOR': 'OFF',
    'SDL_DIALOG': 'OFF',
    'SDL_OFFSCREEN': 'OFF',
})

# Linux specific options
if host == 'linux'
  sdl_opts.add_cmake_defines({
    'SDL_WAYLAND': 'ON',
    'SDL_X11': 'ON',
    'SDL_LIBUDEV': 'ON',
    'SDL_KMSDRM': 'ON',
  })
endif

sdl3_proj = cmake.subproject('sdl3', options: sdl_opts)
sdl3_dep = sdl3_proj.dependency('SDL3-static')

pacman_source_files = [
	'src/sdl_uclibc_stub.c',

    'include/defines.h',
    'include/pacman_game.h',
    'include/entity.h',
    'include/player.h',
    'include/ghost.h',
    'include/ui.h',

    'src/main.cpp',
    'src/pacman_game.cpp',
    'src/entity.cpp',
    'src/player.cpp',
    'src/ghost.cpp',
    'src/ui.cpp',
]

pacman_dependencies = [
    sdl3_dep,
]

# Windows specific dependencies
if host == 'windows'
    winmm_dep = cpp.find_library('winmm')
    setupapi_dep = cpp.find_library('setupapi')
    imm32_dep = cpp.find_library('imm32')
    version_dep = cpp.find_library('version')
    pacman_dependencies += [
        winmm_dep,
        setupapi_dep,
        imm32_dep,
        version_dep,
    ]
endif

# macOS specific dependencies
if host == 'darwin'
  coreaudio_dep = dependency('CoreAudio')
  audiotoolbox_dep = dependency('AudioToolbox')
  corefoundation_dep = dependency('CoreFoundation')
  coregraphics_dep = dependency('CoreGraphics')
  corevideo_dep = dependency('CoreVideo')
  iokit_dep = dependency('IOKit')
  forcefeedback_dep = dependency('ForceFeedback')
  carbon_dep = dependency('Carbon')
  metal_dep = dependency('Metal')
  foundation_dep = dependency('Foundation')
  appkit_dep = dependency('AppKit')
  uniformtypeidentifiers_dep = dependency('UniformTypeIdentifiers')
  quartzcore_dep = dependency('QuartzCore')

  pacman_dependencies += [
      coreaudio_dep,
      audiotoolbox_dep,
      corefoundation_dep,
      coregraphics_dep,
      corevideo_dep,
      iokit_dep,
      forcefeedback_dep,
      carbon_dep,
      metal_dep,
      foundation_dep,
      appkit_dep,
      uniformtypeidentifiers_dep,
      quartzcore_dep, 
  ]
endif

executable(
    'pacman',
    pacman_source_files,
    dependencies: pacman_dependencies,
)