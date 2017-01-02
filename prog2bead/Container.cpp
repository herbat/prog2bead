#include "Container.hpp"

void Container::addPipe(Pipe * pipe){
    pipes.emplace(pipe->name, pipe);
};
