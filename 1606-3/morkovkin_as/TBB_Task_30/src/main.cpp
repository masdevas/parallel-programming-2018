#include <iostream>
#include <chrono>
#include <omp.h>
#include "png.hpp"
#include "image.hpp"

void ShowImage(Image image) {
	if (image.SizeX() <= 5 && image.SizeY() <= 5) {
		for (size_t y_coord = 0; y_coord < image.SizeY(); ++y_coord) {
			for (size_t x_coord = 0; x_coord < image.SizeX(); ++x_coord) {
				std::cout << '(' << static_cast<uint32_t>((image.Data())[x_coord][y_coord].red) << ' ' <<
					static_cast<uint32_t>((image.Data())[x_coord][y_coord].green) << ' ' <<
					static_cast<uint32_t>((image.Data())[x_coord][y_coord].blue) << ')';
			}
			std::cout << '\n';
		}
	}
	else {
		std::cout << "Image too big for show" << '\n';
	}
}

int main() {
	/*size_t core_radius = std::stoull(argv[1]);
	size_t size_x = static_cast<size_t>(std::stoull(argv[2]));
	size_t size_y = static_cast<size_t>(std::stoull(argv[3]));*/
	size_t core_radius = 4;
	size_t size_x = 1000;
	size_t size_y = 1000;
	if (core_radius > (size_y - 1) / 2) {
		std::cout << "Too large core radius" << '\n';
		return 1;
	}
	PngProcessor processor;
	Image image_for_seq = processor.Generate(size_x, size_y);
	Image image_for_par(image_for_seq);
	ShowImage(image_for_seq);
	auto start_time = std::chrono::high_resolution_clock::now();
	image_for_seq.NonParallelSmoothing(core_radius);
	auto end_time = std::chrono::high_resolution_clock::now();
	std::cout << "Sequential algorithm time : "
		<< std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count()
		<< '\n';
	std::cout << "*************" << '\n';
	ShowImage(image_for_seq);
    start_time = std::chrono::high_resolution_clock::now();
    image_for_par.ParallelSmoothing(core_radius);
    end_time = std::chrono::high_resolution_clock::now();
    std::cout << "Parallel algorithm time : "
              << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count()
              << '\n';
    std::cout << "*************" << '\n';
	ShowImage(image_for_par);
//    auto start_time = std::chrono::high_resolution_clock::now();
//    std::cout << "Start" << '\n';
//    size_t size = 10'000'000;
//    auto arr = new uint64_t[size];
//#pragma omp parallel for
//    for (uint64_t index = 0; index < size; ++index) {
//        arr[index] = 12;
//    }
//    auto end_time = std::chrono::high_resolution_clock::now();
//    std::cout << "Time : "
//		<< std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count()
//		<< '\n';

	return 0;
}
