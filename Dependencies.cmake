# Protobuf
find_package(protobuf CONFIG REQUIRED)

# gRPC
if (KUSAI_BUILD_SERVICE)
  find_package(gRPC CONFIG REQUIRED)
endif ()

# Abseil
find_package(absl CONFIG REQUIRED)

# CLI11
if (KUSAI_BUILD_APP)
  find_package(CLI11 CONFIG REQUIRED)
endif ()

# xxHash
find_package(xxHash CONFIG REQUIRED)

# Redis++
find_package(redis++ CONFIG REQUIRED)
