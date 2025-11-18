Functions
void fr(int ***image, int N, int M)
Frees the memory allocated for the image.

int ***aloc(int N, int M)
Allocates memory for a new image with dimensions N x M.

int ***flip_horizontal(int ***image, int N, int M)
Flips the image horizontally.

int ***rotate_left(int ***image, int N, int M)
Rotates the image 90 degrees to the left.

int ***crop(int ***image, int N, int M, int x, int y, int h, int w)
Crops the image to a specified region defined by the top-left corner (x, y) and dimensions (h, w).

int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B)
Extends the image by adding borders of specified color (new_R, new_G, new_B) and dimensions (rows, cols).

int ***paste(int ***image_dst, int N_dst, int M_dst, int ***image_src, int N_src, int M_src, int x, int y)
Pastes the source image onto the destination image at the specified position (x, y).

int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size)
Applies a convolution filter to the image for basic image filtering operations.