
#include "Game.hpp"
#include <iostream>


int main(int argc, char* args[])
{
    try {
        SDL_version compiled;
        SDL_version linked;

        SDL_VERSION(&compiled);
        SDL_GetVersion(&linked);
        printf("We compiled against SDL version %d.%d.%d ...\n",
               compiled.major, compiled.minor, compiled.patch);
        printf("But we are linking against SDL version %d.%d.%d.\n\n",
               linked.major, linked.minor, linked.patch);
        
        Game* g = new Game("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);
        
        
        while (g->is_running()) {
            g->run();
        }
        delete g;
        g = nullptr;
        return 0;
    }
    catch (std::invalid_argument e) {
        std::cout << e.what();
        return 1;
    }
    catch (std::logic_error e){
        std::cout << e.what();
        return 2;
    }
    catch (std::runtime_error e){
        std::fprintf(stderr, "%s\n", e.what());
        return 3;
    }
}
