# Protobuf
include(FindProtobuf)

# Abseil
find_package(absl REQUIRED)

# pugixml
find_package(pugixml REQUIRED)

# PkgConfig
find_package(PkgConfig REQUIRED)

# xxHash
pkg_check_modules(XXHASH REQUIRED libxxhash)
