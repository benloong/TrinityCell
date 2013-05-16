SET(CELL_SRC 
	main.cpp
	context.h
	context.cpp
	entity_system.h
	entity_system.cpp
	logger.h
	logger.cpp
	component_detail.h
	component.cpp
	component.h
	entity.h
	input_system.cpp
	input_system.h
	linear_mem_pool.h
	render_system.cpp
	render_system.h
	thread_pool.h
	timer.cpp
	timer.h
	type_identifier.h
)

ADD_EXECUTABLE(CellCore ${CELL_SRC})
