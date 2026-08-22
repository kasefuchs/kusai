if (KUSAI_BUILD_PYTHON)
  add_subdirectory(python)
endif ()

if (KUSAI_BUILD_WASM)
  add_subdirectory(wasm)
endif ()
