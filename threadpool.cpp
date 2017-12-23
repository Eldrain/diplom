#pragma once
//#include "stdafx.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>
#include <memory>
typedef std::function<void()> fun;
namespace eld  {	
	class threadpool {
		//private:
		class workthread {
			public:
			workthread(int &number, std::condition_variable &cvv): n_(number), join_cv_(cvv)/*, mutex_()*/ {
				enable_ = true;//), 
				thread_ = std::thread(&workthread::run, this);
				f_queue = std::queue<fun>();
			}

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
					join_cv_.notify_one();
				}
			}

			bool is_empty() {
				std::unique_lock<std::mutex> locker(mutex_);
				return f_queue.empty();
			}

		private:
			int &n_;
			bool enable_;
			std::mutex mutex_;
			std::thread thread_;
			std::queue<fun> f_queue;
			std::condition_variable cv;
			std::condition_variable &join_cv_;
		};

		typedef std::shared_ptr<workthread> ptr;
	public:

		threadpool(int count = 1) : thread_count_(count), working_(0) {
			for (int i = 0; i < count; i++) {
				ptr ptr_th(new workthread(i, threadpool_cv_));
				threads_.push_back(ptr_th);
			}
		}

		bool add(fun f) {
			std::unique_lock<std::mutex> locker(th_count_mutex_);

			if (working_ == thread_count_) {
				th_count_mutex_.unlock();
				return false;
			}

			get_free_thread()->add_function(f);
			working_++;
			if (working_ == thread_count_) {
				working_ = 0;
			}
			//th_count_mutex_.unlock();

			return true;
		}

		void join() {
			int n = thread_count_ - 1;

			while (n != -1) {
				
				if (!threads_[n]->is_empty()) {
					std::unique_lock<std::mutex> locker(join_mutex_);
					threadpool_cv_.wait(locker, [&]() { return threads_[n]->is_empty(); });
					n = thread_count_;
				}
				n--;
			}
		}

		bool HaveEmpty() {
			if (get_free_thread() == nullptr) {
				return false;
			}
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
			return nullptr;
		}

		int thread_count_;
		int working_;
		std::vector<ptr> threads_;
		std::mutex th_count_mutex_;
		std::mutex join_mutex_;
		std::condition_variable threadpool_cv_;
	};
}