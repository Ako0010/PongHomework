#pragma once

void clearScreen() {
    system("cls||clear");
}

class PongGame {
private:
    int width, height;
    int ballX, ballY;
    int ballDirX, ballDirY;
    int playerPaddleY, botPaddleY;
    int paddleHeight;
    int playerScore, botScore;

public:
    PongGame(int w, int h) {
        width = w;
        height = h;
        ballX = w / 2;
        ballY = h / 2;
        ballDirX = 1;
        ballDirY = 1;
        playerPaddleY = h / 2 - 2;
        botPaddleY = h / 2 - 2;
        paddleHeight = 4;
        playerScore = 0;
        botScore = 0;

        srand(static_cast<unsigned int>(time(0)));
    }

    void draw() {
        clearScreen();
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (j == 0 || j == width - 1) {
                    cout << "|";
                }
                else if (i == ballY && j == ballX) {
                    cout << (char)254;
                }
                else if (j == 1 && i >= playerPaddleY && i < playerPaddleY + paddleHeight) {
                    cout << (char)219;
                }
                else if (j == width - 2 && i >= botPaddleY && i < botPaddleY + paddleHeight) {
                    cout << (char)219;
                }
                else {
                    cout << " ";
                }
            }
            cout << "\n";
        }
        cout << "Score: Player = " << playerScore << " | Bot = " << botScore << "\n";
    }

    void input(char key) {
        if (key == 'w' && playerPaddleY > 0) {
            playerPaddleY--;
        }
        else if (key == 's' && playerPaddleY + paddleHeight < height) {
            playerPaddleY++;
        }
    }

    void Computervs() {
        int predictedBallY = ballY;

        if (ballDirX > 0) {
            int stepsToReachBot = width - 3 - ballX;
            predictedBallY += stepsToReachBot * ballDirY;

            while (predictedBallY < 0 || predictedBallY >= height) {
                if (predictedBallY < 0) predictedBallY = -predictedBallY;
                if (predictedBallY >= height) predictedBallY = 2 * (height - 1) - predictedBallY;
            }

            int errorChance = rand() % 100;
            if (errorChance < 50) {
                int errorMagnitude = rand() % 6 + 2;
                int direction = (rand() % 2 == 0) ? -1 : 1;
                predictedBallY += direction * errorMagnitude;
            }
        }

        if (predictedBallY < botPaddleY && botPaddleY > 0) {
            botPaddleY--;
        }
        else if (predictedBallY > botPaddleY + paddleHeight - 1 && botPaddleY + paddleHeight < height) {
            botPaddleY++;
        }
    }


    void logic() {
        ballX += ballDirX;
        ballY += ballDirY;

        if (ballY == 0 || ballY == height - 1) {
            ballDirY *= -1;
        }

        if (ballX == 2 && ballY >= playerPaddleY && ballY < playerPaddleY + paddleHeight) {
            ballDirX *= -1;
        }

        if (ballX == width - 3 && ballY >= botPaddleY && ballY < botPaddleY + paddleHeight) {
            ballDirX *= -1;
        }

        if (ballX == 0) {
            botScore++;
            resetBall();
        }
        else if (ballX == width - 1) {
            playerScore++;
            resetBall();
        }
    }

    void resetBall() {
        ballX = width / 2;
        ballY = height / 2;
        ballDirX *= -1;
        ballDirY = (rand() % 2 == 0) ? 1 : -1;
    }

    void run() {
        char key = 0;
        while (true) {
            draw();

            if (_kbhit()) {
                key = _getch();
            }

            input(key);
            Computervs();
            logic();

            Sleep(10);
        }
    }
};