SET(CELL_SRC 
	component.cpp
	component.h
	component_detail.h
	component_roster_base.h
	component_system.cpp
	component_system.h
	component_types.h
	context.cpp
	context.h
	entity.h
	entity_system.cpp
	entity_system.h
	fixed_size_pool.h
	hierarchy.cpp
	hierarchy.h
	input_system.cpp
	input_system.h
	logger.cpp
	logger.h
	main.cpp
	render_system.cpp
	render_system.h
	timer.cpp
	timer.h
)

ADD_EXECUTABLE(CellCore ${CELL_SRC})
