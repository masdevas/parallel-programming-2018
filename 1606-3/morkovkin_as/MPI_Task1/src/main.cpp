#include <iostream>
#include <mpi.h>
#include "matrix.hpp"
#include <iostream>
#include <mpi.h>
#include <climits>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int process_rank, process_count;
    double start_time = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    int rows = std::stoi(std::string(argv[1]));
    int columns = std::stoi(std::string(argv[2]));
    int low_limit = std::stoi(std::string(argv[3]));
    int high_limit = std::stoi(std::string(argv[4]));
    Matrix<int> *matrix = nullptr;
    if (process_count <= 1) {
        return 1;
    }
    if (process_rank == 0) {
        matrix = new Matrix<int>(rows, columns);
        matrix->FillRand(low_limit, high_limit);
        start_time = MPI_Wtime();
        if (columns < 10 && rows < 10) {
            matrix->Show();
        }
    }
    int rows_per_proc = rows / process_count;
    int *send = nullptr;
    if (process_rank == 0) {
        send = matrix->Data();
    }
    int *got_rows = new int[rows_per_proc * columns];
    MPI_Scatter(send, rows_per_proc * columns, MPI_FLOAT, got_rows,
                rows_per_proc * columns, MPI_FLOAT, 0, MPI_COMM_WORLD);
    int local_max = INT_MIN;
    for (int i = 0; i < rows_per_proc * columns; ++i) {
        if (got_rows[i] > local_max) {
            local_max = got_rows[i];
        }
    }
    int max;
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Reduce(&local_max, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    int tail = rows % process_count;
    int tail_max = INT_MIN;
    int local_tail_max;
    if (tail != 0) {
        if (process_rank == 0) {
            int start_pos = rows_per_proc * process_count * columns;
            for (int i = 1; i < tail; ++i) {
                MPI_Send(matrix->Data() + start_pos + i * columns,
                        columns, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
            got_rows = matrix->Data() + start_pos;
            local_tail_max = INT_MIN;
            for (int i = 0; i < columns; ++i) {
                if (got_rows[i] > local_tail_max) {
                    local_tail_max = got_rows[i];

                }
            }
        } else if (process_rank > 0 && process_rank < tail) {
            MPI_Recv(got_rows, columns, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            local_tail_max = INT_MIN;
            for (int i = 0; i < columns; ++i) {
                if (got_rows[i] > local_tail_max) {
                    local_tail_max = got_rows[i];
                }
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Reduce(&local_tail_max, &tail_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    }

    if (process_rank == 0) {
        std::cout << '\n' << "Tail is " << rows % process_count << '\n';

        std::cout << "Firts max is " << max << '\n';
        std::cout << "Tail max is " << tail_max << '\n';
        std::cout << "Absolute max is " << (tail_max > max ? tail_max : max) << '\n';
        std::cout << "Wasted time is " << MPI_Wtime() - start_time << '\n';
    }

    if (process_rank == 0) {
        start_time = MPI_Wtime();
        int max = INT_MIN;
        for (int i = 0; i < columns * rows; ++i) {
            if (matrix->Data()[i] > max) {
                max = matrix->Data()[i];
            }
        }
        std::cout << "***************" << '\n';
        std::cout << "Absolute max is " << max << '\n';
        std::cout << "Wasted time is " << MPI_Wtime() - start_time << '\n';
    }

    MPI_Finalize();
    return 0;
}