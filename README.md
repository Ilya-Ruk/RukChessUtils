# RukChessUtils
Utils for usage with the RukChessTrainer.

## split_file
Split FEN-file into validation (10%) and training (90%) data sets.

#### Build

    gcc -O3 -Wall -Wextra -Wshadow -flto split_file.cpp -o split_file.exe

#### Usage

    split_file.exe file_in.fen file_valid.fen file_train.fen

## hidden_weights
Extracts the weights of the hidden layer from the neural network file.

#### Build

    gcc -O3 -Wall -Wextra -Wshadow -flto hidden_weights.cpp -o hidden_weights.exe

#### Usage

    hidden_weights.exe rukchess.nnue hidden_weights.txt
