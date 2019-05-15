#include "ui.h"

namespace GameLogic
{

GameUI::GameUI() {}

GameUI::~GameUI() {}

GameMainMenuUI::GameMainMenuUI() {}

void GameMainMenuUI::Draw() const
{
    std::cout << "\033c";
    std::cout << " ------------------------ " << std::endl;
    std::cout << " Welcome to Tower Defence " << std::endl;
    std::cout << "    -Game By sukkryst-    " << std::endl;
    std::cout << " ------------------------ " << std::endl;

    if (current == 0)
        std::cout << "       \033[0;36m> \033[0;37mPlay Game        " << std::endl;
    else
        std::cout << "         Play Game        " << std::endl;

    if (current == 1)
        std::cout << "         \033[0;36m> \033[0;37mHelp           " << std::endl;
    else
        std::cout << "           Help           " << std::endl;

    if (current == 2)
        std::cout << "         \033[0;36m> \033[0;37mExit           " << std::endl;
    else
        std::cout << "           Exit           " << std::endl;
}

void GameMainMenuUI::Move(const int & x, const int & y)
{
    current += y;
    if (current >= 3)
        current = 0;
        
    if (current < 0)
        current = 2;
}

void GameMainMenuUI::Continue() {}

const int GameMainMenuUI::GetState() const
{
    return current == 0 ? 2 : current == 1 ? 3 : 0;
}

const std::string GameMainMenuUI::GetMsg() const
{
    return "";
}

GameMainMenuUI::~GameMainMenuUI() {}

GameHelpUI::GameHelpUI() {}

void GameHelpUI::Draw() const
{
    std::cout << "\033c";
    std::cout << " ------------------------ " << std::endl;
    std::cout << " If not modified controls " << std::endl;
    std::cout << "  Arrows - movement       " << std::endl;
    std::cout << "   Enter - confirmation   " << std::endl;
    std::cout << "         - build tower    " << std::endl;
    std::cout << "   Space - next turn      " << std::endl;
    std::cout << "       Q - next cursor    " << std::endl;
    std::cout << "         - next tower     " << std::endl;
    std::cout << " ------------------------ " << std::endl
         << std::endl;
    std::cout << "   Press Enter to close   " << std::endl;
}

void GameHelpUI::Move(const int & x, const int & y) {}

void GameHelpUI::Continue() {}

const int GameHelpUI::GetState() const
{
    return 0;
}

const std::string GameHelpUI::GetMsg() const
{
    return "";
}

GameHelpUI::~GameHelpUI() {}

GameLevelSelectUI::GameLevelSelectUI()
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("./examples/maps")) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (std::string(ent->d_name).find("info") == std::string::npos && std::string(ent->d_name).find("lvl") != std::string::npos)
            {
                _lvls.push_back(ent->d_name);
            }
        }
        closedir(dir);
    }
    for (auto i = _lvls.begin(); i < _lvls.end(); i++)
        _valid.push_back(Map(*i).IsValid());
}

void GameLevelSelectUI::Draw() const
{
    std::cout << "\033c";
    std::cout << " ------------------------ " << std::endl;
    std::cout << "     Select Game Level    " << std::endl;
    std::cout << " ------------------------ " << std::endl;

    int i = 0;
    for (auto t = _lvls.begin(); t < _lvls.end(); t++)
    {
        if (_valid[i])
            std::cout << "         ";
        else
            std::cout << "   ";

        if (i == current)
            std::cout << "\033[0;36m> ";
        else
            std::cout << "  ";

        if (_valid[i])
            std::cout << "\033[0;37m" << *t << std::endl;
        else
            std::cout << "\033[0;33m"
                 << "Not Valid: " << *t << "!\033[0;37m" << std::endl;

        i++;
    }

    if (current == _lvls.size())
        std::cout << "         \033[0;36m> \033[0;37mLoad           " << std::endl;
    else
        std::cout << "           Load           " << std::endl;

    if (current == _lvls.size() + 1)
        std::cout << "         \033[0;36m> \033[0;37mExit           " << std::endl;
    else
        std::cout << "           Exit           " << std::endl;
}

void GameLevelSelectUI::Move(const int & x, const int & y)
{
    current += y;
    if (current < 0)
        current = _lvls.size() + 1;

    if (current > _lvls.size() + 1)
        current = 0;
}

void GameLevelSelectUI::Continue() {}

const int GameLevelSelectUI::GetState() const
{
    return current < _lvls.size() ? current : current == _lvls.size() + 1 ? -1 : -2;
}

const std::string GameLevelSelectUI::GetMsg() const
{
    if (GetState() != -1)
        return _lvls[current];
    return "";
}

GameLevelSelectUI::~GameLevelSelectUI() {}

} // namespace GameLogic