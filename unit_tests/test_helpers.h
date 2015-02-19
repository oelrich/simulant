#pragma once

#include <sstream>
#include <vector>


template<> static std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<std::vector<double>>(const std::vector<double> & data)
{
	std::wstringstream ss;
	ss << L"std::vector<double> { ";
	size_t ii{ 0 };
	while (ii < (data.size() - 1))
	{
		ss << data[ii] << ", ";
		++ii;
	}
	if (ii < data.size())
	{
		ss << data[ii];
	}
	ss << " }";

	return ss.str();
}

//std::vector<std::pair<double, double>>



template<> static std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<std::vector<std::pair<double, double>>>(const std::vector<std::pair<double, double>> & data)
{
	std::wstringstream ss;
	ss << L"std::vector<std::pair<double, double>> { ";
	size_t ii{ 0 };
	while (ii < (data.size() - 1))
	{
		ss << "{ " << data[ii].first << ", " << data[ii].second << " }, ";
		++ii;
	}
	if (ii < data.size())
	{
		ss << "{ " << data[ii].first << ", " << data[ii].second << " }";
	}
	ss << " }";

	return ss.str();
}
template<> static std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<std::vector<size_t>>(const std::vector<size_t> & data)
{
	std::wstringstream ss;
	ss << L"std::vector<size_t> { ";
	size_t ii{ 0 };
	while (ii < (data.size() - 1))
	{
		ss << data[ii] << ", ";
		++ii;
	}
	if (ii < data.size())
	{
		ss << data[ii];
	}
	ss << " }";

	return ss.str();
}