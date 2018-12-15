#include <iostream>
#include <mpi.h>
#include <cstring>
#include "png.hpp"

constexpr int Sqr(ColorType val) {
    return static_cast<int>(val) * val;
}

Pixel ApplyOperator(Pixel* buf, size_t size_x, uint32_t x, uint32_t y, int kernel[3][3]) {
    int res_red = 0, res_green = 0, res_blue = 0;
    for (uint32_t y_coord = y - 1; y_coord <= y + 1; ++y_coord) {
        for (uint32_t x_coord = x - 1; x_coord <= x + 1; ++x_coord) {
            res_red += kernel[y_coord - y + 1][x_coord - x + 1] * buf[y_coord * size_x + x_coord].red;
            res_green += kernel[y_coord - y + 1][x_coord - x + 1] * buf[y_coord * size_x + x_coord].green;
            res_blue += kernel[y_coord - y + 1][x_coord - x + 1] * buf[y_coord * size_x + x_coord].blue;
        }
    }
    return Pixel{
            Clamp(res_red, 0, 255),
            Clamp(res_green, 0, 255),
            Clamp(res_blue, 0, 255)
    };
}

Pixel* SobelFiltering(Pixel *buf, int count_recv_pixels, size_t size_x) {
    int x_kernel[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}
    };
    int y_kernel[3][3] = {
            {-1, -2, -1},
            {0, 0, 0},
            {1, 2, 1}
    };
    auto* pixels_tmp = new Pixel[count_recv_pixels];
    memset(pixels_tmp, 0, count_recv_pixels * sizeof(Pixel));
    size_t size_y_for_proc = count_recv_pixels / size_x;
    for (uint32_t y = 1; y < size_y_for_proc - 1; ++y) {
        for (uint32_t x = 1; x < size_x - 1; ++x) {
            Pixel x_res = ApplyOperator(buf, size_x, x, y, x_kernel);
            Pixel y_res = ApplyOperator(buf, size_x, x, y, y_kernel);
            pixels_tmp[y * size_x + x] = Pixel{
                    Clamp(static_cast<int>(sqrt(Sqr(x_res.red) + Sqr(y_res.red))), 0, 255),
                    Clamp(static_cast<int>(sqrt(Sqr(x_res.green) + Sqr(y_res.green))), 0, 255),
                    Clamp(static_cast<int>(sqrt(Sqr(x_res.blue) + Sqr(y_res.blue))), 0, 255)
            };
        }
    }
    delete[] buf;
    return pixels_tmp;
}

int CountPixelsSendForProcess(size_t size_x, size_t size_y, int number_process) {
    int process_count;
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    int for_each_y_centres = static_cast<int>((size_y - 2) / process_count);
    int limit_number = process_count;
    if (process_count > size_y - 2) {
        limit_number = static_cast<int>(size_y - 2);
        if (number_process >= limit_number) {
            return 0;
        } else {
            return size_x * 3;
        };
    } else {
        if ((number_process == process_count - 1) && ((size_y - 2) % process_count != 0)) {
            return static_cast<int>(for_each_y_centres * size_x + 2 * size_x +
                                    ((size_y - 2) % process_count) * size_x);
        } else {
            return static_cast<int>(for_each_y_centres * size_x + 2 * size_x);
        }
    }
}

int* CreateSendCounts(size_t size_x, size_t size_y) {
    int process_count;
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    int* send_counts = new int[process_count];
    for (size_t i = 0; i < process_count; ++i) {
        send_counts[i] = CountPixelsSendForProcess(size_x, size_y, i);
    }
    return send_counts;
}

void ShowImage(Image* image) {
    if (image->SizeX() <= 5 && image->SizeY() <= 5) {
        for (size_t i = 0; i < image->SizeX() * image->SizeY(); ++i) {
            if (i % image->SizeX() == 0) {
                std::cout << '\n';
            }
            std::cout << '(' << static_cast<uint32_t>((image->Data())[i].red) << ' ' <<
                      static_cast<uint32_t>((image->Data())[i].green) << ' ' <<
                      static_cast<uint32_t>((image->Data())[i].blue) << ')';
        }
        std::cout << '\n';
    } else {
        std::cout << "Image too big for show" << '\n';
    }
}

