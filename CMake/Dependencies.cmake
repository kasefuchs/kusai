# Abseil
find_package(absl CONFIG REQUIRED)

# CLI11
if (KUSAI_BUILD_APP)
  find_package(CLI11 CONFIG REQUIRED)
endif ()

# pugixml
find_package(pugixml CONFIG REQUIRED)

# xxHash
find_package(xxHash CONFIG REQUIRED)
