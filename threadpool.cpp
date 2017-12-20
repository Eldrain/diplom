#pragma once
#include "stdafx.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>
//#include <shared_ptr>

typedef std::function<void()> fun;


namespace eld {
	class threadpool {
	//private:
		class workthread {
		public:
			workthread() : enable_(true), thread_(&workthread::run, this), f_queue() {}

			void add_function(fun f) {
				std::unique_lock<std::mutex> locker(mutex_);
				f_queue.push(f);
				//mutex_.unlock();
				cv.notify_one();
			}

			int get_queue_size() {
				std::unique_lock<std::mutex> locker(mutex_);
				int size = f_queue.size();

				return size;
			}

			~workthread() {
				enable_ = false;
				cv.notify_one();
				thread_.join();
			}

			void run() {
				while (enable_) {
					std::unique_lock<std::mutex> locker(mutex_);

					cv.wait(locker, [&]() { return !enable_ || !f_queue.empty(); });

					while (!f_queue.empty()) {
						fun fn = f_queue.front();

						locker.unlock();
						fn();
						locker.lock();
						f_queue.pop();
					}

				}
			}

		private:
			bool enable_;
			std::mutex mutex_;
			std::thread thread_;
			std::queue<fun> f_queue;
			std::condition_variable cv;

			
		};

		typedef std::shared_ptr<workthread> ptr;
	public:

		threadpool(int count = 1) : thread_count_(count), working_(0) {
			for (int i = 0; i < count; i++) {
				ptr ptr_th(new workthread());
				threads_.push_back(ptr_th);
			}
		}

		bool add(fun f) {
			th_count_mutex_.lock();

			if (working_ == thread_count_) {
				th_count_mutex_.unlock();
				return false;
			}

			get_free_thread()->add_function(f);
			working_++;
			th_count_mutex_.unlock();

			return true;
		}

		template<class _FN, class... _ARGS>
		bool async_task(_FN fn, _ARGS... args) {
			return add(std::bind(fn, args...));
		}

		~threadpool() {}

	private:
		ptr get_free_thread() {
			for (int i = 0; i < threads_.size(); i++) {
				
				if (threads_[i]->get_queue_size() == 0) {
					return threads_[i];
				}
			}
		}

		int thread_count_;
		int working_;
		std::vector<ptr> threads_;
		std::mutex th_count_mutex_;
		
	};
}