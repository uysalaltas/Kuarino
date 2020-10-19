
#ifndef end_stop_h
#define end_stop_h

#define X_MIN_PIN           3
#ifndef X_MAX_PIN
  #define X_MAX_PIN         2
#endif
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19


class end_stop {
  public:
    end_stop();
    void init();
    int stop_x();
    int stop_y();
    int stop_z();
};

#endif
