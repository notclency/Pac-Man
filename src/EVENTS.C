#include "EVENTS.H"

void on_pacman_move(Model *model, UINT32 key, int player)
{
    switch (key)
    {
    case UP_KEY:
        move_pacman(model->pacman, UP, player);
        break;
    case DOWN_KEY:
        move_pacman(model->pacman, DOWN, player);
        break;
    case LEFT_KEY:
        move_pacman(model->pacman, LEFT, player);
        break;
    case RIGHT_KEY:
        move_pacman(model->pacman, RIGHT, player);
        break;
    }
}

void on_ghost_move(Model *model, int player)
{
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        move_ghost(&model->ghosts[i], model->pacman, player);
    }
}

void on_snack_eat(Model *model, int player)
{
    model->pacman[player].score += 50;
    update_scorebox(model, player);
}

void on_cherry_eat(Model *model, int player)
{
    model->pacman[player].score += 100;
    update_scorebox(model, player);
}

void on_glow_ball_eat(Model *model, int player)
{
    int j = 0;

    model->pacman[player].score += 200;
    model->pacman[player].mode = SUPER;
    update_scorebox(model, player);
    for (j = 0; j < 3; j++)
    {
        model->ghosts[j].mode = SCATTER;
    }
}

void on_ghost_eat(Model *model, int player)
{
    int pacman_x = model->pacman[player].x;
    int pacman_y = model->pacman[player].y;
    int i = 0;

    for (i = 0; i < 3; i++)
    {
        if (model->ghosts[i].x == pacman_x && model->ghosts[i].y == pacman_y)
        {
            if (model->pacman[player].mode == SUPER)
            {
                model->pacman[player].score += 200;
                model->ghosts[i].is_dead = TRUE;
                update_scorebox(model, player);

                model->ghosts[i].x = 19;
                model->ghosts[i].y = 6;
            }
            else
            {
                model->pacman[player].lives--;
                model->pacman[player].x = 15;
                model->pacman[player].y = 13;
                model->pacman[player].mode = NORMAL;
                update_livebox(model, player);
            }
        }
    }
}

void on_game_start(Model *model, int player_count, int player)
{
    ini_game_session(model, player_count, player);
}

void on_game_over(Model *model)
{
    close_game_session(model);
}

void on_game_win(Model *model, int player_count)
{
    won_game_session(model);
}
