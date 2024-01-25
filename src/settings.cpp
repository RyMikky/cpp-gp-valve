#include "settings.h"

namespace settings {

    namespace detail {

        void operator++(PARAM_TYPE& param) {

            switch (param)
            {
            case PARAM_TYPE::NOAP:
                param = PARAM_TYPE::HELP;
                break;

            case PARAM_TYPE::HELP:
                param = PARAM_TYPE::ATM;
                break;

            case PARAM_TYPE::ATM:
                param = PARAM_TYPE::MPA;
                break;

            case PARAM_TYPE::MPA:
                param = PARAM_TYPE::KALVIN;
                break;

            case PARAM_TYPE::KALVIN:
                param = PARAM_TYPE::CELSIUM;
                break;

            case PARAM_TYPE::CELSIUM:
                param = PARAM_TYPE::APP_HANDLER_MODE;
                break;

            case PARAM_TYPE::APP_HANDLER_MODE:
                param = PARAM_TYPE::FILE_NAME;
                break;

            case PARAM_TYPE::FILE_NAME:
                param = PARAM_TYPE::TEXT;
                break;

            case PARAM_TYPE::TEXT:
                param = PARAM_TYPE::IMAGE;
                break;

            case PARAM_TYPE::IMAGE:
                param = PARAM_TYPE::CONSOLE;
                break;

            case PARAM_TYPE::CONSOLE:
                param = PARAM_TYPE::GAS_TYPE_STR;
                break;
            
            case PARAM_TYPE::GAS_TYPE_STR:
                param = PARAM_TYPE::GAS_CELSIUM_TEMP;
                break;

            case PARAM_TYPE::GAS_CELSIUM_TEMP:
                param = PARAM_TYPE::GAS_INPUT_PRESSURE;
                break;

            case PARAM_TYPE::GAS_INPUT_PRESSURE:
                param = PARAM_TYPE::GAS_OUTPUT_PRESSURE;
                break;

            case PARAM_TYPE::GAS_OUTPUT_PRESSURE:
                param = PARAM_TYPE::GAS_PRESSURE_DROP;
                break;

            case PARAM_TYPE::GAS_PRESSURE_DROP:
                param = PARAM_TYPE::GAS_DROP_LIMMIT;
                break;

            case PARAM_TYPE::GAS_DROP_LIMMIT:
                param = PARAM_TYPE::GAS_DROP_STEP;
                break;

            case PARAM_TYPE::GAS_DROP_STEP:
                param = PARAM_TYPE::PIPE_INNER_DIAMETER;
                break;
            
            case PARAM_TYPE::PIPE_INNER_DIAMETER:
                param = PARAM_TYPE::PIPE_STEEL_MARK;
                break;

            case PARAM_TYPE::PIPE_STEEL_MARK:
                param = PARAM_TYPE::APERTURE_DIAMETER;
                break;

            case PARAM_TYPE::APERTURE_DIAMETER:
                param = PARAM_TYPE::APERTURE_SCALER;
                break;

            case PARAM_TYPE::APERTURE_SCALER:
                param = PARAM_TYPE::NOAP;
                break;

            default:
                break;
            }
        }

