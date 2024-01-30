#include "handler.h"

#include <Python.h>
#include "../3rd_party/matplotlibcpp.h"
#define PY_SSIZE_T_CLEAN

#include <stdexcept>
#include <exception>

namespace handler {

	Handler::Handler(int args, char** argv) {

		auto settings = console::GetSettingsSet(args, argv);
		_handler_settings = std::move(settings.first);
		_valve_settings = std::move(settings.second);

		_valve = std::make_unique<fittings::Valve>(_valve_settings);
	};

	Handler& Handler::Run() {

		switch (_handler_settings._app_handler_mode)
		{
		case settings::APP_HANDLER_MODE::SINGLE:
			return HandleValveSingleCalculation();

		case settings::APP_HANDLER_MODE::PACKAGE:
			return HandleValvePackageCalculation();

		default:
			return *this;
		}
	}

	Handler& Handler::PrintResultInOstream(const fittings::ValveResult& result, std::ostream& out) {
		out << "Gaz mass consumption is " << result._mass_consumption << " kg/sec" << std::endl;
		out << "Gaz volume consumption is " << result._volume_consumption << " m3/sec" << std::endl;
		return *this;
	}

	Handler& Handler::DrawResultInToImage(const fittings::ValveResult& result) {
		namespace plt = matplotlibcpp;

		std::vector<double> mass = { result._mass_consumption, 0 };
		std::vector<double> value = { 0, result._volume_consumption };

		plt::title("Gaz consumption");

		plt::bar(mass, "black", "-", 1, { {"color", "blue"}, {"label", "fasfasf"}});
		plt::bar(value, "black", "-", 1, { {"color", "orange"} });

		plt::text(0.0, result._mass_consumption, std::to_string(static_cast<int>(result._mass_consumption)));
		plt::text(1.0, result._volume_consumption, std::to_string(static_cast<int>(result._volume_consumption)));

		plt::plot({ 0 }, { {"label", "kg/sec"}, {"color", "blue"} });
		plt::plot({ 0 }, { {"label", "m3/sec"}, {"color", "orange"} });

		plt::legend();
		plt::save(_handler_settings._app_report_file_name);

		return *this;
	}

	Handler& Handler::HandleValveSingleCalculation() {

		if (_valve == nullptr) 
			throw std::runtime_error("The valve is not available");

		fittings::ValveResult result = _valve->GetCalculationResult();

		if (_handler_settings._app_report_console)
			PrintResultInConsole(result);

		if (_handler_settings._app_report_txt_file)
			WriteResultToTextFile(result);

		if (_handler_settings._app_report_png_file)
			DrawResultInToImage(result);
		
		return *this;
	}

	std::vector<double> Handler::GetConsumptionVector(const Handler::CycleResults& results, Handler::CONSUM_TYPE type) {
		std::vector<double> result(results.size());

		for (size_t i = 0; i != result.size(); ) {

			switch (type)
			{
			case handler::Handler::CONSUM_TYPE::MASS:
				result[++i] = results[i]._mass_consumption;
				break;

			case handler::Handler::CONSUM_TYPE::VOLUME:
				result[++i] = results[i]._volume_consumption;
				break;

			default:
				break;
			}
		}
		return result;
	}

	Handler& Handler::DrawResultInToImage(const PackageResult& result) {

		namespace plt = matplotlibcpp;
		plt::title("Gaz volume consumption, in m3/sec");

		for (size_t i = 0; i != result.size(); ++i) {
			double drop = _valve_settings._gas_press_drop() + (_valve_settings._gas_drop_step() * (i + 1));
			std::string label = "Gas pressure drop = " + std::to_string(drop) + " MPa";
			plt::plot(GetConsumptionVector(result[i], Handler::CONSUM_TYPE::VOLUME), {{"label", label}});
		}

		plt::ylabel("Volume consumption value");
		plt::xlabel("Valve aperture open-preccent");
		
		plt::legend();
		plt::save(_handler_settings._app_report_file_name);

		return *this;
	}


	Handler& Handler::PrintResultInOstream(const PackageResult& result, std::ostream& out) {

		out << "Gas consumption package calculation" << std::endl;
		out << "Gas type - \"" << _valve_settings._gas_type_str  << "\"" << std::endl;
		out << "Gas press ~ " << (int)_valve_settings._gas_input_pressure() << " MPa" << std::endl;
		out << "Gas temp - " << (int)_valve_settings._gas_celsium_temp() << " cel" << std::endl;

		for (size_t i = 0; i != result.size(); ++i) {
			
			double drop = _valve_settings._gas_press_drop() + (_valve_settings._gas_drop_step() * (i + 1));
			out << std::endl << "Cycle #" << i << " | Gas pressure drop = " << drop << " MPa" << std::endl;

			for (size_t j = 0; j != result[i].size(); ++j) {
				out << (double)(j + 1) / 100 << " | ";
				out << "Mass consumption = " << (int)result[i][j]._mass_consumption << " kg/sec" << " | ";
				out << "Volume consumption = " << (int)result[i][j]._volume_consumption << " m3/sec" << std::endl;
			}
		}

		return *this;
	}

	size_t Handler::GetNumCycles() {
		return (static_cast<size_t>(_valve_settings._gas_drop_limmit() * 1e3)
			- static_cast<size_t>(_valve_settings._gas_press_drop() * 1e3))
			/ static_cast<size_t>(_valve_settings._gas_drop_step() * 1e3);
	}

	Handler::CycleResults Handler::HandleOneCycleCalcucation() {

		if (_valve == nullptr) 
			throw std::runtime_error("The valve is not available");

		CycleResults result;
		result.reserve(100);

		while (_valve_settings._aperture_scaler <= 1.0)
		{
			result.push_back(
				std::move(_valve->GetCalculationResult()));

			_valve_settings._aperture_scaler += 0.01;
		}

		return result;
	}

	Handler& Handler::HandleValvePackageCalculation() {

		/* Определяем количество требуемых итераций рассчётов */

		size_t num_cycles = GetNumCycles();
		PackageResult result(num_cycles);

		/* Выполняем указанное количество циклов рассчёта с открытием клапана 0.0 -> 1.0 */
		double income_gas_press_drop = _valve_settings._gas_press_drop();
		for (size_t i = 0; i != num_cycles; ) {
			_valve_settings._gas_press_drop._value += _valve_settings._gas_drop_step()/* * (i + 1)*/;
			_valve_settings._aperture_scaler = 0.0;

			result[i++] = std::move(HandleOneCycleCalcucation());
		}

		/* Возвращаем исходное значение падения давления */
		_valve_settings._gas_press_drop._value = income_gas_press_drop;

		if (_handler_settings._app_report_console)
			PrintResultInConsole(result);

		if (_handler_settings._app_report_txt_file)
			WriteResultToTextFile(result);

		if (_handler_settings._app_report_png_file)
			DrawResultInToImage(result);

		return *this;
	}

} // namespace handler