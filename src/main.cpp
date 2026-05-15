#include "checkmanager.h"
#include "utils.hpp"

int main(int argc, char *argv[])
{
    try 
    {
        auto args = Utils::parse(argc, argv);
        CheckManager manager(args.interval, args.directory, args.reportType);
        manager.run();
    } catch (const std::exception &e) 
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}