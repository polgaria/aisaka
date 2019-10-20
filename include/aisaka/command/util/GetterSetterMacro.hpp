#define GETTER_SETTER(fname, _class, type)                                 \
	[[nodiscard]] type _class::fname() const noexcept { return _##fname; } \
	_class& _class::fname(type fname) noexcept {                           \
		_##fname = fname;                                                  \
		return *this;                                                      \
	}

#define GETTER_SETTER_ARG(fname, _class, type, param_type)                 \
	[[nodiscard]] type _class::fname() const noexcept { return _##fname; } \
	_class& _class::fname(param_type fname) noexcept {                     \
		_##fname = fname;                                                  \
		return *this;                                                      \
	}
