#pragma once

#include <chrono>



namespace benchmark
{


class Timer
{
public:
	Timer() {
		reset();
		reset_average();
	}


	void reset() noexcept
	{
		start_ = std::chrono::steady_clock::now();
	}

	void reset_average() noexcept
	{
		average_divisor_ = 0;
		average_total_ = 0;
	}


	double getms() noexcept
	{
		const auto end = std::chrono::steady_clock::now();
		const auto time = std::chrono::duration<double>(end - start_);

		const double ms = time.count();

		average_total_ += ms;
		average_divisor_++;

		return ms;
	}

	double get_average() const noexcept { return average_total_ / average_divisor_; }


private:
	std::chrono::steady_clock::time_point start_;

	double average_total_;
	double average_divisor_;
};


} // namespace benchmark