        // Возваращает пару короткого и длинного варианта команды
        pair_com GetParamExpression(const PARAM_TYPE& param) {
            switch (param)
            {
            case PARAM_TYPE::NOAP:
                return std::make_pair(_NOAP, _NOAP);

            case PARAM_TYPE::HELP:
                return std::make_pair(ParamType::HELP_SHORT, ParamType::HELP_LARGE);

            case PARAM_TYPE::ATM:
                return std::make_pair(ParamType::ATM_SHORT, ParamType::ATM_LARGE);

            case PARAM_TYPE::MPA:
                return std::make_pair(ParamType::MPA_SHORT, ParamType::MPA_LARGE);
              
            case PARAM_TYPE::KALVIN:
                return std::make_pair(ParamType::KALVIN_SHORT, ParamType::KALVIN_LARGE);

            case PARAM_TYPE::CELSIUM:
                return std::make_pair(ParamType::CELSIUM_SHORT, ParamType::CELSIUM_LARGE);

            case PARAM_TYPE::APP_HANDLER_MODE:
                return std::make_pair(ParamType::HANDLER_MODE_SHORT, ParamType::HANDLER_MODE_LARGE);

            case PARAM_TYPE::FILE_NAME:
                return std::make_pair(ParamType::FILE_NAME_SHORT, ParamType::FILE_NAME_LARGE);

            case PARAM_TYPE::TEXT:
                return std::make_pair(ParamType::TEXT_SHORT, ParamType::TEXT_LARGE);

            case PARAM_TYPE::IMAGE:
                return std::make_pair(ParamType::IMAGE_SHORT, ParamType::IMAGE_LARGE);

            case PARAM_TYPE::CONSOLE:
                return std::make_pair(ParamType::CONSOLE_SHORT, ParamType::CONSOLE_LARGE);
            
            case PARAM_TYPE::GAS_TYPE_STR:
                return std::make_pair(ParamType::GAS_TYPE_SHORT, ParamType::GAS_TYPE_LARGE);

            case PARAM_TYPE::GAS_CELSIUM_TEMP:
                return std::make_pair(ParamType::GAS_CELSIUM_TEMP_SHORT, ParamType::GAS_CELSIUM_TEMP_LARGE);

            case PARAM_TYPE::GAS_INPUT_PRESSURE:
                return std::make_pair(ParamType::GAS_INPUT_PRESSURE_SHORT, ParamType::GAS_INPUT_PRESSURE_LARGE);

            case PARAM_TYPE::GAS_OUTPUT_PRESSURE:
                return std::make_pair(ParamType::GAS_OUTPUT_PRESSURE_SHORT, ParamType::GAS_OUTPUT_PRESSURE_LARGE);

            case PARAM_TYPE::GAS_PRESSURE_DROP:
                return std::make_pair(ParamType::GAS_PRESSURE_DROP_SHORT, ParamType::GAS_PRESSURE_DROP_LARGE);

            case PARAM_TYPE::GAS_DROP_LIMMIT:
                return std::make_pair(ParamType::GAS_DROP_LIMMIT_SHORT, ParamType::GAS_DROP_LIMMIT_LARGE);

            case PARAM_TYPE::GAS_DROP_STEP:
                return std::make_pair(ParamType::GAS_DROP_STEP_SHORT, ParamType::GAS_DROP_STEP_LARGE);
            
            case PARAM_TYPE::PIPE_INNER_DIAMETER:
                return std::make_pair(ParamType::PIPE_INNER_DIAMETER_SHORT, ParamType::PIPE_INNER_DIAMETER_LARGE);

            case PARAM_TYPE::PIPE_STEEL_MARK:
                return std::make_pair(ParamType::PIPE_STEEL_MARK_SHORT, ParamType::PIPE_STEEL_MARK_LARGE);

            case PARAM_TYPE::APERTURE_DIAMETER:
                return std::make_pair(ParamType::APERTURE_DIAMETER_SHORT, ParamType::APERTURE_DIAMETER_LARGE);
            
            case PARAM_TYPE::APERTURE_SCALER:
                return std::make_pair(ParamType::APERTURE_SCALER_SHORT, ParamType::APERTURE_SCALER_LARGE);

            default:
                return std::make_pair(_NOAP, _NOAP);
            }
        }

        // Печатает возможные значения аргументов для параметра
        void PrintParameterPossibleArgs(PARAM_TYPE param, std::ostream& out) {
            switch (param) {

            case PARAM_TYPE::APP_HANDLER_MODE:
                PrintParameterPossibleArgs(_POSSIBLE_HANDLER_MODE_ARGS, out);
                break;
            }
        }

        // Выводит в поток лист помощи с описанием всех комманд
        void PrintTableHeader(std::ostream& out) {

            out << detail::_HT_HEADER_N << std::setw(_CW_NUMBER) << _CW_SEPARATOR;
            out << detail::_HT_HEADER_SHORT_COM << _CW_SEPARATOR;
            out << detail::_HT_HEADER_LARGE_COM << std::setw(
                _CW_LARGE_COMMAND - static_cast<int>(detail::_HT_HEADER_LARGE_COM.size())) << _CW_SEPARATOR;
            out << detail::_HT_HEADER_DESC << std::setw(NULL);
            out << std::endl;

        }

