#include "checkmanager.h"
#include "utils.hpp"

int main(int argc, char *argv[])
{
    auto args = Utils::parse(argc, argv);
    CheckManager manager(args.interval, args.directory, args.reportType);
    manager.run();
    return 0;
}