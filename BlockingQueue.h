#pragma once

#include <deque>
#include <string>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

typedef boost::mutex MutexLock;
typedef boost::condition_variable Condition;
typedef boost::mutex::scoped_lock ScopedLock;

class BlockingQueue
{
public:
	BlockingQueue() {}
	~BlockingQueue() {}

	void put(const std::string &s)
	{
		ScopedLock lock(mutex_);
		queue_.push_back(s);
		notEmpty_.notify_one();
	}

	std::string take()
	{
		ScopedLock lock(mutex_);
		while (queue_.empty()) {
			notEmpty_.wait(lock);
		}

		std::string res(queue_.front());
		queue_.pop_front();
		return res;
	}

	void take_all(std::deque<std::string> &d)
	{
		ScopedLock lock(mutex_);
		while (queue_.empty()) {
			notEmpty_.wait(lock);
		}

		d.swap(queue_);
	}

	size_t size() const
	{
		ScopedLock lock(mutex_);
		return queue_.size();
	}
	
private:
	mutable MutexLock mutex_;
	Condition notEmpty_;
	std::deque<std::string> queue_;

	BlockingQueue(const BlockingQueue &rhs);
	void operator=(const BlockingQueue &rhs);
};
