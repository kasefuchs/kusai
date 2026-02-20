function(kusai_add_library)
  cmake_parse_arguments(KUSAI_LIB
    ""
    "NAME"
    "SRCS;HDRS;DEPS"
    ${ARGN}
  )

  add_library(${KUSAI_LIB_NAME} ${KUSAI_LIB_SRCS})

  set_target_properties(${KUSAI_LIB_NAME} PROPERTIES
    OUTPUT_NAME "kusai_${KUSAI_LIB_NAME}"
  )

  if(KUSAI_LIB_HDRS)
    set(_hdr_paths "")
    foreach(h ${KUSAI_LIB_HDRS})
      list(APPEND _hdr_paths "${CMAKE_SOURCE_DIR}/include/kusai/${KUSAI_LIB_NAME}/${h}")
    endforeach()

    target_sources(${KUSAI_LIB_NAME} PUBLIC
      FILE_SET HEADERS
        TYPE HEADERS
        BASE_DIRS ${CMAKE_SOURCE_DIR}/include
        FILES ${_hdr_paths}
    )
  endif()

  target_include_directories(${KUSAI_LIB_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )

  if(KUSAI_LIB_DEPS)
    target_link_libraries(${KUSAI_LIB_NAME} PUBLIC ${KUSAI_LIB_DEPS})
  endif()
endfunction()
