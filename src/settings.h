#pragma once

#include "matherials.h"
#include "physics.h"
#include "math.h"
//#include "defines.h"

#include <string>
#include <utility>
#include <numeric>

#include <iostream>
#include <iomanip>
#include <string_view>
#include <unordered_map>

using namespace std::string_view_literals;

// Сожержит структуру настроек клапана и все необходимые методы для её получения
namespace settings {

#define GAS_TYPE_STRING std::string _gas_type_str                                        // Тип газа в системе в виде строки
#define GAS_CEL_TEMP physics::units::temperature::Cels _gas_celsium_temp                 // Температура газа в системе в град. Цельсия
#define GAS_IN_PRESS physics::units::pressure::MPa _gas_input_pressure                   // Давление газа перед диафрагмой, в МПа
#define GAS_OUT_PRESS physics::units::pressure::MPa _gas_output_pressure                 // Давление газа после диафрагмы, в МПа
#define PIPE_IN_DIAM math::units::Diameter _pipe_inner_diameter                          // Внутренний диаметр трубы, в мм
#define PIPE_STL_MARK std::string _pipe_steel_mark                                       // Марка стали тубы
#define APERTURE_DIAM math::units::Diameter _aperture_diameter                           // Диаметр диафрагмы, в мм

    namespace detail {

        // Not a Parameter
        static const std::string_view _NOAP = "NOAP";
        // Минимальное число аргументов командной строки
        static const int _MIN_ARGS = 2;

        enum class PARAM_TYPE {
            NOAP, HELP, GAS_TYPE_STR, GAS_CELSIUM_TEMP, GAS_INPUT_PRESSURE, 
            GAS_OUTPUT_PRESSURE, PIPE_INNER_DIAMETER, PIPE_STEEL_MARK, APERTURE_DIAMETER
            // NOAP - Not a Parameter
        };

        static const std::string_view _HT_HEADER_N = "N";
        static const std::string_view _HT_HEADER_SHORT_COM = "Short";
        static const std::string_view _HT_HEADER_LARGE_COM = "Large command";
        static const std::string_view _HT_HEADER_DESC = "Description";

        // Инкремент для enum PARAM_TYPE
        void operator++(PARAM_TYPE&);

        // Описание формальных параметров
        static const std::unordered_map<PARAM_TYPE, std::string_view> _PARAM_DESCR = {

            { PARAM_TYPE::HELP, "Show console commands descriptions" },

            { PARAM_TYPE::GAS_TYPE_STR, "Set gas type (print string)" },
            { PARAM_TYPE::GAS_CELSIUM_TEMP, "Set gas temperature, in Celsium" },

            { PARAM_TYPE::GAS_INPUT_PRESSURE, "Set gas input to pipe pressure, in MPa" },
            { PARAM_TYPE::GAS_OUTPUT_PRESSURE, "Set gas output from pipe pressure, in MPa" },

            { PARAM_TYPE::PIPE_INNER_DIAMETER, "Set pipe inner diameter, in mm" },
            { PARAM_TYPE::PIPE_STEEL_MARK, "Set pipe steel mark (print string)" },
            { PARAM_TYPE::APERTURE_DIAMETER, "Set aperture diameter, in mm" },

        };

        // Варианты формальных параметров
        static const std::unordered_map<std::string_view, PARAM_TYPE> _COMMAND_VARIANTS = {

            { "--help"sv, PARAM_TYPE::HELP }, { "-h"sv, PARAM_TYPE::HELP }, 

            { "--gas-type-str"sv, PARAM_TYPE::GAS_TYPE_STR }, { "-g"sv, PARAM_TYPE::GAS_TYPE_STR },
            { "--gas-cel-temp"sv, PARAM_TYPE::GAS_CELSIUM_TEMP }, { "-t"sv, PARAM_TYPE::GAS_CELSIUM_TEMP },

            { "--gas-in-press"sv, PARAM_TYPE::GAS_INPUT_PRESSURE }, { "-i"sv, PARAM_TYPE::GAS_INPUT_PRESSURE },
            { "--gas-out-press"sv, PARAM_TYPE::GAS_OUTPUT_PRESSURE }, { "-o"sv, PARAM_TYPE::GAS_OUTPUT_PRESSURE },

            { "--pipe-in-diam"sv, PARAM_TYPE::PIPE_INNER_DIAMETER }, { "-p"sv, PARAM_TYPE::PIPE_INNER_DIAMETER },
            { "--pipe-stl-mark"sv, PARAM_TYPE::PIPE_STEEL_MARK }, { "-s"sv, PARAM_TYPE::PIPE_STEEL_MARK },
            { "--aper-diam"sv, PARAM_TYPE::APERTURE_DIAMETER }, { "-a"sv, PARAM_TYPE::APERTURE_DIAMETER }

        };

