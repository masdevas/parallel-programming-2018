add_executable(Parallel_TBB image.cpp png.cpp main.cpp)
target_link_libraries(Parallel_TBB ${tbb})

#/*size_t begin = range.begin(), end = range.end();
#uint64_t median_red, median_green, median_blue, divider;
#for (size_t index_x = begin; index_x < end; ++index_x) {
#for (size_t index_y = core_radius_; index_y != size_y_ - core_radius_; ++index_y) {
#median_red = 0, median_green = 0, median_blue = 0;
#for (size_t core_index_y = index_y - core_radius_;
#core_index_y <= index_y + core_radius_; ++core_index_y) {
#for (size_t core_index_x = index_x - core_radius_;
#core_index_x <= index_x + core_radius_; ++core_index_x) {
#median_red += pixels_tmp_[core_index_x][core_index_y].red;
#median_green += pixels_tmp_[core_index_x][core_index_y].green;
#median_blue += pixels_tmp_[core_index_x][core_index_y].blue;
#}
#}
#divider = (core_radius_ * 2 + 1) * (core_radius_ * 2 + 1);
#median_red /= divider;
#median_green /= divider;
#median_blue /= divider;
#pixels_[index_x][index_y] = Pixel{static_cast<ColorType>(median_red),
#static_cast<ColorType>(median_green),
#static_cast<ColorType>(median_blue)};
#}
#}*/