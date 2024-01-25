#include "console.h"

#include <exception>
#include <stdexcept>

namespace console {

    using namespace std::string_literals;

    // Уточнение и проверка единиц измерения температуры
    void TemperatureSpecification(SettingsSet* set) {
        if (set->first._app_temp_unit == settings::APP_TEMP_UNIT::KALVIN)
            set->second._gas_celsium_temp = physics::units::Convert(
                physics::units::temperature::Kalv(set->second._gas_celsium_temp()));
    }

    // Уточнение и проверка единиц измерения давления
    void PressureSpecification(SettingsSet* set) {
        if (set->first._app_press_unit == settings::APP_PRESS_UNIT::ATM) {
            set->second._gas_drop_limmit = physics::units::Convert(
                physics::units::pressure::Atm(set->second._gas_drop_limmit()));

            set->second._gas_drop_step = physics::units::Convert(
                physics::units::pressure::Atm(set->second._gas_drop_step()));

            set->second._gas_press_drop = physics::units::Convert(
                physics::units::pressure::Atm(set->second._gas_press_drop()));

            set->second._gas_input_pressure = physics::units::Convert(
                physics::units::pressure::Atm(set->second._gas_input_pressure()));

            set->second._gas_output_pressure = physics::units::Convert(
                physics::units::pressure::Atm(set->second._gas_output_pressure()));
        }
    }

    // Уточнение и проверка показателя перепада давления
    void PressureDropSpecification(SettingsSet* set) {
        if (set->second._gas_press_drop.is_nan()) {

            if (set->second._gas_input_pressure.is_nan()
                || set->second._gas_output_pressure.is_nan())
            {
                throw std::logic_error("gas_input_pressure and gas_output_pressure must be setted");
            }
            else
            {
                set->second._gas_press_drop._value =
                    set->second._gas_input_pressure() - set->second._gas_output_pressure();
            }
        }
    }

    // Выставляет флаг работы обработчика в завивисимости от заданных параметров
    void HandlerModeSpecification(SettingsSet* set) {
        if (!set->second._gas_drop_step.is_nan()
            && !set->second._gas_drop_limmit.is_nan()
            && set->first._app_handler_mode != settings::APP_HANDLER_MODE::PACKAGE)
            set->first._app_handler_mode = settings::APP_HANDLER_MODE::PACKAGE;

        if (set->first._app_handler_mode == settings::APP_HANDLER_MODE::PACKAGE
            && !set->second._gas_drop_step.is_nan() && set->second._gas_drop_step() == 0)
            throw std::logic_error("Pressure drop step == NULL on APP_HANDLER_MODE::PACKAGE");
    }

    // Уточняет корректность заданного имени файла сохранения результатов
    void ReportFileNameSpecification(SettingsSet* set) {
        if ((set->first._app_report_png_file || set->first._app_report_txt_file) && set->first._app_report_file_name.empty())
            throw std::logic_error("Report file name must be setted");
    }

    /*
        Для обеспечения корректности работы программы необходимо добавить проверки 
        на наличие всех требуемых данных с учётом режима исполнения обработчика
    */

    // Уточнение и проверка заданых параметров
    void SettingsSpecification(SettingsSet* set) {

        TemperatureSpecification(set);
        PressureSpecification(set);
        PressureDropSpecification(set);
        HandlerModeSpecification(set);
        ReportFileNameSpecification(set);

        /*
            ...
        */
    }

