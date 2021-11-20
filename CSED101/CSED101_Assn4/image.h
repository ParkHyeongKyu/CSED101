struct CUBIC
{
	char name[100]; // File name
	float*** data; // Pixel for CUBIC DATA
	int C, H, W; // C: Channel, H: height, W: width
	int is_normalized; // Whether image is normalized or not
};
typedef struct CUBIC CUBIC;

int show_menu();
void show_il(CUBIC **images, int i);
void show_fl(CUBIC **filters, int j);
void image_load(CUBIC **images, int i);
void print(CUBIC **images, CUBIC **filters, int i, int j);
void image_save(CUBIC **images, int i);
void filter_load(CUBIC **filters, int j);
void image_remove(CUBIC **images, int i);
void filter_remove(CUBIC **filters, int j);
void move_image_index(CUBIC **images, int i, int num);
void move_filter_index(CUBIC **filters, int j, int num);
void normalize(CUBIC **images, int i);
void denormalize(CUBIC **images, int j);
void image_convolution(CUBIC **images, CUBIC **filters, int i, int j);
void quit(CUBIC **images, CUBIC **filters, int i, int j);