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
