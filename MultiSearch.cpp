#include "stdafx.h"
#include "MultiSearch.h"


MultiSearch::MultiSearch(int countThreads)
{
	for (int i = 0; i < countThreads; i++)
		threads.push_front(*new std::thread());
}




MultiSearch::~MultiSearch()
{
}
