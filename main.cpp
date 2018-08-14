#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

sf::Texture setTexture(std::string);

int main()
{

    int row = 10;//y
    int col = 10;//x
    int gameboard[10][10] = {0};
    int localX;
    int localY;
    int piecesInARow;
    int playerTurn;
    int playerTurnNum;
    int winningNumberofPieces = 4;//set to 1 less than you want

    bool winner;
    bool legalMoves;
    bool updateGame = true;

    string currentPlayer = "Player ";
    string gameOver = "Game Over\nNo valid moves";
    string playerWinner = "Player ";

    sf::RenderWindow window(sf::VideoMode(630, 680), "TicTacToe44");

    sf::Vector2i mousePosition;

    sf::Texture Tblank(setTexture("resources/empty.bmp"));
    sf::Texture Tcross(setTexture("resources/cross.bmp"));
    sf::Texture Tcircle(setTexture("resources/circle.bmp"));
    sf::Texture Tsquare(setTexture("resources/square.bmp"));
    sf::Texture Ttriangle(setTexture("resources/triangle.bmp"));

    sf::Sprite blank(Tblank);
    sf::Sprite cross(Tcross);
    sf::Sprite circle(Tcircle);
    sf::Sprite square(Tsquare);
    sf::Sprite triangle(Ttriangle);

    sf::Font gameoverFont;
    gameoverFont.loadFromFile("resources/Optien.ttf");
    sf::Font playerTurnFont;
    playerTurnFont.loadFromFile("resources/Optien.ttf");

    sf::Text gameoverString (gameOver, gameoverFont);
    gameoverString.setCharacterSize(75);
    gameoverString.setPosition(125,200);
    gameoverString.setColor(sf::Color::Red);

    sf::Text playerWinnerString (playerWinner, playerTurnFont);
    playerWinnerString.setCharacterSize(75);
    playerWinnerString.setPosition(125,200);
    playerWinnerString.setColor(sf::Color::Red);

    sf::Text playerTurnString (currentPlayer, playerTurnFont);
    playerTurnString.setCharacterSize(20);
    playerTurnString.setPosition(350,640);
    playerTurnString.setColor(sf::Color::White);

    playerTurn = 1;
    playerTurnNum = 0;
    legalMoves = true;
    winner = false;


    window.setKeyRepeatEnabled(false);

    //start game
    while (window.isOpen())
    {
        //debug //std::cout << "X: " << mousePosition.x<< " Y: " << mousePosition.y << " Player turn: " << playerTurn << " PlayerTurnNum: " << playerTurnNum <<endl;

        ostringstream convertPlayerTurn;
        ostringstream convertPlayerTurnNum;
        ostringstream convertPlayerWinner;

        window.clear();

        for(int a=0;a<10;a++){
                for(int z=0;z<10;z++){
                    switch(gameboard[a][z]){
                        case 0:
                            window.draw(blank);
                            blank.setPosition(a*63+1,z*63+1);
                            break;
                        case 1:
                            window.draw(cross);
                            cross.setPosition(a*63+1,z*63+1);
                            break;
                        case 2:
                            window.draw(circle);
                            circle.setPosition(a*63+1,z*63+1);
                            break;
                        case 3:
                            window.draw(square);
                            square.setPosition(a*63+1,z*63+1);
                            break;
                        case 4:
                            window.draw(triangle);
                            triangle.setPosition(a*63+1,z*63+1);
                            break;

                    }
                }
            }

        window.draw(playerTurnString);
        window.draw(cross);

        sf::Event event;

        while (window.pollEvent(event))//
        {

            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;


                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left&&updateGame==true)
                    {
                        mousePosition = sf::Mouse::getPosition(window);

                        if(mousePosition.y/63<10&&gameboard[mousePosition.x/63][mousePosition.y/63] == 0){
                           gameboard[mousePosition.x/63][mousePosition.y/63] = playerTurn;
                           playerTurnNum++;
                           break;
                        }
                    }
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::S&&updateGame==true)
                        playerTurnNum++;
                    break;

                default:
                    break;
            }

        }

        for(int x = 0; x < col; x++){
            for(int y = 0; y < row; y++){
                localY = y;
                localX = x;

                while(gameboard[y][x] != 0 && gameboard[y][x]==gameboard[--localY][x]){//check horizontal
                    piecesInARow++;
                    if(piecesInARow == winningNumberofPieces){
                        winner = true;
                    }
                }
                    piecesInARow = 0;
                    localY = y;

                while(gameboard[y][x] != 0 && gameboard[y][x]==gameboard[y][--localX]){//check vertical
                    piecesInARow++;
                    if(piecesInARow == winningNumberofPieces){
                        winner = true;
                    }
                }
                piecesInARow = 0;
                localX = x;

                while(gameboard[y][x] != 0 && gameboard[y][x]==gameboard[--localY][++localX]){//check diagonal /
                    piecesInARow++;
                    if(piecesInARow == winningNumberofPieces){
                        winner = true;
                    }
                }
                piecesInARow = 0;
                localX = x;
                localY = y;
                while(gameboard[y][x] != 0 && gameboard[y][x]==gameboard[--localY][--localX]){//check other diagonal
                    piecesInARow++;
                    if(piecesInARow == winningNumberofPieces){
                        winner = true;
                    }
                }
                piecesInARow = 0;
            }
        }

        if(playerTurnNum>=2){
            playerTurnNum=0;
            playerTurn++;
        }

        if(playerTurn>=5){//loops allowing each player to go twice
            playerTurn=1;
        }



        convertPlayerTurn << playerTurn;
        convertPlayerTurnNum << (playerTurnNum + 1);
        if(playerTurnNum==0)
            convertPlayerWinner << playerTurn-1;
        else
            convertPlayerWinner << playerTurn;

        playerWinner = "Player " + convertPlayerWinner.str() + " wins!";
        currentPlayer = "Player " + convertPlayerTurn.str() + ": move " + convertPlayerTurnNum.str();

        playerTurnString.setString(currentPlayer);
        playerWinnerString.setString(playerWinner);


        legalMoves=false;

        for(int i=0;i<10;i++){
            for(int g=0;g<10;g++){
                if(gameboard[i][g]==0){//when compiler finds a 0 it knows there are moves left
                    legalMoves=true;
                    break;
                }
            }
            if(legalMoves==true){
                break;
            }
        }

        if(legalMoves==false){
            window.clear();
            window.draw(gameoverString);
            updateGame = false;
        }else if(winner == true){
            window.draw(playerWinnerString);
            updateGame = false;
        }

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}

sf::Texture setTexture (std::string name){

    sf::Texture texture;

    texture.loadFromFile(name);
    texture.setSmooth(true);

    return texture;

}
