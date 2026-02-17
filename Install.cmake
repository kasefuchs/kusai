include(GNUInstallDirs)

install(TARGETS proto graph markov textchain tokenizer
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if (KUSAI_BUILD_APP)
  install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
endif ()

include(CPack)
