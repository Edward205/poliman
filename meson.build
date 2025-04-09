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


sdl_opts = cmake.subproject_options()
sdl_opts.add_cmake_defines({
	'CMAKE_POSITION_INDEPENDENT_CODE': 'ON',
	'CMAKE_BUILD_TYPE': 'Release',
	'SDL_CCACHE': 'ON',
	'SDL_TESTS': 'OFF',
	'SDL_SHARED': 'OFF',
	'SDL_STATIC': 'ON',
	'SDL_STATIC_PIC': 'ON',
	'SDL_TEST_LIBRARY': 'OFF',
	'SDL_CPU_X64': 'ON',

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
	'SDL_RENDER_VULKAN': 'ON',
	'SDL_WAYLAND': 'ON',
	'SDL_WAYLAND_SHARED': 'ON',
	'SDL_WAYLAND_LIBDECOR': 'ON',
	'SDL_WAYLAND_LIBDECOR_SHARED': 'ON',
	'SDL_X11': 'ON',
	'SDL_X11_SHARED': 'ON',
	'SDL_LIBUDEV': 'ON',
    'SDL_KMSDRM': 'ON',
    'SDL_KMSDRM_SHARED': 'ON'
})

sdl3_dep = cmake.subproject('sdl3', options: sdl_opts).dependency('SDL3-static')


pacman_source_files = [
    'src/main.cpp'
]

pacman_dependencies = [
    sdl3_dep,
]


executable(
    'pacman',
    [pacman_source_files],
    dependencies: pacman_dependencies,
)