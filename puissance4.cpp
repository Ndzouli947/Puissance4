#include <iostream>
#include <string>


void drawGrid(int grid[7][6]);
bool playTurn(int grid[7][6], int column, int player);
bool checkVictory(int grid[7][6], int player);
int getComputerMove(int grid[7][6]);

int main(int argc, char** argv) {
    int grille[7][6] = {};
    std::string choix;
    int player1Score = 0, player2Score = 0;
    bool JouerContreOrdi = true;
    int player = 1;





    drawGrid(grille);

    while (true) {
        std::cout << "Joueur " << player << " -> col :";

        if (player == 2 && JouerContreOrdi) {
            // Tour de l'ordinateur
            int col = getComputerMove(grille);
            std::cout << col << "\n";
            if (!playTurn(grille, col, player)) continue;
        } else {
            // Tour du joueur
            std::cin >> choix;
            if (choix == "exit")
                break;

            bool success = false;
            if (choix.size() == 1 && choix[0] >= '1' && choix[0] <= '7') {
                int col = choix[0] - '0';
                success = playTurn(grille, col, player);
            }

            // Utilise "clear" sur les systèmes Unix/Linux
            system("CLS");

            if (!success) {
                std::cout << "Votre choix est incorrect\n";
                drawGrid(grille);
                continue;
            }
        }

        // Vérification de la victoire
        if (checkVictory(grille, player)) {
            drawGrid(grille);
            std::cout << "Le Joueur " << player << "  gagne la partie!\n";
            if (player == 1)
                ++player1Score;
            else
                ++player2Score;

            // Affichage des scores et remise à zéro de la grille
            std::cout << "SCORE\nJoueur 1: " << player1Score << " | ";
            if (JouerContreOrdi)
                std::cout << "Ordinateur: " << player2Score << "\n";
            else
                std::cout << "Joueur 2: " << player2Score << "\n";


            continue;
        }

        // Changement de joueur
        player = (player == 1) ? 2 : 1;
        drawGrid(grille);
    }

    return 0;
}

void drawGrid(int grille[7][6]) {
    for (int ligne = 0; ligne < 6; ligne++) {
        std::cout << "|";
        for (int col = 0; col < 7; col++) {
            if (grille[col][ligne] == 1) std::cout << "\033[31m*\033[37m";
            else if (grille[col][ligne] == 2) std::cout << "\033[32m*\033[37m";
            else std::cout << " ";
            std::cout << "|";
        }
        std::cout << "\n";
    }
}

bool playTurn(int grid[7][6], int column, int player) {
    if (column < 1 || column > 7) return false;
    for (int line = 5; line >= 0; line--) {
        if (grid[column - 1][line] == 0) {
            grid[column - 1][line] = player;
            return true;
        }
    }
    return false;
}

bool checkVictory(int grid[7][6], int player) {
    // Vérifie lignes, colonnes et diagonales
    for (int ligne = 0; ligne < 6; ligne++)
        for (int col = 0; col < 4; col++)
            if (grid[col][ligne] == player && grid[col + 1][ligne] == player &&
                grid[col + 2][ligne] == player && grid[col + 3][ligne] == player)
                return true;

    for (int col = 0; col < 7; col++)
        for (int ligne = 0; ligne < 3; ligne++)
            if (grid[col][ligne] == player && grid[col][ligne + 1] == player &&
                grid[col][ligne + 2] == player && grid[col][ligne + 3] == player)
                return true;

    for (int col = 0; col < 4; col++)
        for (int ligne = 0; ligne < 3; ligne++)
            if (grid[col][ligne] == player && grid[col + 1][ligne + 1] == player &&
                grid[col + 2][ligne + 2] == player && grid[col + 3][ligne + 3] == player)
                return true;

    for (int col = 0; col < 4; col++)
        for (int ligne = 3; ligne < 6; ligne++)
            if (grid[col][ligne] == player && grid[col + 1][ligne - 1] == player &&
                grid[col + 2][ligne - 2] == player && grid[col + 3][ligne - 3] == player)
                return true;

    return false;
}

int getComputerMove(int grid[7][6]) {
    int col;
    do {
        col = std::rand() % 7 + 1; // Génère une colonne aléatoire entre 1 et 7
    } while (grid[col - 1][0] != 0); // Assure que la colonne n'est pas pleine
    return col;
}