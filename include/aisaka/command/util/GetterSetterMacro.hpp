#define GETTER_SETTER(fname, _class, type)                    \
	[[nodiscard]] auto _class::fname() const noexcept->type { \
		return _##fname;                                      \
	}                                                         \
	auto _class::fname(type fname) noexcept->_class& {        \
		_##fname = fname;                                     \
		return *this;                                         \
	}

#define GETTER_SETTER_ARG(fname, _class, type, param_type)    \
	[[nodiscard]] auto _class::fname() const noexcept->type { \
		return _##fname;                                      \
	}                                                         \
	auto _class::fname(param_type fname) noexcept->_class& {  \
		_##fname = fname;                                     \
		return *this;                                         \
	}
