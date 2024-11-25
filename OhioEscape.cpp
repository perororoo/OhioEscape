#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <conio.h>
#include <wchar.h>
#include <windows.h>


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

class Game {
private:
protected:
  static int gameState;
  int wallNumber;

public:
  Game() {
    gameState = 0;
  };

  void startGame() {
    gameState = 1;
  };

  void stopGame() {
    gameState = 0;
  };

  void endGame() {
    gameState = -1;
  };
};

int Game::gameState;

class Player : public Game {
protected:
  static int playerPosition;
  static int rizz;
  static int choiceStorage;
  std::string userInput;

public:
  Player() {

  }

  int getUserInput() {
    int userInput = getch();

    return userInput;
  };

  int getRizz() {
    return rizz;
  };

  int fetchUserChoice() {
    return choiceStorage;
  };

  void choiceUseLife() {
    choiceStorage = 0;
  };

  void chooseGacha() {
    choiceStorage = 1;
  };

  void resetPlayerPosition() {
    playerPosition = 1;
  };
};

int Player::playerPosition = 1;
int Player::choiceStorage = 0;
int Player::rizz = 7;

class Map : public Game {
public:
  static std::vector<std::vector<int>> walls;

  void generateMap() {
    for (int i = 0; i < 2; i++) {
      if (i != 1) {
        for (int j = 0; j < 5; j++) {
          walls[i][j] = rand() % 6;
          if (walls[i][j] == 0) {
            walls[i][j] += 2;
          };
        };
      }
      else if (i == 1) {
        for (int j = 0; j < 5; j++) {
          walls[i][j] = rand() % 6;
          if (walls[i][j] == 0) {
            walls[i][j] += 2;
          };
          if (walls[0][j] && walls[i][j] == 5) {
            walls[0][j] -= 1;
          };
        };
      };

    };
  };
};

std::vector<std::vector<int>> Map::walls(5, std::vector<int>(5, 0));

class GameLogic : public Player, public Map {
protected:
  static int obstacleCount;
  static std::vector<int> currentObstacle;

public:
  GameLogic() {

  };

  int getGameState() {
    if (gameState == 1) {
      return 1;
    }
    else {
      return 0;
    };
  };

  void getCurrentObstacle() {
    currentObstacle[0] = walls[0][obstacleCount];
    currentObstacle[1] = walls[1][obstacleCount];
  };

  void incrementObstacleCount() {
    obstacleCount++;
  };

  int checkIfGameEnd() {
    if (obstacleCount == 5) {
      return 1;
    }
    else {
      return 0;
    };
  };
};

std::vector<int> GameLogic::currentObstacle(2, 0);
int GameLogic::obstacleCount = 0;

class Choice : public GameLogic {
protected:
  static int gachaRoll;
public:

  void useLife() {
    playerPosition += currentObstacle[1];
    rizz -= currentObstacle[1];
  };

  void gacha() {
    if (playerPosition == 1) {
      gachaRoll = rand() % 10;
      playerPosition += gachaRoll - 1;
    }
    else {
      gachaRoll = rand() % 7;
      playerPosition += gachaRoll - 1;
    };

    if (playerPosition > 5) {

      if ((playerPosition - 5) < (~(currentObstacle[0] - 6) + 1) && playerPosition >= currentObstacle[1]) {
        rizz += 3;
      };
      if ((playerPosition - 5) >= (~(currentObstacle[0] - 6) + 1)) {
        rizz = rizz - currentObstacle[0];
      };
    }
    else if (playerPosition <= 5) {
      if (playerPosition > currentObstacle[0]) {
        rizz += 3;
      }
      else {
        rizz -= currentObstacle[0];
      };
    };
  };
};

int Choice::gachaRoll = 0;

class Printer : public GameLogic, protected Choice {
public:
  void printStartMessage() {
    std::cout << "Ohio Escape" << '\n';
    std::cout << "Can you escape all 5 checkpoints to get out of Ohio?" << "\n\n";
    std::cout << "Press any key to rizz all over the place and start mogging the betas";

  };

