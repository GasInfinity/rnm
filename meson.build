project('rnm', 'cpp', version: '0.0.0', default_options: ['cpp_std=c++26'])

gtest_dep = dependency('gtest', main: true, required: true)

rnm = include_directories('include')

test_sources = files(
  'tests/vec_tests.cpp',
  'tests/mat_tests.cpp',
)

tests = executable('rnm-tests', test_sources,
  dependencies: [gtest_dep],
  include_directories: rnm,
  cpp_args: ['-g'],
)

test('rnm-tests', tests)
