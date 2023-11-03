install(
    TARGETS gallow_exe
    RUNTIME COMPONENT gallow_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
