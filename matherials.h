#pragma once

#include <exception>
#include <stdexcept>
#include <string_view>
#include <unordered_map>

// Блок с информацией по конструкционным материалам стали для трубопроводов
namespace matherials {

	using namespace std::string_view_literals;

	struct SteelCoef {;
		double _ae = 0.0;
		double _be = 0.0;
		double _ce = 0.0;
	};

	// коэффициенты для рассчёта температурного различных марок стали
	static const std::unordered_map<std::string_view, SteelCoef> _STEEL_DATA = 
	{
		{ "8"sv, {10.9, 7.7, 2.4 }}, { "10"sv, {10.8, 9.0, 4.2 } }, { "15"sv, {11.1, 7.9, 3.9 }},
		{ "15m"sv, {10.7, 13.0, 13.0 }}, { "16m"sv, {11.1, 8.4, 3.7 }}, { "20"sv, {11.1, 7.7, 3.4 }},
		{ "20m"sv, {10.7, 13.0, 13.0 }}, { "25"sv, {12.2, 0.0, 0.0 }}, { "30"sv, {10.2, 10.4, 5.6 }},
		{ "35"sv, {10.2, 10.4, 5.6 }}, { "h6Sm"sv, {10.1, 2.7, 0.0 }}, { "h7Sm"sv, {10.1, 2.7, 0.0 }},
		{ "12mh"sv, {11.3, 3.8, 0.0 }}, { "12h1mf"sv, {10.0, 9.6, 6.0 }}, { "12h17"sv, {9.4, 7.4, 6.0 }}, 
		{ "12h18n9t"sv, {15.6, 8.3, 6.5 }}, { "12h18n10t"sv, {15.6, 8.3, 6.5 }}, { "14h17n2"sv, {9.4, 7.5, 7.8 }},
		{ "15hma"sv, {11.1, 8.5, 5.2 }}, { "15h1m1f"sv, {10.4, 8.1, 4.4 }}, { "15n5m"sv, {10.1, 2.7, 0.0 }}, 
		{ "15h12ehmf"sv, {9.8, 3.0, 0.0 }}, { "17h18n9"sv, {15.0, 5.7, 0.0 }}, { "20h23n13"sv, {15.5, 1.7, 0.0 }},
		{ "36h18n25s2"sv, {12.0, 10.0, 5.4 }}
	};

	// Вовзращает таблицу с коэфеициентами для указанной марки стали.
	// Внимание! Ввод должен быть осуществлён цифрами и латинскими буквами в нижнем регистре
	static const SteelCoef GetSteelCoef(std::string_view line) {
		if (_STEEL_DATA.count(line)) return _STEEL_DATA.at(line);
		throw std::out_of_range(
			"The data table does not contain the specified entry, \
				make sure that the character input and case are correct");
	}

} // namespace matherials