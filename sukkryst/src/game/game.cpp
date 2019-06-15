#include "game.h"

namespace GameLogic
{

GameManager::GameManager()
{
    _state = MainMenu;
    _ui.push_back(new GameMainMenuUI());
    _ui.push_back(new GameHelpUI());
    _ui.push_back(new GameLevelSelectUI());

    //Loading Towers
    Tower *tow;
    tow = new BasicTower(std::make_pair(_cY, _cX), "basic");
    _towerPref.push_back(tow);
    tow = new IceTower(std::make_pair(_cY, _cX), "ice");
    _towerPref.push_back(tow);
    tow = new FireTower(std::make_pair(_cY, _cX), "fire");
    _towerPref.push_back(tow);
    tow = new MortarTower(std::make_pair(_cY, _cX), "mortar");
    _towerPref.push_back(tow);

    //Loading from consts
    _input.Set(_consts.GetUpKey(), _consts.GetDownKey(), _consts.GetLeftKey(), _consts.GetRightKey(), _consts.GetCancelKey(), _consts.GetConfirmKey(), _consts.GetNextKey(), _consts.GetChangeKey());

    GameLoop();
}

void GameManager::SwitchState(const GameState &nextState)
{
    _state = nextState;
    if (_state == Exit)
        _run = false;
}

void GameManager::LoadLevel(const std::string &name)
{
    currentMap = Map();
    currentMap = Map(name);

    Resize(currentMap.GetW(), currentMap.GetH());

    if (!currentMap.IsValid())
    {
        _name = "";
        SwitchState(MapSelect);
    }
    else
    {
        _name = name;
        SwitchState(InGame);
        Start();
    }

    std::vector<int> info = Extra::File<int>::LoadFromFile("./examples/maps/" + name + "info");
    _currentMoney = info.at(2);
    _income = info.at(3);
    _maxWave = info.at(4);

    int index = 0;
    int nu = 0;
    int ty = 0;

    _waveQueue = std::queue<int>();

    for (auto i = info.begin() + 5; i < info.end(); i++)
    {
        if (index == 0)
        {
            nu = *i;
        }

        if (index == 1)
        {
            ty = *i;
            for (int n = 0; n < nu; n++)
            {
                _waveQueue.push(ty);
            }
            index = -1;
        }

        index++;
    }
}

void GameManager::Save() const
{
    std::ofstream save;
    save.open("./examples/save");

    if (!save.is_open() || !save.good())
    {
        save.close();
        return;
    }

    save << _name << "\n";
    save << _currentMoney << "\n";
    save << _currentWave << "\n";
    save << _lives << "\n";
    save << _turn << "\n";

    for (auto i = _towers.begin(); i < _towers.end(); i++)
    {
        save << (*i)->GetPos().first << " " << (*i)->GetPos().second << " " << (*i)->GetType() << "-1"
             << "\n";
    }

    for (auto i = _enemies.begin(); i < _enemies.end(); i++)
    {
        save << (*i)->GetPos().first << " " << (*i)->GetPos().second << " " << (*i)->GetType() << " " << (*i)->GetHP() << "\n";
    }
    save.close();
}

void GameManager::Load()
{
    Start();
    std::ifstream inp("./examples/save");

    if (!inp.is_open() || !inp.good())
    {
        inp.close();
        return;
    }

    inp >> _name;

    int f = 0;
    int s = 0;
    int h = 0;
    int t = 0;

    LoadLevel(_name);

    inp >> _currentMoney;
    inp >> _currentWave;
    inp >> _lives;
    inp >> _turn;

    while (inp >> f >> s >> t >> h)
    {
        if (!inp.is_open() || !inp.good())
        {
            inp.close();
            break;
        }

        std::pair<int, int> p = std::make_pair(f, s);

        if (t == 0)
        {
            Unit *slime;
            slime = new Slime(p);
            slime->SetHP(h);
            _enemies.push_back(slime);
        }

        if (t == 1)
        {
            Unit *king;
            king = new SlimeKing(p);
            king->SetHP(h);
            _enemies.push_back(king);
        }

        if (t == 2)
        {
            Unit *orc;
            orc = new Orc(p);
            orc->SetHP(h);
            _enemies.push_back(orc);
        }

        if (t == 3)
        {
            Unit *gol;
            gol = new Golem(p);
            gol->SetHP(h);
            _enemies.push_back(gol);
        }

        if (t == -2)
        {
            Tower *tow;
            tow = new BasicTower(p, "basic");
            _towers.push_back(tow);
            currentMap.PlaceTower(p);
        }

        if (t == -3)
        {
            Tower *tow;
            tow = new FireTower(p, "fire");
            _towers.push_back(tow);
            currentMap.PlaceTower(p);
        }

        if (t == -4)
        {
            Tower *tow;
            tow = new IceTower(p, "ice");
            _towers.push_back(tow);
            currentMap.PlaceTower(p);
        }

        if (t == -5)
        {
            Tower *tow;
            tow = new MortarTower(p, "mortar");
            _towers.push_back(tow);
            currentMap.PlaceTower(p);
        }
    }

    for (int w = 0; w < _turn; w++)
    {
        if (!_waveQueue.empty())
            _waveQueue.pop();
    }

    inp.close();
    SwitchState(InGame);
}

void GameManager::ProcessInput()
{
    Key key = _input.Process();
    system("stty sane");

    switch (_state)
    {

    case InGame:
        switch (key)
        {
        case Key::Left:
            if (_cX > 0)
                _cX -= 1;
            break;

        case Key::Right:
            if (_cX < _w - 1)
                _cX += 1;
            break;

        case Key::Up:
            if (_cY > 0)
                _cY -= 1;
            break;

        case Key::Down:
            if (_cY < _h - 1)
                _cY += 1;
            break;

        case Key::Confirm:
            PlaceTower();
            break;

        case Key::Change:
            NextCursor();
            break;

        case Key::End:
            Save();
            SwitchState(MainMenu);
            break;

        case Key::Next:
            GameStep();
            break;
        }
        break;

    case MainMenu:
        switch (key)
        {
        case Key::Up:
            _ui[0]->Move(0, -1);
            break;

        case Key::Down:
            _ui[0]->Move(0, 1);
            break;

        case Key::Confirm:
            SwitchState(GetGameState(_ui[0]->GetState()));
            break;

        case Key::End:
            _run = false;
            break;
        }
        break;

    case Help:
        switch (key)
        {
        case Key::Up:
            break;

        case Key::Down:
            break;

        case Key::Confirm:
            SwitchState(MainMenu);
            break;

        case Key::End:
            _run = false;
            break;
        }
        break;

    case MapSelect:
        switch (key)
        {
        case Key::Up:
            _ui[2]->Move(0, -1);
            break;

        case Key::Down:
            _ui[2]->Move(0, 1);
            break;

        case Key::Confirm:
            if (_ui[2]->GetState() == -1)
                SwitchState(MainMenu);
            else if (_ui[2]->GetState() == -2)
                Load();
            else
                LoadLevel(_ui[2]->GetMsg());
            break;

        case Key::End:
            _run = false;
            break;
        }
        break;
    }
}

const GameState GameManager::GetGameState(const int &i) const
{
    if (i == 0)
        return Exit;

    if (i == 1)
        return MainMenu;

    if (i == 2)
        return MapSelect;

    if (i == 3)
        return Help;

    if (i == 4)
        return InGame;
}

void GameManager::PlaceTower()
{
    if (_currentTower != -1)
    {
        Tower *tow;

        if (_currentTower == 0)
            tow = new BasicTower(std::make_pair(_cY, _cX), "basic");

        if (_currentTower == 1)
            tow = new IceTower(std::make_pair(_cY, _cX), "ice");

        if (_currentTower == 2)
            tow = new FireTower(std::make_pair(_cY, _cX), "fire");

        if (_currentTower == 3)
            tow = new MortarTower(std::make_pair(_cY, _cX), "mortar");

        if (_currentMoney - tow->GetPrice() >= 0)
        {
            bool tmp;
            tmp = currentMap.PlaceTower(std::make_pair(_cY, _cX));

            if (tmp)
            {
                _currentMoney -= tow->GetPrice();

                for (auto i = _enemies.begin(); i < _enemies.end(); i++)
                {
                    (*i)->ClearPath();
                }

                _towers.push_back(tow);
            }
            else
                delete tow;
        }
        else
            delete tow;
    }
}

void GameManager::GameLoop()
{
    system("stty sane");

    switch (_state)
    {
    case MainMenu:
        _ui[0]->Draw();
        break;

    case Help:
        _ui[1]->Draw();
        break;

    case InGame:
        DrawInGame();
        break;

    case MapSelect:
        _ui[2]->Draw();
        break;

    default:
        break;
    }

    ProcessInput();
    system("stty sane");
    Clear();

    if (_state == GameState::Exit)
        _run = false;

    if (_run)
        GameLoop();
}

void GameManager::Resize(const int &x, const int &y)
{
    for (int i = 0; i < _h; i++)
    {
        if (_display[i] != nullptr)
            delete[] _display[i];

        if (_colors[i] != nullptr)
            delete[] _colors[i];
    }

    if (_display != nullptr)
        delete[] _display;

    if (_colors != nullptr)
        delete[] _colors;

    _colors = new Color *[y];
    _display = new char *[y];

    for (int i = 0; i < y; i++)
    {
        _colors[i] = new Color[x];
        _display[i] = new char[x];

        for (int t = 0; t < x; t++)
        {
            _display[i][t] = ' ';
            _colors[i][t] = White;
        }
    }

    _w = x;
    _h = y;
}

void GameManager::Start()
{
    _run = true;
    _currentTower = -1;
    _currentWave = 1;
    _lives = 10;
    _turn = 0;

    for (auto i = _enemies.begin(); i < _enemies.end(); i++)
        delete *i;

    for (auto i = _towers.begin(); i < _towers.end(); i++)
        delete *i;

    _towers.clear();
    _enemies.clear();
}

void GameManager::Clear()
{
    std::cout << "\033c";
    for (int i = 0; i < _h; i++)
        for (int t = 0; t < _w; t++)
            _colors[i][t] = White;
}

void GameManager::DrawInGame() const
{
    //Displaying Map
    currentMap.GetChars(_display);
    currentMap.GetColors(_colors);

    //Displaying Enemies
    for (auto i = _enemies.begin(); i < _enemies.end(); i++)
    {
        (*i)->GetChar(_display);
        (*i)->GetColor(_colors);
    }

    char tmp = _display[_cY][_cX];
    //Cursor
    _display[_cY][_cX] = 'x';
    _colors[_cY][_cX] = Green;

    //Displaying Towers
    for (auto i = _towers.begin(); i < _towers.end(); i++)
    {
        (*i)->GetChar(_display);
        (*i)->GetColor(_colors);
    }

    //Tower Distance
    if (_currentTower != -1)
    {
        for (int r = _towerPref[_currentTower]->GetDistance(); r >= 1; r--)
        {
            for (int ang = 0; ang < 360; ang += 1)
            {
                int tY = round(_cY + r * sin(ang));
                int tX = round(_cX + r * cos(ang));

                if (tY < 0 || tX < 0 || tX >= _w || tY >= _h)
                    continue;

                if (_display[tY][tX] == ' ')
                {
                    _display[tY][tX] = '+';
                    _colors[tY][tX] = Red;
                }
            }
        }
    }

    std::string col;

    for (int i = 0; i < _h; i++)
    {
        for (int t = 0; t < _w; t++)
        {
            switch (_colors[i][t])
            {
            case White:
                col = "\033[0;37m";
                break;

            case Black:
                col = "\033[0;30m";
                break;

            case Blue:
                col = "\033[0;34m";
                break;

            case Red:
                col = "\033[0;31m";
                break;

            case Green:
                col = "\033[0;32m";
                break;

            case Yellow:
                col = "\033[0;33m";
                break;

            case Magenta:
                col = "\033[0;35m";
                break;

            case Cyan:
                col = "\033[0;36m";
                break;

            default:
                col = "\033[0;37m";
                break;
            }

            std::cout << col << _display[i][t];
        }

        std::cout << std::endl;
    }

    //Display Main
    std::cout << "\033[0;37m ------------------------ " << std::endl;
    std::cout << "|        Lives: " << std::setw(2) << std::setfill(' ') << _lives << "       |" << std::endl;
    std::cout << " ------------------------ " << std::endl;
    std::cout << "| Wave: " << std::setw(2) << std::setfill('0') << _currentWave << "/" << std::setw(2) << std::setfill('0') << _maxWave << " Money: " << std::setw(3) << std::setfill('0') << _currentMoney << " |" << std::endl;
    std::cout << " ------------------------ " << std::endl;

    bool emp = true;
    if (_currentTower != -1)
    {
        std::cout << *_towerPref[_currentTower] << std::endl;
    }
    else
    {
        if (tmp == ' ')
        {
            for (auto i = _towers.begin(); i < _towers.end(); i++)
            {
                if ((*i)->GetPos().first == _cY && (*i)->GetPos().second == _cX)
                {
                    std::cout << (**i) << std::endl;
                    emp = false;
                    break;
                }
            }

            if (emp)
                std::cout << "|         empty          |" << std::endl;
        }
        else if (tmp == '#')
        {
            std::cout << "|          wall          |" << std::endl;
        }
        else
        {
            for (auto i = _enemies.begin(); i < _enemies.end(); i++)
            {
                if ((*i)->GetPos().first == _cY && (*i)->GetPos().second == _cX)
                {
                    std::cout << (**i) << std::endl;
                    emp = false;
                    break;
                }
            }

            if (emp)
                std::cout << "|         xxxxx          |" << std::endl;
        }
    }

    std::cout << " ------------------------ " << std::endl;
}

void GameManager::GameStep()
{
    if (_enemies.size() > 0)
    {
        if (_towers.size() > 0)
        {
            for (auto i = _towers.begin(); i < _towers.end(); i++)
            {
                (*i)->ProcessAttack(_enemies);
            }
        }

        for (auto i = _enemies.end() - 1; i >= _enemies.begin(); i--)
        {
            if (!(*i)->IsAlive())
            {
                delete *i;
                _enemies.erase(i);
            }
        }

        for (auto i = _enemies.end() - 1; i >= _enemies.begin(); i--)
        {
            (*i)->Move(currentMap);
            if (currentMap.ReachedEnd((*i)->GetPos()))
            {
                _lives -= (*i)->GetAtk();

                if (_lives <= 0)
                    SwitchState(MainMenu);

                delete *i;
                _enemies.erase(i);
            }
        }
    }

    _turn++;

    if (!_waveQueue.empty())
    {
        int sp = _waveQueue.front();
        if (sp == -2)
            _currentWave++;

        if (sp == 0)
        {
            Unit *slime;
            slime = new Slime(currentMap.GetS());
            _enemies.push_back(slime);
        }

        if (sp == 1)
        {
            Unit *king;
            king = new SlimeKing(currentMap.GetS());
            _enemies.push_back(king);
        }

        if (sp == 2)
        {
            Unit *orc;
            orc = new Orc(currentMap.GetS());
            _enemies.push_back(orc);
        }

        if (sp == 3)
        {
            Unit *gol;
            gol = new Golem(currentMap.GetS());
            _enemies.push_back(gol);
        }

        _waveQueue.pop();
    }
    else
    {
        if (_enemies.size() == 0)
            SwitchState(MainMenu);
    }

    _currentMoney += _income;

    if (_currentMoney > 999)
        _currentMoney = 999;
}

void GameManager::NextCursor()
{
    _currentTower++;

    if (_currentTower >= _towerPref.size())
        _currentTower = -1;
}

GameManager::~GameManager()
{
    for (int i = 0; i < _h; i++)
    {
        delete[] _colors[i];
        delete[] _display[i];
    }

    delete[] _colors;
    delete[] _display;

    for (auto i = _enemies.begin(); i < _enemies.end(); i++)
        delete *i;

    for (auto i = _towers.begin(); i < _towers.end(); i++)
        delete *i;

    for (auto i = _towerPref.begin(); i < _towerPref.end(); i++)
        delete *i;

    for (auto i = _ui.begin(); i < _ui.end(); i++)
        delete *i;
}

} // namespace GameLogic