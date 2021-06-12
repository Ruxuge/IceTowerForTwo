#include "vectors.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <array>
#include <chrono>
#include <cstdint>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <thread>
#include <tuple>
#include <vector>


std::ostream& operator<<(std::ostream& o, const std::array<double, 2>& a)
{
    o << "[" << a[0] << "," << a[1] << "]";
    return o;
}

void draw_o(std::shared_ptr<SDL_Renderer> r, std::array<double, 2> p, std::shared_ptr<SDL_Texture> tex, double w, double h, double a)
{
    SDL_Rect dst_rect = {(int)(p[0] - w / 2), (int)(p[1] - h / 2), (int)w, (int)h};
    SDL_RenderCopyEx(r.get(), tex.get(), NULL, &dst_rect, a, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
}

class physical_c
{
public:
    std::array<double, 2> position;
    std::array<double, 2> velocity;
    std::array<double, 2> acceleration;
    double friction;
    double gravity;

    void update(double dt_f, std::function<void(physical_c*, std::array<double, 2>& pos, std::array<double, 2>& vel)> callback_f)
    {
        using namespace tp::operators;
        // apply friction:
        auto new_acceleration = acceleration - velocity*length(velocity)*friction;
        auto new_velocity = velocity + new_acceleration * dt_f;
        auto new_position = position + new_velocity * dt_f + new_acceleration * dt_f * dt_f * 0.5;
        callback_f(this, new_position, new_velocity);
    }



    void jump(){
        float myGravity = 0.2f;
        float maxFallSpeed = -5.0f;
        float myJumpForce = 5.0f;
        float curJumpForce = 0.0f;
        float deltaTime;
        float jump_p;

        curJumpForce = myJumpForce;


        jump_p += curJumpForce * deltaTime;

        if(curJumpForce > maxFallSpeed){
                    myJumpForce -= myGravity * deltaTime;
        }else{
                curJumpForce = maxFallSpeed;
        }

        //callback_f(this, new_position, new_velocity);
    }

};

class player : public physical_c
{
public:
    std::map<std::string, int> intentions;

    player()
    {
        position = {10, 10};
        velocity = {0*0.5, 0};
        friction = 0.03;
        acceleration = {0,0};

        //int px = 1;
       // int py = 1;
        //int p2x = 1;
        //int p2y = 1;

        //SDL_Rect p1 = { px, py, 10, 10 };
        //SDL_Rect p2 = { px, py, 10, 10 };

    }



    /**
 * applies and clears intentions
 * */
    void apply_intent()
    {
        acceleration = {0, 30};
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


    //SDL_Rect p2 = { p2x, p2y, 1, 1 };

    shared_ptr<SDL_Window> window_p(
            SDL_CreateWindow("IceTowerForTwo", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, 640, 360, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE),
            [](auto* window) { SDL_DestroyWindow(window); });

    shared_ptr<SDL_Renderer> renderer_p(
            SDL_CreateRenderer(window_p.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
            [](auto* renderer) {
                SDL_DestroyRenderer(renderer);
            });




    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    SDL_RenderSetLogicalSize(renderer_p.get(), 640, 360);

    shared_ptr<SDL_Texture> tex_p1(IMG_LoadTexture(renderer_p.get(), "data/ship1.png"),
                                  [](auto* tex) { SDL_DestroyTexture(tex); });

    shared_ptr<SDL_Texture> tex_p2(IMG_LoadTexture(renderer_p.get(), "data/ship2.png"),
                                  [](auto* tex) { SDL_DestroyTexture(tex); });

    shared_ptr<SDL_Texture> tex_t(IMG_LoadTexture(renderer_p.get(), "data/tlo.png"),
                                  [](auto* tex) { SDL_DestroyTexture(tex); });



    player player1;

    player player2;


    milliseconds dt(15);
    steady_clock::time_point current_time = steady_clock::now(); // remember current time



    for (bool game_active = true; game_active;) {

        //SDL_bool collision_l = SDL_HasIntersection(, &rect1);

        //if (collision_l) {
            //std::cout << "Left" << endl;

        //}

       // SDL_bool collision_t = SDL_HasIntersection(, &rect3);

        //if (collision_t) {
      //      std::cout << "Top" << endl;

        //}


        //steady_clock::time_point frame_start = steady_clock::now();
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


        /// fizyka
        double dt_f = dt.count() / 1000.0;
        player1.apply_intent();
        player1.update(dt_f, [&](auto p, auto pos, auto vel) {
            if (pos[1] < 40) {
                p->position = pos;
                p->velocity = vel;
                p->friction = 0.2;
            } else {
                p->velocity = {(vel[0] * vel[0] > 2.2) ? vel[0] : 0.0, 0};
                p->position[0] = pos[0];
                p->friction = 0.3;

            }
        });
        player2.apply_intent();
        player2.update(dt_f, [&](auto p, auto pos, auto vel) {
            if(pos[0] < 2){
                std::cout << "Left" << endl;
            }else if(pos[0] > 62){
                std::cout << "right" << endl;
            }else if( pos[1] < 2){
                std::cout << "top" << endl;
            }else if(pos[1] > 35){
                std::cout << "bottom" << endl;
            }
            if (pos[1] < 40) {
                p->position = pos;
                p->velocity = vel;
                p->friction = 0.2;
            } else {
                p->velocity = {(vel[0]*vel[0]>2.2)?vel[0]:0.0, 0};
                p->position[0] = pos[0];
                p->friction = 0.3;
            }

        });






        /// grafika
        //SDL_SetRenderDrawColor(renderer_p.get(), 0, 10, 200, 255);
        //SDL_RenderClear(renderer_p.get());

        //SDL_SetRenderDrawColor(renderer_p.get(), 0, 0, 0, 0);
        //SDL_RenderFillRect(renderer_p.get(), &p1);

        //SDL_SetRenderDrawColor(renderer_p.get(), 0, 0, 0, 0);
        //SDL_RenderFillRect(renderer_p.get(), &p2);

        SDL_RenderCopy(renderer_p.get(), tex_t.get(), NULL, NULL);

        SDL_SetRenderDrawColor(renderer_p.get(), 255, 0, 0, 255);
        SDL_RenderFillRect(renderer_p.get(), &rect1);

        SDL_SetRenderDrawColor(renderer_p.get(), 255, 0, 0, 255);
        SDL_RenderFillRect(renderer_p.get(), &rect2);

        SDL_SetRenderDrawColor(renderer_p.get(), 255, 0, 0, 255);
        SDL_RenderFillRect(renderer_p.get(), &rect3);

        SDL_SetRenderDrawColor(renderer_p.get(), 255, 0, 0, 255);
        SDL_RenderFillRect(renderer_p.get(), &rect4);

        draw_o(renderer_p, player1.position*10, tex_p1, 12, 20, player1.position[0]*36+player1.position[1]*5);
        draw_o(renderer_p, player2.position*10, tex_p2, 16, 20, player2.position[0]*36+player2.position[1]*5);


        SDL_RenderPresent(renderer_p.get());

        this_thread::sleep_until(current_time = current_time + dt);


    }
    SDL_Quit();
    return 0;
}