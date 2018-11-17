#include <iostream>
#include <mpi.h>
#include <cstring>
#include "png.hpp"

void Smooth(Pixel* buf, int count_recv_pixels, size_t size_x, size_t core_radius) {
    auto* pixels_tmp = new Pixel[count_recv_pixels];
    memcpy(pixels_tmp, buf, count_recv_pixels * sizeof(Pixel));
    size_t size_y_for_proc = count_recv_pixels / size_x;
    for (size_t index_y = core_radius; index_y + core_radius < size_y_for_proc; ++index_y) {
        for (size_t index_x = core_radius; index_x + core_radius < size_x; ++index_x) {
            uint64_t median_red = 0, median_green = 0, median_blue = 0;
            int counter = 0;
            for (size_t core_index_y = index_y - core_radius; core_index_y <= index_y + core_radius; ++core_index_y) {
                for (size_t core_index_x = index_x - core_radius; core_index_x <= index_x + core_radius; ++core_index_x) {
                    median_red += pixels_tmp[core_index_x + core_index_y * size_x].red;
                    median_green += pixels_tmp[core_index_x + core_index_y * size_x].green;
                    median_blue += pixels_tmp[core_index_x + core_index_y * size_x].blue;
                    counter++;
                }
            }
            size_t divider = (core_radius * 2 + 1) * (core_radius * 2 + 1);
            median_red /= divider;
            median_green /= divider;
            median_blue /= divider;
            buf[index_x + index_y * size_x] = Pixel{static_cast<ColorType>(median_red),
                                                    static_cast<ColorType>(median_green),
                                                    static_cast<ColorType>(median_blue)};
        }
    }
    delete[] pixels_tmp;
}

int CountPixelsSendForProcess(size_t size_x, size_t size_y, int number_process, size_t core_radius) {
    int process_count;
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    int for_each_y_centres = static_cast<int>((size_y - 2 * core_radius) / process_count);
    int limit_number = process_count;
    if (process_count > size_y - 2 * core_radius) {
        limit_number = static_cast<int>(size_y - 2 * core_radius);
        if (number_process >= limit_number) {
            return 0;
        } else {
            return size_x * (2 * core_radius + 1);
        };
    } else {
        if ((number_process == process_count - 1) && ((size_y - 2 * core_radius) % process_count != 0)) {
            return static_cast<int>(for_each_y_centres * size_x + 2 * core_radius * size_x +
                                    ((size_y - 2 * core_radius) % process_count) * size_x);
        } else {
            return static_cast<int>(for_each_y_centres * size_x + 2 * core_radius * size_x);
        }
    }
}

int* CreateSendCounts(size_t size_x, size_t size_y, size_t core_radius) {
    int process_count;
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    int* send_counts = new int[process_count];
    for (size_t i = 0; i < process_count; ++i) {
        send_counts[i] = CountPixelsSendForProcess(size_x, size_y, i, core_radius);
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

int* CreateDisplsSend(size_t size_x, size_t size_y, size_t core_radius) {
    int process_count;
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    int* displs = new int[process_count];
    displs[0] = 0;
    int limit_number = process_count;
    if (process_count > size_y - 2 * core_radius) {
        limit_number = static_cast<int>(size_y - 2 * core_radius);
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
                                         CountPixelsSendForProcess(size_x, size_y, i - 1, core_radius) -
                                         2 * core_radius * size_x);

        }
    }
    return displs;
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int process_rank, process_count;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    size_t core_radius;
    uint32_t size_x, size_y;
    Image *image = nullptr;
    double start_time;
    if (process_rank == 0) {
        core_radius = std::stoull(argv[1]);
        size_x = static_cast<uint32_t>(std::stoull(argv[2]));
        size_y = static_cast<uint32_t>(std::stoull(argv[3]));
        if (core_radius > (size_y - 1) / 2) {
            std::cout << "Too large core radius" << '\n';
            return 1;
        }
        PngProcessor processor;
        Image* image2 = new Image(processor.Generate(size_x, size_y));
        image = new Image(*image2);
        ShowImage(image2);
        start_time = MPI_Wtime();
        image2->NonParallelSmoothing(core_radius);
        std::cout << "Sequential algorithm time : " << MPI_Wtime() - start_time << '\n';

        ShowImage(image2);
        delete image2;
        std::cout << "*************" << '\n';
        ShowImage(image);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    start_time = MPI_Wtime();
    MPI_Bcast(&core_radius, 1, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);
    if (process_rank == 0) {
        size_x = image->SizeX();
        size_y = image->SizeY();
    }
    MPI_Bcast(&size_x, 1, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);
    MPI_Bcast(&size_y, 1, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);
    MPI_Datatype dt_pixel;
    MPI_Type_contiguous(3, MPI_UNSIGNED_CHAR, &dt_pixel);
    MPI_Type_commit(&dt_pixel);
    int *send_counts = nullptr;
    int *displs_send = nullptr;
    int count_recv_pixels = CountPixelsSendForProcess(size_x, size_y, process_rank, core_radius);
    auto *buf = new Pixel[count_recv_pixels];
    if (process_rank == 0) {
        send_counts = CreateSendCounts(size_x, size_y, core_radius);
        displs_send = CreateDisplsSend(size_x, size_y, core_radius);
    }
    Pixel *pixels;
    if (process_rank == 0) {
        pixels = image->Data();
    } else {
        pixels = nullptr;
    }
    MPI_Scatterv(pixels, send_counts, displs_send, dt_pixel, buf, count_recv_pixels, dt_pixel, 0, MPI_COMM_WORLD);
    if (process_rank == 0) {
        memset(pixels, 0, size_x * size_y * sizeof(Pixel));
    }
    Smooth(buf, count_recv_pixels, size_x, core_radius);
    int limit_number = process_count;
    if (process_count > size_y - 2 * core_radius) {
        limit_number = static_cast<int>(size_y - 2 * core_radius);
    }
    if (process_rank == 0) {
        for (int rank = 0; rank < process_count; ++rank) {
            if (rank < limit_number) {
                send_counts[rank] -= core_radius * size_x;
                displs_send[rank] += core_radius * size_x;
            }
        }
    }
    if (process_rank < limit_number) {
        count_recv_pixels -= 2 * core_radius * size_x;
    }
    MPI_Gatherv(buf + core_radius * size_x, count_recv_pixels, dt_pixel, pixels, send_counts, displs_send, dt_pixel, 0,
                MPI_COMM_WORLD);
    if (process_rank == 0) {
        image->SetData(pixels);
        std::cout << "Parallel algorithm time : " << MPI_Wtime() - start_time << '\n';
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if (process_rank == 0) {
        ShowImage(image);
        delete image;
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}