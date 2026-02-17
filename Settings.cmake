set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (APPLE)
  set(CMAKE_INSTALL_RPATH "@loader_path/../lib")
elseif (UNIX)
  set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
endif ()

set(CPACK_GENERATOR "TGZ;ZIP;DEB")
set(CPACK_PACKAGE_CONTACT "kasefuchs@protonmail.com")
set(CPACK_PACKAGE_LICENSE "MIT")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CMakeDependentOption)
option(KUSAI_BUILD_APP "Build CLI app" OFF)
