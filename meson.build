project(
    'pacman',
    ['c', 'cpp'],
    default_options: [
        'cpp_std=gnu++20',
        'warning_level=2',
    ],
)

cmake = import('cmake')
cpp = meson.get_compiler('cpp')

# Windows libraries
winmm_dep = cpp.find_library('winmm')
setupapi_dep = cpp.find_library('setupapi')
imm32_dep = cpp.find_library('imm32')
version_dep = cpp.find_library('version')

sdl_opts = cmake.subproject_options()
sdl_opts.add_cmake_defines({
    'CMAKE_POSITION_INDEPENDENT_CODE': 'ON',
    'CMAKE_BUILD_TYPE': 'Release',
    'SDL_TESTS': 'OFF',
    'SDL_SHARED': 'OFF',
    'SDL_STATIC': 'ON',
    'SDL_TEST_LIBRARY': 'OFF',
    'SDL_AUDIO': 'OFF',
    'SDL_CAMERA': 'OFF',
    'SDL_JOYSTICK': 'OFF',
    'SDL_HAPTIC': 'OFF',
    'SDL_HIDAPI': 'ON',
    'SDL_POWER': 'OFF',
    'SDL_SENSOR': 'OFF',
    'SDL_DIALOG': 'OFF',
    'SDL_VIDEO': 'ON',
    'SDL_OFFSCREEN': 'OFF',
    'SDL_RENDER': 'OFF',
    'SDL_OPENGL': 'ON',
    'SDL_OPENGLES': 'ON',
    'SDL_VULKAN': 'ON',
    'SDL_WAYLAND': 'OFF',
    'SDL_X11': 'OFF',
    'SDL_LIBUDEV': 'OFF',
    'SDL_KMSDRM': 'OFF'
})

sdl3_proj = cmake.subproject('sdl3', options: sdl_opts)
sdl3_dep = sdl3_proj.dependency('SDL3-static')

pacman_source_files = [
    'src/main.cpp',
	'src/sdl_uclibc_stub.c'
]

pacman_dependencies = [
    sdl3_dep,
    winmm_dep,
    setupapi_dep,
    imm32_dep,
    version_dep,
]

executable(
    'pacman',
    pacman_source_files,
    dependencies: pacman_dependencies,
    install: true
)