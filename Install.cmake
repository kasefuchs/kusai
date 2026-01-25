include(GNUInstallDirs)

install(TARGETS proto graph markov textchain
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if (KUSAI_BUILD_SERVICE)
  install(TARGETS service
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
endif ()

if (KUSAI_BUILD_APP)
  install(TARGETS ${PROJECT_NAME}
    RUNTIME_DEPENDENCY_SET ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

  install(RUNTIME_DEPENDENCY_SET ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PRE_EXCLUDE_REGEXES
    "^ld-linux.*" "^libc\\.so" "^libm\\.so" "^libz\\.so" "^libdl\\.so"
    "^libutil\\.so" "^libgcc_s\\.so" "^libstdc\\+\\+\\.so"
    "^libpthread\\.so" "^librt\\.so" "^libresolv\\.so"
    "^libcrypto\\.so" "^libssl\\.so" "^libsystemd\\.so"
  )
endif ()

include(CPack)
