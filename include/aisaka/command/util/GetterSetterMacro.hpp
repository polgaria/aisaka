#define GETTER_SETTER(fname, _class, type)                         \
	const type _class::fname() const noexcept { return _##fname; } \
	_class& _class::fname(const type fname) noexcept {             \
		_##fname = fname;                                          \
		return *this;                                              \
	}

#define GETTER_SETTER_ARG(fname, _class, type, param_type)         \
	const type _class::fname() const noexcept { return _##fname; } \
	_class& _class::fname(const param_type fname) noexcept {       \
		_##fname = fname;                                          \
		return *this;                                              \
	}
