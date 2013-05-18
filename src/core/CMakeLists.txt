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
	component_roster_base.h
	entity.h
	fixed_size_pool.h
	hierarchy.h
	hierarchy.cpp
	input_system.cpp
	input_system.h
	render_system.cpp
	render_system.h
<<<<<<< HEAD
=======
	thread_pool.h
	timer.cpp
	timer.h
>>>>>>> 52e4340eccc1b12141f0261ef39e4409bde8d461
)

ADD_EXECUTABLE(CellCore ${CELL_SRC})
