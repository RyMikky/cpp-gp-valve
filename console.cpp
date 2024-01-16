#include "console.h"

#include <exception>
#include <stdexcept>

namespace console {

    using namespace std::string_literals;

    template <typename Arg>
    void SetDataToArguments(settings::detail::PARAM_TYPE type, settings::Settings* data, Arg&& arg) {
        switch (type)
        {  
        case settings::detail::PARAM_TYPE::GAS_TYPE_STR:
            data->_gas_type_str = arg;
            break;

        case settings::detail::PARAM_TYPE::GAS_CELSIUM_TEMP:
            data->_gas_celsium_temp = physics::units::temperature::Cels(std::stof(std::forward<Arg>(arg)));
            break;

        case settings::detail::PARAM_TYPE::GAS_INPUT_PRESSURE:
            data->_gas_input_pressure = physics::units::pressure::MPa(std::stof(std::forward<Arg>(arg)));
            break;

        case settings::detail::PARAM_TYPE::GAS_OUTPUT_PRESSURE:
            data->_gas_output_pressure = physics::units::pressure::MPa(std::stof(std::forward<Arg>(arg)));
            break;

        case settings::detail::PARAM_TYPE::PIPE_STEEL_MARK:
            data->_pipe_steel_mark = arg;
            break;

        case settings::detail::PARAM_TYPE::PIPE_INNER_DIAMETER:
            data->_pipe_inner_diameter = math::units::Diameter(math::units::scale::mMeter(std::stof(std::forward<Arg>(arg))));
            break;

        case settings::detail::PARAM_TYPE::APERTURE_DIAMETER:
            data->_aperture_diameter = math::units::Diameter(math::units::scale::mMeter(std::stof(std::forward<Arg>(arg))));
            break;
        
        default:
            break;
        }
    }

    void ParseSingleCommand(settings::Settings* data, const char* line) {
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
            SetDataToArguments(type, data, argument);
        }
        else {
            settings::detail::PrintHelpListAndExit(std::cerr);
        }
    }
    
    settings::Settings ParseCommandLine(int args, char** argv) {

        if (!settings::detail::ParamCountIsCorrect(args)) {
            throw std::invalid_argument("command line has incorrect arguments count");
        }

        settings::Settings result;
        for (int i = 1; i != args; ++i) {
            ParseSingleCommand(&result, argv[i]);
        }

        return result; // воспользуемся RVO компилятора и тем, что у структуры имеются только перемещающие конструкторы
    }

} // namespace console 