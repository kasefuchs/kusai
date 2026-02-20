include(GNUInstallDirs)

install(
  TARGETS proto graph markov textchain tokenizer
  EXPORT kusai
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

if (KUSAI_BUILD_APP)
  install(
    TARGETS kusai
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
endif ()

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/kusai-config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/kusai-config.cmake"
  @ONLY
)

install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/kusai-config.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/kusai"
)

install(
  EXPORT kusai
  FILE kusai-targets.cmake
  NAMESPACE kusai::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kusai
)

install(
  DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/proto/kusai/proto
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/kusai
  FILES_MATCHING PATTERN "*.pb.h"
)

include(CPack)
