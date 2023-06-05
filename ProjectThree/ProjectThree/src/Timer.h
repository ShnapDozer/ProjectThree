#pragma once

#include <thread>
#include <atomic>

#include "Object.h"

namespace pt {

	template <class ClassName>
	class Timer : public Object{
	public:
		Timer() {}
		~Timer() { this->stop(); }

		void start(long long interval, ClassName* callBackClass, void(ClassName::* callBackFunction)()) {

			if (this->isExecute()) {
				this->stop();
			}

			_execute.store(true, std::memory_order_release);

			_thread = std::thread([this, interval, callBackClass, callBackFunction]() {
				while (this->isExecute()) {
					(callBackClass->*callBackFunction)();
					std::this_thread::sleep_for(std::chrono::milliseconds(interval));
				}
			});
		}

		void stop() {
			_execute.store(true, std::memory_order_release);

			if (_thread.joinable()) {
				_thread.join();
			}
		}

		bool isExecute() {
			return _execute.load(std::memory_order_acquire);
		}

	private:
		std::atomic<bool> _execute;
		std::thread _thread;
	};
}