  void printUserInterface(int input) {
    if (input == 1) {
      std::cout << '\n' << "rizz: " << rizz << "                                         " << "Checkpoints Mogged: " << obstacleCount << '\n';
      std::cout << "-----------------------------------------------------------------------" << '\n';
      std::cout << (playerPosition == 10 ? "(You) --> \U0001F426 " : "             ") << "      " << ((currentObstacle[0] >= 1) ? 'v' : ' ') << '\n';
      std::cout << (playerPosition == 9 ? "(You) --> \U0001F426 " : "             ") << "      " << ((currentObstacle[0] >= 2) ? 'v' : ' ') << '\n';
      std::cout << (playerPosition == 8 ? "(You) --> \U0001F426 " : "             ") << "      " << ((currentObstacle[0] >= 3) ? 'v' : ' ') << '\n';
      std::cout << (playerPosition == 7 ? "(You) --> \U0001F426 " : "             ") << "      " << ((currentObstacle[0] >= 4) ? 'v' : ' ') << '\n';
      std::cout << (playerPosition == 6 ? "(You) --> \U0001F426 " : "             ") << "      " << ((currentObstacle[0] >= 5) ? 'v' : ' ') << '\n';

      std::cout << (playerPosition == 5 ? "(You) --> \U0001F426 " : "             ") << "      " << ((currentObstacle[1] >= 5) ? '^' : ' ') << '\n';
      std::cout << (playerPosition == 4 ? "(You) --> \U0001F426 " : "             ") << "      " << ((currentObstacle[1] >= 4) ? '^' : ' ') << '\n';
      std::cout << (playerPosition == 3 ? "(You) --> \U0001F426 " : "             ") << "      " << ((currentObstacle[1] >= 3) ? '^' : ' ') << '\n';
      std::cout << (playerPosition == 2 ? "(You) --> \U0001F426 " : "             ") << "      " << ((currentObstacle[1] >= 2) ? '^' : ' ') << '\n';
      std::cout << (playerPosition == 1 ? "(You) --> \U0001F426 " : "             ") << "      " << ((currentObstacle[1] >= 1) ? '^' : ' ') << '\n';
      std::cout << "-----------------------------------------------------------------------" << '\n';
    };
  };

