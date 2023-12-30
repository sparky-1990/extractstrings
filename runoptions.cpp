#include "runoptions.h"

RunOptions::RunOptions() {
}

RunOptions::~RunOptions()
{
    delete headerStream;
    delete header;

    delete translationStream;
    delete translation;
}
