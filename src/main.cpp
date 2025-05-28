#include "cli.h"
#include "utrello.h"

int main(int argc, char* argv[]){
    const string holidayFileAddress = argv[1];
    shared_ptr<UTrello> app = make_shared<UTrello>(holidayFileAddress);
    CliHandler cliHandler = CliHandler(app);
    cliHandler.start();

    return 0;
}