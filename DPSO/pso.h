template <typename T>
class DPSO{
	int maxIt;
	public:
	T optimize();
	static T optimize(T*,void (*CostFunction)); 
};