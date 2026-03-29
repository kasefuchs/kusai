include(FetchContent)

# Abseil
find_package(absl CONFIG REQUIRED)

# CLI11
if (KUSAI_BUILD_APP)
  find_package(CLI11 CONFIG REQUIRED)
endif ()

# nlohmann json
find_package(nlohmann_json CONFIG REQUIRED)

# xxHash
find_package(xxHash CONFIG REQUIRED)

# Pybind11
if (KUSAI_BUILD_PYTHON)
  find_package(pybind11 CONFIG REQUIRED)

  FetchContent_Declare(
    pybind11_json
    GIT_REPOSITORY https://github.com/pybind/pybind11_json.git
    GIT_TAG        master
  )
  FetchContent_MakeAvailable(pybind11_json)
endif()
