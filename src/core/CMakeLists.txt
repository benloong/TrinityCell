SET(CELL_SRC main.cpp
context.h
context.cpp
entity_system.h
entity_system.cpp
logger.h
logger.cpp
)

ADD_EXECUTABLE(CellCore ${CELL_SRC})
