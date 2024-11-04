
typedef struct {
    uint64_t last_point_time;
    uint8_t score;
} GAME_DATA;

GAME_DATA get_game_data();
void score_counter();