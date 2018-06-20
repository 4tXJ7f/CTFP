#ifndef FACT_HPP
#define FACT_HPP

/*
 * base fact class
 */
class Fact {
public:
	enum Op {
		FAdd32, FAbs32, FOlt32,
		FAdd64, FAbs64, FOlt64
	};

	std::vector<void *> vars;
	std::vector<Range> ranges;

	Op op;
	std::vector<Fact *> args;

	Fact() { };
	Fact(Op op) { op = op; }
	Fact(Range init) { ranges.push_back(init); }
	Fact(Range64 init) { ranges.push_back(Range(init)); }
	~Fact() {}

	double Lower() const;
	double Upper() const;
	std::string Str() const;
	void Dump() const;

	static Fact FltAbs64(Fact &in);

	static Fact FltOLT64(Fact &lhs, Fact &rhs, void *var);

	static double Next64(double val) { return std::nextafter(val, INFINITY); }
	static double Prev64(double val) { return std::nextafter(val, -INFINITY); }
};


/*
 * pass class
 */
class Pass {
public:
	llvm::Function *func;
	std::map<llvm::Value *, Fact> map;

	Pass() = delete;
	Pass(llvm::Function *init) { func = init; }
	~Pass() {}

	void Run();
	void Add(llvm::Value *value, const Fact &fact);

	Fact &Get(llvm::Value *value);
	std::pair<Fact::Op, std::vector<Fact *>> Info(llvm::Instruction &inst);

	void Dump() const;
};

#endif
