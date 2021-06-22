#include "vectors.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <array>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <thread>

std::ostream& operator<<(std::ostream& o, const std::array<double, 2>& a)
{
    o << "[" << a[0] << "," << a[1] << "]";
    return o;
}

void draw_o(std::shared_ptr<SDL_Renderer> r, int x, int y, std::shared_ptr<SDL_Texture> tex, double w, double h, double a)
{
    SDL_Rect dst_rect = {x, y, (int)w, (int)h};
    SDL_RenderCopyEx(r.get(), tex.get(), NULL, &dst_rect, a, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
}

class physical_c
{
public:
    std::array<double, 2> position;
    std::array<double, 2> velocity;
    std::array<double, 2> acceleration;

    double friction;

    void update(double dt_f, std::function<void(physical_c*, std::array<double, 2>& pos, std::array<double, 2>& vel)> callback_f)
    {
        using namespace tp::operators;
        auto new_acceleration = acceleration - velocity*length(velocity)*friction;
        auto new_velocity = velocity + new_acceleration * dt_f;
        auto new_position = position + new_velocity * dt_f + new_acceleration * dt_f * dt_f * 0.5;
        callback_f(this, new_position, new_velocity);
    }

};


class trap : public physical_c
{
public:
    //void createTrap() {
    //    int trap_l = rand() % 360 + 1;
    //    int trap_r = rand() % 360 + 1;
    //
    //    int trap_t = rand() % 640 + 1;
    //    int trap_b = rand() % 640 + 1;
    //
    //    int trap_number = rand() % 10 + 10;
    //
    //    double angle = atan2(trap_l - 300, 0 - 640) - M_PI;
    //
    //
    //    auto speed = 10;
    //    auto dst_x = speed*cos(angle);
    //    auto dst_y = speed*sin(angle);
    //}

    std::map<std::string, int> intentions;

    trap()
    {
        int trap_loc = rand() % 640 + 1;
        position = {10, 10};
        velocity = {0*50, 0};
        friction = 0;
        acceleration = {0,0};
    }

    void apply_intent()
    {
        int intent_rand = rand() % 4 +1;

        acceleration = {0, 0};
        if(intent_rand == 1) acceleration[0] += 200;
        if(intent_rand == 2) acceleration[0] += -200;
        if(intent_rand == 3) acceleration[1] += -200;
        if(intent_rand == 4) acceleration[1] += 200;

        intentions.clear();
    }
};

class buff
{

public:
    void createBuff() {

        int buff_x = rand() % 640 + 1;
        int buff_y = rand() % 360 + 1;

        int buff_type = rand() % 10 + 10;

        SDL_Rect buff_react = { buff_x, buff_y, 10, 10 };


    }
};

class player : public physical_c
{
public:
    std::map<std::string, int> intentions;

    player()
    {
        position = {10, 10};
        velocity = {0, 0};
        friction = 0.03;
        acceleration = {0,0};
    }

    void apply_intent()
    {
        acceleration = {0, 0};
        if (intentions.count("right")) acceleration[0] += 100;
        if (intentions.count("left")) acceleration[0] += -100;
        if (intentions.count("up")) acceleration[1] += -100;
        if (intentions.count("down")) acceleration[1] += +100;

        intentions.clear();
    }
};



int main(int, char**)
{
    using namespace std;
    using namespace std::chrono;
    using namespace tp::operators;

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    SDL_Rect rect1 = { 0, 0, 10, 360 };
    SDL_Rect rect2 = { 0, 0, 640, 10 };
    SDL_Rect rect3 = { 630, 0, 10, 360 };
    SDL_Rect rect4 = { 0, 350, 640, 10 };

    SDL_Rect log1 = {200, 70, 200, 20};

    SDL_Rect log2 = {500, 300, 200, 20};

    SDL_Rect log3 = {50, 250, 200, 20};

    SDL_Rect log4 = {300, 150, 200, 20};




    shared_ptr<SDL_Window> window_p(
            SDL_CreateWindow("IceTowerForTwo", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, 640, 360, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE),
            [](auto* window) { SDL_DestroyWindow(window); });

    shared_ptr<SDL_Renderer> renderer_p(
            SDL_CreateRenderer(window_p.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
            [](auto* renderer) { SDL_DestroyRenderer(renderer); });




    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    SDL_RenderSetLogicalSize(renderer_p.get(), 640, 360);

    shared_ptr<SDL_Texture> tex_p1(IMG_LoadTexture(renderer_p.get(), "data/ship1.png"),
                                  [](auto* tex) { SDL_DestroyTexture(tex); });

    shared_ptr<SDL_Texture> tex_p2(IMG_LoadTexture(renderer_p.get(), "data/ship2.png"),
                                  [](auto* tex) { SDL_DestroyTexture(tex); });

    shared_ptr<SDL_Texture> tex_t(IMG_LoadTexture(renderer_p.get(), "data/background.png"),
                                  [](auto* tex) { SDL_DestroyTexture(tex); });

    shared_ptr<SDL_Texture> tex_bomb(IMG_LoadTexture(renderer_p.get(), "data/trap.jpeg"),
                                  [](auto* tex) { SDL_DestroyTexture(tex); });



    player player1;

    player player2;

    trap trap;

    buff new_buff;

    //SDL_Rect buff_react;

    milliseconds dt(15);
    steady_clock::time_point current_time = steady_clock::now(); // remember current time
    for (bool game_active = true; game_active;) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) { // check if there are some events
            if (event.type == SDL_QUIT)
                game_active = false;
        }
        auto kbdstate = SDL_GetKeyboardState(NULL);
        if (kbdstate[SDL_SCANCODE_RIGHT]) player1.intentions["right"] = 1;
        if (kbdstate[SDL_SCANCODE_LEFT]) player1.intentions["left"] = 1;
        if (kbdstate[SDL_SCANCODE_UP]) player1.intentions["up"] = 1;
        if (kbdstate[SDL_SCANCODE_DOWN]) player1.intentions["down"] = 1;

        if (kbdstate[SDL_SCANCODE_D]) player2.intentions["right"] = 1;
        if (kbdstate[SDL_SCANCODE_A]) player2.intentions["left"] = 1;
        if (kbdstate[SDL_SCANCODE_S]) player2.intentions["down"] = 1;
        if (kbdstate[SDL_SCANCODE_W]) player2.intentions["up"] = 1;

        if (kbdstate[SDL_SCANCODE_B]) new_buff.createBuff();


        //new_trap.update(speed, angle)
        //{
        //    p->speed = {((vel[0] * vel[0] > 2.2) ? vel[0] : 0.0) * (-2), 0};
        //    p->position[0] = pos[0];
        //    p->friction = 0.3;
        //}



        /// fizyka
        double dt_f = dt.count() / 1000.0;
        player1.apply_intent();
        player1.update(dt_f, [&](auto p, auto pos, auto vel) {
            if(pos[0] < 2){
                std::cout << "Left" << endl;
                p->velocity = {((vel[0]*vel[0]>2.2)?vel[0]:0.0) * (-2), 0};
                p->position[0] = pos[0];
                p->friction = 0.3;

            }else if(pos[0] > 62){
                std::cout << "right" << endl;
                p->velocity = {((vel[0]*vel[0]>2.2)?vel[0]:0.0) * (-2), 0};
                p->position[0] = pos[0];
                p->friction = 0.3;

            }else if( pos[1] < 2){
                std::cout << "top" << endl;
                p->velocity = {((vel[0]*vel[0]>2.2)?vel[0]:0.0) * (-2), 0};
                p->position[0] = pos[0];
                p->friction = 0.3;

            }else if(pos[1] > 35){
                std::cout << "bottom" << endl;
                p->velocity = {((vel[0]*vel[0]>2.2)?vel[0]:0.0) * (-2), 0};
                p->position[0] = pos[0];
                p->friction = 0.3;

            }else if (pos[1] < 40) {
                p->position = pos;
                p->velocity = vel;
                p->friction = 0.2;
            } else {
                p->velocity = {(vel[0]*vel[0]>2.2)?vel[0]:0.0, 0};
                p->position[0] = pos[0];
                p->friction = 0.3;
            }

        }
        );
        player2.apply_intent();
        player2.update(dt_f, [&](auto p, auto pos, auto vel) {
            if(pos[0] < 2){
                std::cout << "Left" << endl;
                p->velocity = {((vel[0]*vel[0]>2.2)?vel[0]:0.0) * (-2), 0};
                p->position[0] = pos[0];
                p->friction = 0.3;

            }else if(pos[0] > 62){
                std::cout << "right" << endl;
                p->velocity = {((vel[0]*vel[0]>2.2)?vel[0]:0.0) * (-2), 0};
                p->position[0] = pos[0];
                p->friction = 0.3;

            }else if( pos[1] < 2){
                std::cout << "top" << endl;
                p->velocity = {((vel[0]*vel[0]>2.2)?vel[0]:0.0) * (-2), 1};
                p->position[0] = pos[0];
                p->friction = 0.3;

            }else if(pos[1] > 35){
                std::cout << "bottom" << endl;
                p->velocity = {((vel[0]*vel[0]>2.2)?vel[0]:0.0) * (-2), 1};
                p->position[0] = pos[0];
                p->friction = 0.3;

            }else if (pos[1] < 40) {
                p->position = pos;
                p->velocity = vel;
                p->friction = 0.2;
            } else {
                p->velocity = {(vel[0]*vel[0]>2.2)?vel[0]:0.0, 0};
                p->position[0] = pos[0];
                p->friction = 0.3;
            }
        });

        trap.apply_intent();
        trap.update(dt_f, [&](auto p, auto pos, auto vel) {
            if(pos[0] < 2){
                std::cout << "Left" << endl;
                p->velocity = {((vel[0]*vel[0]>2.2)?vel[0]:0.0) * (-2), 0};
                p->position[0] = pos[0];
                p->friction = 0.3;

            }else if(pos[0] > 62){
                std::cout << "right" << endl;
                p->velocity = {((vel[0]*vel[0]>2.2)?vel[0]:0.0) * (-2), 0};
                p->position[0] = pos[0];
                p->friction = 0.3;

            }else if( pos[1] < 2){
                std::cout << "top" << endl;
                p->velocity = {((vel[0]*vel[0]>2.2)?vel[0]:0.0) * (-2), 1};
                p->position[0] = pos[0];
                p->friction = 0.3;

            }else if(pos[1] > 35){
                std::cout << "bottom" << endl;
                p->velocity = {((vel[0]*vel[0]>2.2)?vel[0]:0.0) * (-2), 1};
                p->position[0] = pos[0];
                p->friction = 0.3;

            }else if (pos[1] < 40) {
                p->position = pos;
                p->velocity = vel;
                p->friction = 0.2;
            } else {
                p->velocity = {(vel[0]*vel[0]>2.2)?vel[0]:0.0, 0};
                p->position[0] = pos[0];
                p->friction = 0.3;
            }
        });

        //SDL_Rect log1 = {200, 70, 200, 20};
        //
        //SDL_Rect log2 = {500, 300, 200, 20};
        //
        //SDL_Rect log3 = {50, 250, 200, 20};
        //
        //SDL_Rect log4 = {300, 150, 200, 20};



        int p1x = ((int)(player1.position[0]*10 - 12 / 2));
        int p2x = ((int)(player2.position[0]*10 - 16 / 2));
        int p1y = ((int)(player1.position[1]*10 - 12 / 2));
        int p2y = ((int)(player2.position[1]*10 - 16 / 2));

        //if( (((p1x - p2x) < 10) && ((p1x - p2x) > -10)) && (((p1y - p2y) < 10) && ((p1y - p2y) > -10)) ){
        //    std::cout << "end" << endl;
        //}

        //if( (((p1x - p2x) < 10) && ((p1x - p2x) > -10)) && (((p1y - p2y) < 10) && ((p1y - p2y) > -10)) ){
        //    std::cout << "end" << endl;
        //}

        SDL_Rect frame_p1 = {p1x, p1y, 20, 20};

        SDL_Rect frame_p2 = {p2x, p2y, 20, 20};

        if(SDL_HasIntersection(&frame_p1, &frame_p2) ){
            std::cout << "crash" << endl;
        }

        if(SDL_HasIntersection(&frame_p1, &log1) || SDL_HasIntersection(&frame_p1, &log2) || SDL_HasIntersection(&frame_p1, &log3) || SDL_HasIntersection(&frame_p1, &log4)){
            std::cout << "player1 - lose" << endl;
        }

        if(SDL_HasIntersection(&frame_p2, &log1) || SDL_HasIntersection(&frame_p2, &log2) || SDL_HasIntersection(&frame_p2, &log3) || SDL_HasIntersection(&frame_p2, &log4)){
            std::cout << "player2 - lose" << endl;
        }


        /// grafika
        SDL_RenderFillRect(renderer_p.get(), &frame_p1);

        SDL_RenderFillRect(renderer_p.get(), &frame_p2);

        SDL_RenderCopy(renderer_p.get(), tex_t.get(), NULL, NULL);

        SDL_SetRenderDrawColor(renderer_p.get(), 255, 0, 0, 255);
        SDL_RenderFillRect(renderer_p.get(), &rect1);

        SDL_SetRenderDrawColor(renderer_p.get(), 255, 0, 0, 255);
        SDL_RenderFillRect(renderer_p.get(), &rect2);

        SDL_SetRenderDrawColor(renderer_p.get(), 255, 0, 0, 255);
        SDL_RenderFillRect(renderer_p.get(), &rect3);

        SDL_SetRenderDrawColor(renderer_p.get(), 255, 0, 0, 255);
        SDL_RenderFillRect(renderer_p.get(), &rect4);

        SDL_SetRenderDrawColor(renderer_p.get(), 0, 255, 0, 255);
        //SDL_RenderFillRect(renderer_p.get(), &buff_react);

        SDL_SetRenderDrawColor(renderer_p.get(), 255, 0, 0, 255);
        SDL_RenderFillRect(renderer_p.get(), &log1);

        SDL_SetRenderDrawColor(renderer_p.get(), 255, 0, 0, 255);
        SDL_RenderFillRect(renderer_p.get(), &log2);

        SDL_SetRenderDrawColor(renderer_p.get(), 255, 0, 0, 255);
        SDL_RenderFillRect(renderer_p.get(), &log3);

        SDL_SetRenderDrawColor(renderer_p.get(), 255, 0, 0, 255);
        SDL_RenderFillRect(renderer_p.get(), &log4);

        //if(player1.intentions["top"] == 1){
        //    angle = 0;
        //}else if (player1.intentions["bottom"] == 1){
        //    angle = 180;
        //}else if (player1.intentions["right"] == 1){
        //    angle = 90;
        //}else if (player1.intentions["left"] == 1){
        //    angle = 270;
        //}


        draw_o(renderer_p, (int)(player1.position[0]*10 - 12 / 2), (int)(player1.position[1] * 10 - 20 / 2), tex_p1, 12, 20, player1.position[0]*36+player1.position[1]*5);
        draw_o(renderer_p, (int)(player2.position[0]*10 - 16 / 2), (int)(player2.position[1] * 10 - 20 / 2), tex_p2, 16, 20, player2.position[0]*36+player2.position[1]*5);
        /// a = double * 36 + [1 or 0] * 5

        draw_o(renderer_p, (int)(trap.position[0]), (int)(trap.position[1]), tex_bomb, 10, 10, trap.position[0]*36+trap.position[1]*5);



        SDL_RenderPresent(renderer_p.get());

        this_thread::sleep_until(current_time = current_time + dt);

    }
    SDL_Quit();
    return 0;
}