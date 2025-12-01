#include <iostream>
#include "GameView.h"
#include "GameScene.h"
#include <memory>

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    try
    {
        // NOTE: Если при загрузке карты будет выброшено исключение,
        //  то память утечёт. Избавиться от этого можно с помощью
        //  замены new/delete на make_unique и unique_ptr.
        auto gameView = std::unique_ptr<GameView>(NewGameView({ 800, 600 }));
        auto gameScene = std::unique_ptr<GameScene>(NewGameScene());

        // Аргумент типа `GameLogic*` будет преобразован в `void*`.
        EnterGameLoop(*gameView, UpdateGameScene, DrawGameScene, gameScene.get());
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}