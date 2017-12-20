#pragma once
#include "stdafx.h"
#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <queue>
#include <condition_variable>

typedef std::function<void()> function;

namespace eld {
	class threadpool {//threadpool with std::thread

	public:
		threadpool(int max_count = 1): max_count_(max_count), cur_count_(0), i_(0) {}

		void add(function f) {

		}

		~threadpool() {

		}
	private:
		int max_count_;
		int cur_count_;
		int i_;
		std::vector<eld::threadpool::work_thread> work_thr_;

		class work_thread {
		public:
			work_thread() :thread(std::thread(&work_thread::run, this)), enabled(true) {}
			
		private:

			void run() {
				while (enabled) {
					

					while (!f_queue.empty()) {
						function f = f_queue.front();
						f();
						f_queue.pop();
					}
				}
			}

			std::thread thread;
			std::mutex mutex;
			std::condition_variable work;
			std::queue<function> f_queue;
			bool enabled;

		};
	};
}