Expression::Expression(const Expression& that) :
	type(that.type),
	value(that.value)
	{}

Expression::Expression() :
	type(-1),
	value()
	{}

Expression::~Expression() {
	
};