  void printResult(int choice) {
    if (choice == 0) {
      system("cls");
      std::cout << '\n' << "rizz: " << rizz << "                                         " << "Checkpoints Mogged: " << obstacleCount << '\n';
      std::cout << "-----------------------------------------------------------------------" << '\n';
      std::cout << (playerPosition == 10 ? "       (You) --> \U0001F426 " : currentObstacle[0] >= 1 ? "                   v" : " "); std::cout << '\n';
      std::cout << (playerPosition == 9 ? "        (You) --> \U0001F426 " : currentObstacle[0] >= 2 ? "                   v" : " "); std::cout << '\n';
      std::cout << (playerPosition == 8 ? "        (You) --> \U0001F426 " : currentObstacle[0] >= 3 ? "                   v" : " "); std::cout << '\n';
      std::cout << (playerPosition == 7 ? "        (You) --> \U0001F426 " : currentObstacle[0] >= 4 ? "                   v" : " "); std::cout << '\n';
      std::cout << (playerPosition == 6 ? "        (You) --> \U0001F426 " : currentObstacle[0] >= 5 ? "                   v" : " "); std::cout << '\n';

      std::cout << (playerPosition == 5 ? "        (You) --> \U0001F426 " : currentObstacle[1] >= 5 ? "                   ^" : " "); std::cout << '\n';
      std::cout << (playerPosition == 4 ? "        (You) --> \U0001F426 " : currentObstacle[1] >= 4 ? "                   ^" : " "); std::cout << '\n';
      std::cout << (playerPosition == 3 ? "        (You) --> \U0001F426 " : currentObstacle[1] >= 3 ? "                   ^" : " "); std::cout << '\n';
      std::cout << (playerPosition == 2 ? "        (You) --> \U0001F426 " : currentObstacle[1] >= 2 ? "                   ^" : " "); std::cout << '\n';
      std::cout << (playerPosition == 1 ? "        (You) --> \U0001F426 " : currentObstacle[1] >= 1 ? "                   ^" : " "); std::cout << '\n';
      std::cout << "-----------------------------------------------------------------------\n\n";
      std::cout << "You chose to pay the Fanum tax and lost -" << currentObstacle[1] << " rizz. \n\n";
      std::cout << (rizz == 0 ? "Game Over (Skill issue) \U0001F480 \U0001F480 \U0001F480 \n\n" : "");
      std::cout << (rizz < 0 ? "Bro has negative rizz now whathesigma \U0001F480 \U0001F480 \U0001F480 \n\n" : "");
      std::cout << (rizz > 0 ? "Press any key to continue!! \n" : "Press any key to continue.\n");

      getch();
      system("cls");
    };

    if (choice == 1) {
      system("cls");
      std::cout << '\n' << "rizz: " << rizz << "                                         " << "Checkpoints Mogged: " << obstacleCount << '\n';
      std::cout << "-----------------------------------------------------------------------" << '\n';
      std::cout << (playerPosition == 10 ? "       (You) --> \U0001F426 " : currentObstacle[0] >= 1 ? "                   v" : " "); std::cout << '\n';
      std::cout << (playerPosition == 9 ? "        (You) --> \U0001F426 " : currentObstacle[0] >= 2 ? "                   v" : " "); std::cout << '\n';
      std::cout << (playerPosition == 8 ? "        (You) --> \U0001F426 " : currentObstacle[0] >= 3 ? "                   v" : " "); std::cout << '\n';
      std::cout << (playerPosition == 7 ? "        (You) --> \U0001F426 " : currentObstacle[0] >= 4 ? "                   v" : " "); std::cout << '\n';
      std::cout << (playerPosition == 6 ? "        (You) --> \U0001F426 " : currentObstacle[0] >= 5 ? "                   v" : " "); std::cout << '\n';

      std::cout << (playerPosition == 5 ? "        (You) --> \U0001F426 " : currentObstacle[1] >= 5 ? "                   ^" : " "); std::cout << '\n';
      std::cout << (playerPosition == 4 ? "        (You) --> \U0001F426 " : currentObstacle[1] >= 4 ? "                   ^" : " "); std::cout << '\n';
      std::cout << (playerPosition == 3 ? "        (You) --> \U0001F426 " : currentObstacle[1] >= 3 ? "                   ^" : " "); std::cout << '\n';
      std::cout << (playerPosition == 2 ? "        (You) --> \U0001F426 " : currentObstacle[1] >= 2 ? "                   ^" : " "); std::cout << '\n';
      std::cout << (playerPosition == 1 ? "        (You) --> \U0001F426 " : currentObstacle[1] >= 1 ? "                   ^" : " "); std::cout << '\n';
      std::cout << "-----------------------------------------------------------------------\n\n";
      std::cout << "Your goofy ahh rolled a " << gachaRoll << ". " << (gachaRoll == 0 ? "What the sigma.." : " ") << (gachaRoll == 10 ? "Rolled too high RIP Bozo L" : " ") << "\n";
      std::cout << (rizz < 0 ? "NAHHHH WHY BRO HAS NEGATIVE RIZZ NOW AIN'T NO WAYYYY \U0001F62D \U0001F62D \U0001F62D \n\n" : "");
      std::cout << (rizz == 0 ? "Bro fell off \U0001F480 \U0001F480 \U0001F480 \n\n" : "");
      std::cout << (rizz > 0 ? "Press any key to continue!! \n" : "Press any key to continue.\n");
      getch();
      system("cls");
    };
  };

  void printChoices(int input) {
    switch (input)
    {
    case 0:
      std::cout << "  Actions: |  ";
      wprintf(L"\x1b[30;107m Jump ");
      wprintf(L"\x1b[39;49m ");
      std::cout << " |  Gacha                                           " << '\n';
      std::cout << '\n';
      std::cout << "Description: \n";
      std::cout << " Choose to pay the Fanum tax to get through a checkpoint. \n - Uses your rizz points to mog the poles.";
      break;

    case 1:
      std::cout << "  Actions: |   Jump   | ";
      wprintf(L"\x1b[30;107m Gacha ");
      wprintf(L"\x1b[39;49m                                          \n");
      std::cout << '\n';
      std::cout << "Description: \n";
      std::cout << " LET'S GO GAMBLING!! \n - Hit either of the checkpoint barriers and your rizz points get a deduction. Hit neither and you get +3 rizz points.";
      break;

    default:
      break;
    }

  };