        // Выводит в поток лист помощи с описанием всех комманд
        void PrintHelpListAndExit(std::ostream& out) {
            using ParamExpression = std::pair<std::string_view, std::string_view>;

            out << "A program for simulating a gas valve and calculating the flow rate of a passing gas stream." 
                << std::endl << std::endl << "Use next console arguments" << std::endl;
            
            PrintTableHeader(out);
            PARAM_TYPE param = PARAM_TYPE::HELP;
            while (param != PARAM_TYPE::NOAP)
            {
                ParamExpression expression = GetParamExpression(param);
                if (expression.first != _NOAP && expression.second != _NOAP ) {

                    if (static_cast<int>(param) < 10) {
                        out << static_cast<int>(param) << std::setw(_CW_NUMBER) << _CW_SEPARATOR;
                    }
                    else {
                        out << static_cast<int>(param) << std::setw(_CW_NUMBER - 2) << _CW_SEPARATOR;
                    }
                    
                    if (expression.first == "") {
                        out << "  " << std::setw(_CW_SHORT_COMMAND) << _CW_SEPARATOR;
                    }
                    else {
                        out << expression.first << std::setw(_CW_SHORT_COMMAND) << _CW_SEPARATOR;
                    }
                    
                    out << expression.second << std::setw(
                        _CW_LARGE_COMMAND - static_cast<int>(expression.second.size())) << _CW_SEPARATOR;
                    out << _PARAM_DESCR.at(param) << std::setw(NULL);
                    out << std::endl;
                }

                ++param;
            }

            out << std::endl;

            out << "The program can be used in two modes: single (used as default) and package calculation\n";
            PrintParameterPossibleArgs(PARAM_TYPE::APP_HANDLER_MODE, out);
            out << " - In the single calculation mode, the program outputs the result in only one single state,\n   ";
            out << "with the valve fully open, according to the set parameters\n";
            out << " - In the package mode, the program calculates the gas flow rate according to the specified\n   ";
            out << "pressure drop range by opening the valve from 0 to 100%\n\n";

            out << "Some commands may overlap each other, for example, ";
            out << "suppose the commands are written in the following order:\n";
            out << "\t . . . " << ParamType::HANDLER_MODE_SHORT << "=single ";
            out << ParamType::KALVIN_LARGE << " ";
            out << ParamType::GAS_TYPE_SHORT << "=methane . . . ";
            out << ParamType::CELSIUM_LARGE << " . . .\n";
            out << "In this case, the first command \"--kalvin\" sets the temperature in Kelvin.\n";
            out << "However, next, the \"--celsium\" command appears, which resets the temperature units back to degrees Celsius\n";
            

            out << "\nFor example:\n";
            out << "\t" << ParamType::GAS_CELSIUM_TEMP_LARGE << "=15 ";
            out << ParamType::GAS_TYPE_SHORT << "=methane ";
            out << ParamType::PIPE_STEEL_MARK_LARGE << "=15m ";
            out << ParamType::PIPE_INNER_DIAMETER_SHORT << "=100 ";
            out << ParamType::APERTURE_DIAMETER_SHORT << "=75 ";
            out << ParamType::GAS_INPUT_PRESSURE_SHORT << "=12 ";
            out << ParamType::GAS_OUTPUT_PRESSURE_SHORT << "=8\n";
            out << "\nTry run application again whit correct arguments" << std::endl;
            
            std::exit(1);
        }

        // Првоеряет количество переданных параметров
        bool ParamCountIsCorrect(int count) {
            return count >= _MIN_ARGS && count <= settings::detail::_PARAM_COUNT + 1;
        }

        // Возвращает режим обработчика по полученной строке
        APP_HANDLER_MODE GetHandlerMode(std::string_view argv) {
            return _MODE_VARIANTS.count(argv) ? _MODE_VARIANTS.at(argv) : APP_HANDLER_MODE::NOAP;
        }

        // Возвращает тип параметра по полученной строке
        PARAM_TYPE GetParamType(std::string_view argv) {
            return _COMMAND_VARIANTS.count(argv) ? _COMMAND_VARIANTS.at(argv) : PARAM_TYPE::NOAP;
        }            

    } // namespace detail

} // namespace settings
