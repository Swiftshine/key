#include <gfl/file.h>

gfl::File::File() {
    this->filesystem = NULL;
    /* clear filename */
    this->_20C = 0;
}

gfl::File::~File() { }