  void printAllWalls() { // for debug
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 5; j++) {
        std::cout << walls[i][j] << ' ';
      };
      std::cout << '\n';
    };
    std::cout << "obstacleCount: " << obstacleCount;
    std::cout << '\n';
  };

  void printResult() {

  };
};

int main() {
  //initialize runtime components
  srand(time(0));

  SetConsoleOutputCP(CP_UTF8);

  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hOut == INVALID_HANDLE_VALUE)
  {
    return GetLastError();
  }

  DWORD dwMode = 0;
  if (!GetConsoleMode(hOut, &dwMode))
  {
    return GetLastError();
  }

  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  if (!SetConsoleMode(hOut, dwMode))
  {
    return GetLastError();
  }

  //initialize game
  char test;
  Game game;
  Map map;
  Player rizzler;
  GameLogic gameLogic;
  Choice choice;
  Printer printer;

  printer.printStartMessage();

  getch();

  system("cls");

  game.startGame();
  map.generateMap();
  gameLogic.getCurrentObstacle();

  printer.printUserInterface(gameLogic.getGameState());
  printer.printChoices(0);

  while (gameLogic.getGameState() == 1 && gameLogic.checkIfGameEnd() == 0)
  {

    switch (rizzler.getUserInput()) {
    case KEY_LEFT:
      system("cls");
      rizzler.choiceUseLife();
      printer.printUserInterface(gameLogic.getGameState());
      printer.printChoices(0);

      //debug
      /* std::cout << '\n';
      printer.printAllWalls(); */
      break;
    case KEY_RIGHT:
      system("cls");
      rizzler.chooseGacha();
      printer.printUserInterface(gameLogic.getGameState());
      printer.printChoices(1);

      //debug
      /* std::cout << '\n';
      printer.printAllWalls(); */
      break;
    case KEY_ENTER:
      system("cls");
      printer.printUserInterface(gameLogic.getGameState());

      if (rizzler.fetchUserChoice() == 0) {
        choice.useLife();
        printer.printResult(0);
        if (rizzler.getRizz() > 0) {
          rizzler.resetPlayerPosition();
          gameLogic.incrementObstacleCount();
          gameLogic.getCurrentObstacle();
          rizzler.choiceUseLife();
          printer.printUserInterface(gameLogic.getGameState());
          printer.printChoices(0);
        }
        else if (rizzler.getRizz() <= 0) {
          game.stopGame();
        };
        continue;

        //debug
        /* std::cout << '\n';
        printer.printAllWalls(); */
      }
      else if (rizzler.fetchUserChoice() == 1) {
        choice.gacha();
        printer.printResult(1);
        if (rizzler.getRizz() > 0) {
          rizzler.resetPlayerPosition();
          gameLogic.incrementObstacleCount();
          gameLogic.getCurrentObstacle();
          rizzler.choiceUseLife();
          printer.printUserInterface(gameLogic.getGameState());
          printer.printChoices(0);
        }
        else if (rizzler.getRizz() <= 0) {
          game.stopGame();
        };
        continue;

        //debug
        /* std::cout << '\n';
        printer.printAllWalls(); */
      };
      break;
    default:
      break;
    }
  };
  system("cls");
  if (rizzler.getRizz() > 0) {
    std::cout << "\nOh my god you're so skibidi truly the sigma among all the alphas in Ohio \n";
    std::cout << "\nYou Won !!! :D\n";
    std::cout << "\nPress any key to exit the program!!";
    getch();
  };

  if (rizzler.getRizz() <= 0) {
    std::cout << "\nYou Lost!! :C\n";
    std::cout << "\nPress any key to exit the program. Better luck next time!";
    getch();
  };
}