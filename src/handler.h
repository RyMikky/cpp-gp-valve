#pragma once

#include "valve.h"
#include "console.h"

namespace handler {

	// Класс-обработчик выполнения тестирования и сбора данных по расходу газа проходящего через клапан
	class Handler {
		using CycleResults = std::vector<fittings::ValveResult>;
		using PackageResult = std::vector<CycleResults>;
	private:
		settings::HandlerSettings _handler_settings = {};
		settings::ValveSettings _valve_settings = {};
	public:
		Handler() = delete;
		Handler(int args, char** argv);

		Handler& Run();

	private:
		std::unique_ptr<fittings::Valve> _valve = nullptr;

		// Выводит информацию с результатом в поток
		Handler& PrintResultInOstream(const fittings::ValveResult&, std::ostream&);

		// Выводит информацию с результатом в консоль
		template <typename Result>
		Handler& PrintResultInConsole(const Result&);

		// Записывает информацию с резульатом в текстовый файл
		template <typename Result>
		Handler& WriteResultToTextFile(const Result&);

		// Отображает результат в изображении
		Handler& DrawResultInToImage(const fittings::ValveResult&);

		// Выполняет обработку в режиме одиночного рассчёта
		Handler& HandleValveSingleCalculation();

		enum class CONSUM_TYPE {
			MASS, VOLUME
		};

		// Возвращает вектор значений расхода из вектора результатов цикла
		std::vector<double> GetConsumptionVector(const Handler::CycleResults&, CONSUM_TYPE);
		
		// Отображает результат в изображении
		Handler& DrawResultInToImage(const PackageResult&);

		// Выводит информацию с комплексным результатом в поток
		Handler& PrintResultInOstream(const PackageResult&, std::ostream&);

		// Возвращает количество циклов обработки
		size_t GetNumCycles();

		// Выполняет цикл обработки с заданными параметрами
		CycleResults HandleOneCycleCalcucation();

		// Выполняет обработку в режиме пакетной обработки диапазона
		Handler& HandleValvePackageCalculation();

	};

	template <typename Result>
	Handler& Handler::PrintResultInConsole(const Result& result) {
		return Handler::PrintResultInOstream(result, std::cout);
	}

	template <typename Result>
	Handler& Handler::WriteResultToTextFile(const Result& result) {
		std::ofstream out(std::string{ _handler_settings._app_report_file_name + ".txt" }, std::ios::trunc);
		if (!out.is_open() || !out.good())
			throw std::runtime_error("Can't open file \""
				+ std::string{ _handler_settings._app_report_file_name + ".txt" } + "\" to write");

		PrintResultInOstream(result, out);
		out.close();
		return *this;
	}

} // namespace handler