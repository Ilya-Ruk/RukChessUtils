# RukChessUtils
Utils for usage with the RukChessTrainer.

## split_file
Split FEN-file into validation (5%) and training (95%) data sets.

#### Build

    gcc -O3 -Wall -Wextra -Wshadow -flto split_file.cpp -o split_file.exe

#### Usage

    split_file.exe file_in.fen file_valid.fen file_train.fen

## nnue_weights_biases
Extracts the weights and biases of the layers from the neural network file.

#### Build

    gcc -O3 -Wall -Wextra -Wshadow -flto nnue_weights_biases.cpp -o nnue_weights_biases.exe

#### Usage

    nnue_weights_biases.exe rukchess.nnue

## merge_files
Merge two files in one.

#### Build

    gcc -O3 -Wall -Wextra -Wshadow -flto merge_files.cpp -o merge_files.exe

#### Usage

    merge_files.exe file_in_1.fen file_in_2.fen file_out.fen

## shuffle
Shuffle positions.

#### Build

    gcc -O3 -Wall -Wextra -Wshadow -flto shuffle.cpp -o shuffle.exe

#### Usage

    shuffle.exe games_in.fen games_out.fen

## rand64
Distribution of random numbers for different pseudo-random number generators and obtaining a normal distribution.

#### Build

    gcc -O3 -Wall -Wextra -Wshadow -flto rand64.cpp -o rand64.exe
