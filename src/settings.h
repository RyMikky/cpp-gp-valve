﻿#pragma once

#include "matherials.h"
#include "physics.h"
#include "math.h"

#include <set>
#include <vector>
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

    // Режим исполнения обработчика
    enum class APP_HANDLER_MODE {
        NOAP, SINGLE, PACKAGE
    };

    // Единица измерения температуры на входе в консоль
    enum class APP_TEMP_UNIT {
        NOAP, KALVIN, CELSIUM
    };

    // Единица измерения давлеия на входе в консоль
    enum class APP_PRESS_UNIT {
        NOAP, MPA, ATM
    };

#define APP_MODE APP_HANDLER_MODE _app_handler_mode                                      // Режим выполнения программы
#define APP_PRESS APP_PRESS_UNIT _app_press_unit                                         // Eдиницы измерения давления
#define APP_TEMP APP_TEMP_UNIT _app_temp_unit                                            // Eдиницы измерения температуры

#define REPORT_TO_CONSOLE bool _app_report_console                                       // Флаг вывода информации в консоль
#define REPORT_TO_TEXT bool _app_report_txt_file                                         // Флаг вывода информации в текстовый файл
#define REPORT_TO_IMAGE bool _app_report_png_file                                        // Флаг вывода информации в файл изображения
#define REPORT_FILE_NAME std::string _app_report_file_name                               // Имя файла сохранения информации 

#define GAS_TYPE_STRING std::string _gas_type_str                                        // Тип газа в системе в виде строки
#define GAS_CEL_TEMP physics::units::temperature::Cels _gas_celsium_temp                 // Температура газа в системе в град. Цельсия
#define GAS_IN_PRESS physics::units::pressure::MPa _gas_input_pressure                   // Давление газа перед диафрагмой, в МПа
#define GAS_OUT_PRESS physics::units::pressure::MPa _gas_output_pressure                 // Давление газа после диафрагмы, в МПа

#define GAS_PRESS_DROP physics::units::pressure::MPa _gas_press_drop                     // Падение давления на перепаде, в МПа
#define GAS_DROP_LIMM physics::units::pressure::MPa _gas_drop_limmit                     // Предельное значения перепада давленния, в МПа
#define GAS_DROP_STP physics::units::pressure::MPa _gas_drop_step                        // Шаг изменения перепада давления, в МПа

