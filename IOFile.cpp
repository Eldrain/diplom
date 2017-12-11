#pragma once
#include "stdafx.h"
#include "Procs.cpp"
#include <fstream>

using std::string;

class IOFile {
	std::fstream file;

public:

	IOFile() {
		file.close();
	}
	
	bool loadData(Jobs &jobs, Procs &procs, string filename) {
		file.open(filename, std::fstream::in);

		if (file) {
			char buffer = file.get();
			int num = 0;

			while (buffer != '\n') {
				while (buffer != ' ' && buffer != '\n') {
					num = num * 10 + buffer - 48;
					buffer = file.get();
				}
				if (buffer == '\n')
					break;
				jobs.resize(num);
				num = 0;
				buffer = file.get();
			}
			procs.resize(num);
			num = 0;
			buffer = file.get();

			int nowCell = 0;
			while (buffer != '\n') {
				if (buffer == ' ') {
					jobs.SetJobTime(nowCell + 1, num);
					num = 0;
					nowCell++;
				}
				else
					num = num * 10 + buffer - 48;
				buffer = file.get();
			}
			jobs.SetJobTime(nowCell + 1, num);
			loadRelations(jobs);

			file.close();
			return true;
		}
		else
			return false;
	}

	bool loadRelations(Jobs &jobs) {

		if (file) {
			char buffer = file.get();
			int num = 0, numJob = 0;

			while (!file.eof()) {
				if (buffer == ' ') {
					jobs.AddJobFollow(numJob, num);
					num = 0;
				}
				else if (buffer == '\n') {
					if (num != 0)
						jobs.AddJobFollow(numJob, num);
					numJob++;
					num = 0;
				}
				else
					num = num * 10 + buffer - 48;
				buffer = file.get();
			}
			jobs.defineCountPrev();
			jobs.refresh();
			return true;
		}
		else
			return false;
	}
	
	~IOFile() {
		if (file)
			file.close();
	}
};