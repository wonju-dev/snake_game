#include "GameOverScene.h"
#include "GameScene.h"
#include "WaitingScene.h"
#include "Utils.h"
#include <ncurses.h>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

GameOverScene::GameOverScene() {
}

GameOverScene::~GameOverScene() {}

void GameOverScene::Update(float eTime)
{
    refresh();
    Load();
    char answer = AskUserToPlayAgain();

    if (answer == 'y') {
        ChangeScene(new GameScene());
    }
    else if (answer == 'n')
        exit(0);
}
void GameOverScene::Render() {}

void GameOverScene::ClearCentre(float x, float y)
{
    int maxWidth, maxHeight;
    initscr();
    noecho();
    getmaxyx(stdscr, maxHeight, maxWidth);
    move((maxHeight / 3 * 2 / y), (maxWidth / x));
}

int GameOverScene::UserInput()
{
    int UserInput = getch();
    endwin();
    clear();

    return UserInput;
}

void GameOverScene::Load()
{
    std::ifstream readFile;
    string src = "scene/GameOverScene.txt";

    readFile.open(src);
    int height = 0;

    while (!readFile.eof())
    {
        char temp[120];
        readFile.getline(temp, 120);

        for (int width = 0; width < 58; ++width) {
            if (temp[width] == ' ') {
                move(height + 2, width + 2);
                addch(' ');
            }

            else {
                move(height + 2, width + 2);
                addch(char(219));
            }
        }

        ++height;
    }
}

int GameOverScene::AskUserToPlayAgain() {
    ClearCentre(3.5, 2);
    move(7, 25);
    printw("Restart? (y/n)");
    return UserInput();
}