        // Возвращает сроковое предаставление параметра
        struct ParamType {
            ParamType() = default;
            constexpr static std::string_view HELP_SHORT = "-h";
            constexpr static std::string_view HELP_LARGE = "--help";

            constexpr static std::string_view GAS_TYPE_SHORT = "-g";
            constexpr static std::string_view GAS_TYPE_LARGE = "--gas-type-str";
            constexpr static std::string_view GAS_CELSIUM_TEMP_SHORT = "-t";
            constexpr static std::string_view GAS_CELSIUM_TEMP_LARGE = "--gas-cel-temp";

            constexpr static std::string_view GAS_INPUT_PRESSURE_SHORT = "-i";
            constexpr static std::string_view GAS_INPUT_PRESSURE_LARGE = "--gas-in-press";
            constexpr static std::string_view GAS_OUTPUT_PRESSURE_SHORT = "-o";
            constexpr static std::string_view GAS_OUTPUT_PRESSURE_LARGE = "--gas-out-press";

            constexpr static std::string_view PIPE_INNER_DIAMETER_SHORT = "-p";
            constexpr static std::string_view PIPE_INNER_DIAMETER_LARGE = "--pipe-in-diam";
            constexpr static std::string_view PIPE_STEEL_MARK_SHORT = "-s";
            constexpr static std::string_view PIPE_STEEL_MARK_LARGE = "--pipe-stl-mark";
            constexpr static std::string_view APERTURE_DIAMETER_SHORT = "-a";
            constexpr static std::string_view APERTURE_DIAMETER_LARGE = "--aper-diam";
        };

        static const std::string_view _CW_SEPARATOR = " | ";

        // Ширина строки для вывода написания индекса | CW - Console Width
        static const int _CW_NUMBER = 2;
        // Ширина строки для вывода написания команды | CW - Console Width
        static const int _CW_LARGE_COMMAND = 20;
        // Ширина строки для вывода написания короткой команды | CW - Console Width
        static const int _CW_SHORT_COMMAND = 6;
        // Ширина строки для вывода текстового описания команды | CW - Console Width
        static const int _CW_COMMAND_DESCRIPTION = 50;

        // Количество формальных параметров
        static const size_t _PARAM_COUNT = _COMMAND_VARIANTS.size() / 2;

        using pair_com = std::pair<std::string_view, std::string_view>;

        // Возваращает пару короткого и длинного варианта команды
        pair_com GetParamExpression(const PARAM_TYPE& param);

        // Выводит в поток лист помощи с описанием всех комманд
        void PrintTableHeader(std::ostream&);

        // Выводит в поток лист помощи с описанием всех комманд
        void PrintHelpListAndExit(std::ostream&);

        // Првоеряет количество переданных параметров
        bool ParamCountIsCorrect(int);

        // Возвращает тип параметра по полученной строке
        PARAM_TYPE GetParamType(std::string_view);

    } // namespace detail

    // Блок настрроек для работы клапана
    struct Settings {

        GAS_TYPE_STRING = {};
        GAS_CEL_TEMP = {};
        GAS_IN_PRESS = {};
        GAS_OUT_PRESS = {};
        PIPE_IN_DIAM = {};
        PIPE_STL_MARK = {};
        APERTURE_DIAM = {};

        Settings() = default;
        Settings(const Settings&) = delete;
        Settings& operator=(const Settings&) = delete;

        Settings(Settings&&) = default;
        Settings& operator=(Settings&&) = default;
        ~Settings() = default;
    };

} // namespace settings