int* CreateDisplsSend(size_t size_x, size_t size_y) {
    int process_count;
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    int* displs = new int[process_count];
    displs[0] = 0;
    int limit_number = process_count;
    if (process_count > size_y - 2) {
        limit_number = static_cast<int>(size_y - 2);
        for (size_t i = 1; i < process_count; ++i) {
            if (i < limit_number) {
                displs[i] = displs[i - 1] + size_x;
            } else {
                displs[i] = 0;
            }
        }
    } else {
        for (size_t i = 1; i < process_count; ++i) {
            displs[i] = static_cast<int>(displs[i - 1] +
                                         CountPixelsSendForProcess(size_x, size_y, i - 1) -
                                         2 * size_x);
        }
    }
    return displs;
}

bool IsDifferentResults(Image* parallel_image, Image* non_parallel_image, size_t size_x) {
    for (uint32_t y = 1; y < parallel_image->SizeY() - 1; ++y) {
        for (uint32_t x = 1; x < parallel_image->SizeX() - 1; ++x) {
            if (parallel_image->Data()[y * size_x + x] != non_parallel_image->Data()[y * size_x + x]) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int process_rank, process_count;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    uint32_t size_x, size_y;
    Image *image = nullptr;
    Image *image_non_parallel = nullptr;
    double start_time;
    if (process_rank == 0) {
        size_x = static_cast<uint32_t>(std::stoull(argv[1]));
        size_y = static_cast<uint32_t>(std::stoull(argv[2]));
        PngProcessor processor;
        image_non_parallel = new Image(processor.Generate(size_x, size_y));
        image = new Image(*image_non_parallel);
        ShowImage(image_non_parallel);
        start_time = MPI_Wtime();
        image_non_parallel->SetData(SobelFiltering(image_non_parallel->Data(), size_x * size_y, size_x));
        std::cout << "Sequential algorithm time : " << MPI_Wtime() - start_time << '\n';
        ShowImage(image_non_parallel);
        std::cout << "*************" << '\n';
        ShowImage(image);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    start_time = MPI_Wtime();
    MPI_Bcast(&size_x, 1, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);
    MPI_Bcast(&size_y, 1, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);
    MPI_Datatype dt_pixel;
    MPI_Type_contiguous(3, MPI_UNSIGNED_CHAR, &dt_pixel);
    MPI_Type_commit(&dt_pixel);
    int *send_counts = nullptr;
    int *displs_send = nullptr;
    int count_recv_pixels = CountPixelsSendForProcess(size_x, size_y, process_rank);
    auto *buf = new Pixel[count_recv_pixels];
    if (process_rank == 0) {
        send_counts = CreateSendCounts(size_x, size_y);
        displs_send = CreateDisplsSend(size_x, size_y);
    }
    Pixel *pixels;
    if (process_rank == 0) {
        pixels = image->Data();
    } else {
        pixels = nullptr;
    }
    //MPI_Barrier(MPI_COMM_WORLD);
    MPI_Scatterv(pixels, send_counts, displs_send, dt_pixel, buf, count_recv_pixels, dt_pixel, 0, MPI_COMM_WORLD);
    if (process_rank == 0) {
        memset(pixels, 0, size_x * size_y * sizeof(Pixel));
    }
    int limit_number;
    if (process_count > size_y - 2) {
        limit_number = static_cast<int>(size_y - 2);
    } else {
        limit_number = process_count;
    }
    if (process_rank < limit_number) {
        buf = SobelFiltering(buf, count_recv_pixels, size_x);
    }
    if (process_rank == 0) {
        for (int rank = 0; rank < process_count; ++rank) {
            if (rank < limit_number) {
                //send_counts[rank] -= size_x;
                send_counts[rank] -= size_x * 2;
                displs_send[rank] += size_x;
            }
        }
    }
    if (process_rank < limit_number) {
        count_recv_pixels -= 2 * size_x;
    }
    MPI_Gatherv(buf + size_x, count_recv_pixels, dt_pixel, pixels, send_counts, displs_send, dt_pixel, 0,
                MPI_COMM_WORLD);
    if (process_rank == 0) {
        image->SetData(pixels);
        std::cout << "Parallel algorithm time : " << MPI_Wtime() - start_time << '\n';
    }
    //MPI_Barrier(MPI_COMM_WORLD);
    if (process_rank == 0) {
        ShowImage(image);
        bool has_error = IsDifferentResults(image, image_non_parallel, size_x);
        if (has_error) {
            std::cout << "Has error" << '\n';
        } else {
            std::cout << "Results equals" << '\n';
        }
        delete image;
        delete image_non_parallel;
        delete[] displs_send;
        delete[] send_counts;
    }
    delete[] buf;
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}