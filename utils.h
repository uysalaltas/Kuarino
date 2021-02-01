
#ifndef utils_h
#define utils_h

class utils{
    public:
        utils();
        void init();
        void split_gcode(char command[], char axes_dir[], char axes_speed[], char gcode_array[]);
        void char_array_to_char_array(char out[], char in[], int len_arr);
        void initialize_char_array(int max_len, char char_arr[]);
        int motor_speed(int speed);
        int distance_to_degree(float mm_dist);
};

#endif