#define PIPE_IN_DIAM math::units::Diameter _pipe_inner_diameter                          // Внутренний диаметр трубы, в мм
#define PIPE_STL_MARK std::string _pipe_steel_mark                                       // Марка стали тубы
#define APERTURE_DIAM math::units::Diameter _aperture_diameter                           // Диаметр диафрагмы, в мм
#define APERTURE_SCAL double _aperture_scaler                                            // Процент открытия клапана от 0 до 1

    namespace detail {

        // Not a Parameter
        static const std::string_view _NOAP = "NOAP";
        // Минимальное число аргументов командной строки
        static const int _MIN_ARGS = 2;

        enum class PARAM_TYPE {
            NOAP, HELP, 

            ATM, MPA, KALVIN, CELSIUM,
                    
            APP_HANDLER_MODE, FILE_NAME, 
            TEXT, IMAGE, CONSOLE,
       
            GAS_TYPE_STR, GAS_CELSIUM_TEMP, GAS_INPUT_PRESSURE, GAS_OUTPUT_PRESSURE, 
            
            GAS_PRESSURE_DROP, GAS_DROP_LIMMIT, GAS_DROP_STEP, 

            PIPE_INNER_DIAMETER, PIPE_STEEL_MARK, APERTURE_DIAMETER, APERTURE_SCALER
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

            // -------------------------- dimension units ---------------------------------------

            { PARAM_TYPE::ATM, "Set pressure dimension unit as Atm" },
            { PARAM_TYPE::MPA, "Set pressure dimension unit as MPa (used by default)" },
            { PARAM_TYPE::KALVIN, "Set temperature dimension unit as Kalvin" },
            { PARAM_TYPE::CELSIUM, "Set temperature dimension unit as Celsium (used by default)" },

            // -------------------------- handler configuration ---------------------------------

            { PARAM_TYPE::APP_HANDLER_MODE, "Set programm hadler mode (optional parameter)"},
            { PARAM_TYPE::FILE_NAME, "Set handler report file name (used for txt/png output)"},
            { PARAM_TYPE::TEXT, "Process handler report in to *.txt file"},
            { PARAM_TYPE::IMAGE, "Process handler report in to *.png file"},
            { PARAM_TYPE::CONSOLE, "Process handler report in to system console (used by default)"},

            // -------------------------- valve configuration -----------------------------------

            { PARAM_TYPE::GAS_TYPE_STR, "Set gas type (print string)" },
            { PARAM_TYPE::GAS_CELSIUM_TEMP, "Set gas temperature, in Celsium" },

            { PARAM_TYPE::GAS_INPUT_PRESSURE, "Set gas input to pipe pressure, in MPa" },
            { PARAM_TYPE::GAS_OUTPUT_PRESSURE, "Set gas output aperture pipe pressure, in MPa" },

            { PARAM_TYPE::GAS_PRESSURE_DROP, "Set gas pressure drop on aperture, in MPa (used in package-mode as from-value)" },
            { PARAM_TYPE::GAS_DROP_LIMMIT, "Set gas pressure drop max_value, in MPa (used in package-mode as to-value)"},
            { PARAM_TYPE::GAS_DROP_STEP, "Set gas pressure drop step, in MPa (must be set on package-mode)"},

            { PARAM_TYPE::PIPE_INNER_DIAMETER, "Set pipe inner diameter, in mm" },
            { PARAM_TYPE::PIPE_STEEL_MARK, "Set pipe steel mark (print string)" },
            { PARAM_TYPE::APERTURE_DIAMETER, "Set aperture diameter, in mm" },
            { PARAM_TYPE::APERTURE_SCALER, "Set aperture opened scale, in range 0.0 - 1.0" },

        };

        // Варианты формальных параметров
        static const std::unordered_map<std::string_view, PARAM_TYPE> _COMMAND_VARIANTS = {

            { "--help"sv, PARAM_TYPE::HELP }, { "-h"sv, PARAM_TYPE::HELP }, 

            // -------------------------- dimension units ---------------------------------------

            { "--atm", PARAM_TYPE::ATM  }, { "--mpa", PARAM_TYPE::MPA  },
            { "--kalvin", PARAM_TYPE::KALVIN  }, { "--celsium", PARAM_TYPE::CELSIUM  },
            

            // -------------------------- handler configuration ---------------------------------

            { "--handler-mode"sv, PARAM_TYPE::APP_HANDLER_MODE }, { "-m"sv, PARAM_TYPE::APP_HANDLER_MODE },
            { "--out-file-name"sv, PARAM_TYPE::FILE_NAME }, { "-n"sv, PARAM_TYPE::FILE_NAME },
            { "--text"sv, PARAM_TYPE::TEXT }, { "--image"sv, PARAM_TYPE::IMAGE }, { "--console"sv, PARAM_TYPE::CONSOLE },

            // -------------------------- valve configuration -----------------------------------

            { "--gas-type-str"sv, PARAM_TYPE::GAS_TYPE_STR }, { "-g"sv, PARAM_TYPE::GAS_TYPE_STR },
            { "--gas-cel-temp"sv, PARAM_TYPE::GAS_CELSIUM_TEMP }, { "-t"sv, PARAM_TYPE::GAS_CELSIUM_TEMP },

            { "--gas-in-press"sv, PARAM_TYPE::GAS_INPUT_PRESSURE }, { "-i"sv, PARAM_TYPE::GAS_INPUT_PRESSURE }, 
            { "--gas-out-press"sv, PARAM_TYPE::GAS_OUTPUT_PRESSURE }, { "-o"sv, PARAM_TYPE::GAS_OUTPUT_PRESSURE },

            { "--gas-press-drop"sv, PARAM_TYPE::GAS_PRESSURE_DROP }, { "-d"sv, PARAM_TYPE::GAS_PRESSURE_DROP },
            { "--gas-drop-limmit"sv, PARAM_TYPE::GAS_DROP_LIMMIT }, { "-l"sv, PARAM_TYPE::GAS_DROP_LIMMIT },
            { "--gas-drop-step"sv, PARAM_TYPE::GAS_DROP_STEP }, { "-e"sv, PARAM_TYPE::GAS_DROP_STEP },

            { "--pipe-in-diam"sv, PARAM_TYPE::PIPE_INNER_DIAMETER }, { "-p"sv, PARAM_TYPE::PIPE_INNER_DIAMETER },
            { "--pipe-stl-mark"sv, PARAM_TYPE::PIPE_STEEL_MARK }, { "-s"sv, PARAM_TYPE::PIPE_STEEL_MARK },
            { "--aper-diam"sv, PARAM_TYPE::APERTURE_DIAMETER }, { "-a"sv, PARAM_TYPE::APERTURE_DIAMETER },
            { "--aper-scale"sv, PARAM_TYPE::APERTURE_SCALER }, { "-c"sv, PARAM_TYPE::APERTURE_SCALER }

        };

        static const std::set<std::string_view> _POSSIBLE_HANDLER_MODE_ARGS =
        {
            "single"sv, "package"sv, "single_mode"sv, "package_mode"sv
        };

        static const std::unordered_map<std::string_view, APP_HANDLER_MODE> _MODE_VARIANTS =
        {
            { "single"sv, APP_HANDLER_MODE::SINGLE }, { "single_mode"sv, APP_HANDLER_MODE::SINGLE },
            { "package"sv, APP_HANDLER_MODE::PACKAGE }, { "package_mode"sv, APP_HANDLER_MODE::PACKAGE },
        };

        // Возвращает сроковое предаставление параметра
        struct ParamType {
            ParamType() = default;
            constexpr static std::string_view HELP_SHORT = "-h";
            constexpr static std::string_view HELP_LARGE = "--help";

            // -------------------------- dimension units ---------------------------------------

            constexpr static std::string_view ATM_SHORT = "";
            constexpr static std::string_view ATM_LARGE = "--atm";
            constexpr static std::string_view MPA_SHORT = "";
            constexpr static std::string_view MPA_LARGE = "--mpa";
            constexpr static std::string_view KALVIN_SHORT = "";
            constexpr static std::string_view KALVIN_LARGE = "--kalvin";
            constexpr static std::string_view CELSIUM_SHORT = "";
            constexpr static std::string_view CELSIUM_LARGE = "--celsium";

            // -------------------------- handler configuration ---------------------------------

            constexpr static std::string_view HANDLER_MODE_SHORT = "-m";
            constexpr static std::string_view HANDLER_MODE_LARGE = "--handler-mode";
            constexpr static std::string_view FILE_NAME_SHORT = "-n";
            constexpr static std::string_view FILE_NAME_LARGE = "--out-file-name";
            constexpr static std::string_view TEXT_SHORT = "";
            constexpr static std::string_view TEXT_LARGE = "--text";
            constexpr static std::string_view IMAGE_SHORT = "";
            constexpr static std::string_view IMAGE_LARGE = "--image";
            constexpr static std::string_view CONSOLE_SHORT = "";
            constexpr static std::string_view CONSOLE_LARGE = "--console";

            // -------------------------- valve configuration -----------------------------------

            constexpr static std::string_view GAS_TYPE_SHORT = "-g";
            constexpr static std::string_view GAS_TYPE_LARGE = "--gas-type-str";
            constexpr static std::string_view GAS_CELSIUM_TEMP_SHORT = "-t";
            constexpr static std::string_view GAS_CELSIUM_TEMP_LARGE = "--gas-cel-temp";

            constexpr static std::string_view GAS_INPUT_PRESSURE_SHORT = "-i";
            constexpr static std::string_view GAS_INPUT_PRESSURE_LARGE = "--gas-in-press";
            constexpr static std::string_view GAS_OUTPUT_PRESSURE_SHORT = "-o";
            constexpr static std::string_view GAS_OUTPUT_PRESSURE_LARGE = "--gas-out-press";

            constexpr static std::string_view GAS_PRESSURE_DROP_SHORT = "-d";
            constexpr static std::string_view GAS_PRESSURE_DROP_LARGE = "--gas-press-drop";
            constexpr static std::string_view GAS_DROP_LIMMIT_SHORT = "-l";
            constexpr static std::string_view GAS_DROP_LIMMIT_LARGE = "--gas-drop-limmit";
            constexpr static std::string_view GAS_DROP_STEP_SHORT = "-e";
            constexpr static std::string_view GAS_DROP_STEP_LARGE = "--gas-drop-step";

            constexpr static std::string_view PIPE_INNER_DIAMETER_SHORT = "-p";
            constexpr static std::string_view PIPE_INNER_DIAMETER_LARGE = "--pipe-in-diam";
            constexpr static std::string_view PIPE_STEEL_MARK_SHORT = "-s";
            constexpr static std::string_view PIPE_STEEL_MARK_LARGE = "--pipe-stl-mark";
            constexpr static std::string_view APERTURE_DIAMETER_SHORT = "-a";
            constexpr static std::string_view APERTURE_DIAMETER_LARGE = "--aper-diam";
            constexpr static std::string_view APERTURE_SCALER_SHORT = "-c";
            constexpr static std::string_view APERTURE_SCALER_LARGE = "--aper-scale";
        };

        // Печатает возможные значения аргументов для параметра
        template <typename Collection>
        void PrintParameterPossibleArgs(Collection collection, std::ostream& out) {
            out << "   Possible command arguments: ";
            for (const auto& item : collection) {
                out << "\"" << item << "\" ";
            }

            out << std::endl;
        }

        static const std::string_view _CW_SEPARATOR = " | ";

        // Ширина строки для вывода написания индекса | CW - Console Width
        static const int _CW_NUMBER = 4;
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

        // Возвращает режим обработчика по полученной строке
        APP_HANDLER_MODE GetHandlerMode(std::string_view);

        // Возвращает тип параметра по полученной строке
        PARAM_TYPE GetParamType(std::string_view);

    } // namespace detail

    // Блок настроек обработчика
    struct HandlerSettings {

        APP_MODE = APP_HANDLER_MODE::SINGLE;
        APP_PRESS = APP_PRESS_UNIT::MPA;
        APP_TEMP = APP_TEMP_UNIT::CELSIUM;

        REPORT_TO_CONSOLE = true;
        REPORT_TO_TEXT = false;
        REPORT_TO_IMAGE = false;
        REPORT_FILE_NAME = {};

        HandlerSettings() = default;
        HandlerSettings(const HandlerSettings&) = delete;
        HandlerSettings& operator=(const HandlerSettings&) = delete;

        HandlerSettings(HandlerSettings&&) = default;
        HandlerSettings& operator=(HandlerSettings&&) = default;
        ~HandlerSettings() = default;
    };

    // Блок настрроек клапана
    struct ValveSettings {

        GAS_TYPE_STRING = {};
        GAS_CEL_TEMP = {};
        GAS_IN_PRESS = {};
        GAS_OUT_PRESS = {};

        GAS_PRESS_DROP = {};
        GAS_DROP_LIMM = {};
        GAS_DROP_STP = {};

        PIPE_IN_DIAM = {};
        PIPE_STL_MARK = {};
        APERTURE_DIAM = {};
        APERTURE_SCAL = 1.0;     // По умолчанию установлен в едницу - открыт полностью

        ValveSettings() = default;
        ValveSettings(const ValveSettings&) = delete;
        ValveSettings& operator=(const ValveSettings&) = delete;

        ValveSettings(ValveSettings&&) = default;
        ValveSettings& operator=(ValveSettings&&) = default;
        ~ValveSettings() = default;
    };

} // namespace settings