    template <typename Arg>
    void SetDataToArguments(
        settings::detail::PARAM_TYPE type, 
        settings::HandlerSettings* handler_settings, 
        settings::ValveSettings* valve_settings, 
        Arg&& arg) 
    {
        switch (type)
        {  
        
        // -------------------------- dimension units ---------------------------------------

        case settings::detail::PARAM_TYPE::ATM:
            handler_settings->_app_press_unit = settings::APP_PRESS_UNIT::ATM;
            break;

        case settings::detail::PARAM_TYPE::MPA:
            handler_settings->_app_press_unit = settings::APP_PRESS_UNIT::MPA;
            break;

        case settings::detail::PARAM_TYPE::KALVIN:
            handler_settings->_app_temp_unit = settings::APP_TEMP_UNIT::KALVIN;
            break;

        case settings::detail::PARAM_TYPE::CELSIUM:
            handler_settings->_app_temp_unit = settings::APP_TEMP_UNIT::CELSIUM;
            break;

        // -------------------------- handler configuration ---------------------------------

        case settings::detail::PARAM_TYPE::APP_HANDLER_MODE:
            handler_settings->_app_handler_mode = settings::detail::GetHandlerMode(arg);
            break;

        case settings::detail::PARAM_TYPE::FILE_NAME:
            handler_settings->_app_report_file_name = std::move(arg);
            break;

        case settings::detail::PARAM_TYPE::TEXT:
            handler_settings->_app_report_txt_file = true;
            break;

        case settings::detail::PARAM_TYPE::IMAGE:
            handler_settings->_app_report_png_file = true;
            break;

        case settings::detail::PARAM_TYPE::CONSOLE:
            handler_settings->_app_report_console = true;
            break;

        // -------------------------- valve configuration -----------------------------------

        case settings::detail::PARAM_TYPE::GAS_TYPE_STR:
            valve_settings->_gas_type_str = std::move(arg);
            break;

        case settings::detail::PARAM_TYPE::GAS_CELSIUM_TEMP:
            valve_settings->_gas_celsium_temp = physics::units::temperature::Cels(std::stod(std::forward<Arg>(arg)));
            break;

        case settings::detail::PARAM_TYPE::GAS_INPUT_PRESSURE:
            valve_settings->_gas_input_pressure = physics::units::pressure::MPa(std::stod(std::forward<Arg>(arg)));
            break;

        case settings::detail::PARAM_TYPE::GAS_OUTPUT_PRESSURE:
            valve_settings->_gas_output_pressure = physics::units::pressure::MPa(std::stod(std::forward<Arg>(arg)));
            break;


        case settings::detail::PARAM_TYPE::GAS_PRESSURE_DROP:
            valve_settings->_gas_press_drop = physics::units::pressure::MPa(std::stod(std::forward<Arg>(arg)));
            break;

        case settings::detail::PARAM_TYPE::GAS_DROP_LIMMIT:
            valve_settings->_gas_drop_limmit = physics::units::pressure::MPa(std::stod(std::forward<Arg>(arg)));
            break;

        case settings::detail::PARAM_TYPE::GAS_DROP_STEP:
            valve_settings->_gas_drop_step = physics::units::pressure::MPa(std::stod(std::forward<Arg>(arg)));
            break;


        case settings::detail::PARAM_TYPE::PIPE_STEEL_MARK:
            valve_settings->_pipe_steel_mark = std::move(arg);
            break;

        case settings::detail::PARAM_TYPE::PIPE_INNER_DIAMETER:
            valve_settings->_pipe_inner_diameter = math::units::Diameter(std::stod(std::forward<Arg>(arg)));
            break;

        case settings::detail::PARAM_TYPE::APERTURE_DIAMETER:
            valve_settings->_aperture_diameter = math::units::Diameter(std::stod(std::forward<Arg>(arg)));
            break;

        case settings::detail::PARAM_TYPE::APERTURE_SCALER:
            valve_settings->_aperture_scaler = std::stod(std::forward<Arg>(arg));
            break;
        
        default:
            break;
        }
    }

    void ParseSingleCommand(
        settings::HandlerSettings* handler_settings, 
        settings::ValveSettings* valve_settings, 
        const char* line) 
    {
        std::string command = "";
        std::string argument = "";

        bool arg = false;

        while (*line != '\00')
        {
            if (*line != '=')
            {
                if (!arg)
                {
                    command.push_back(*line);
                }
                else 
                {
                    argument.push_back(*line);
                }
            }
            else 
            {
                arg = true;
            }

            ++line;
        }

        settings::detail::PARAM_TYPE type = settings::detail::GetParamType(command.data());

        if (type != settings::detail::PARAM_TYPE::HELP) {
            SetDataToArguments(type, handler_settings, valve_settings, argument);
        }
        else {
            settings::detail::PrintHelpListAndExit(std::cerr);
        }
    }
    
    settings::ValveSettings ParseCommandLine(int args, char** argv) {

        if (!settings::detail::ParamCountIsCorrect(args)) {
            throw std::invalid_argument("command line has incorrect arguments count");
        }

        settings::ValveSettings result;
        for (int i = 1; i != args; ++i) {
            ParseSingleCommand(nullptr, &result, argv[i]);
        }

        return result; // воспользуемся RVO компилятора и тем, что у структуры имеются только перемещающие конструкторы
    }

    SettingsSet GetSettingsSet(int args, char** argv) {

        if (!settings::detail::ParamCountIsCorrect(args)) {
            throw std::invalid_argument("command line has incorrect arguments count");
        }

        SettingsSet result;

        for (int i = 1; i != args; ++i) {
            ParseSingleCommand(&result.first, &result.second, argv[i]);
        }

        SettingsSpecification(&result);
        return result;
    }

} // namespace console 