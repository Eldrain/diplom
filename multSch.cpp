#include <clocale>
#include "MethodSet.cpp"
#include "Generator.cpp"
#include "test.cpp"
#include "threadpool.cpp"

using namespace std;

void innerPrint(Solution *res) {
	cout << endl;
	res->print();
};

int main()
{
	setlocale(0, "");	
	test testModule;
	testModule.timeTest(10, 21, 3, 50, 7, innerPrint);
	//testModule.testHook();
	/*Task task;
	Generator gen;
	MethodSet set;

	set.addSortOut();
	set.addAbBound();
	gen.GenerateTree(task, 10, 50, 6);
	task.ResizeProcs(3);

	cout << endl;
	set.solve(innerPrint, task);*/
	//test test1;
	//test1.timeTest(15, 30, 3, 50, 10);
	
	getchar();
	return 0;
}