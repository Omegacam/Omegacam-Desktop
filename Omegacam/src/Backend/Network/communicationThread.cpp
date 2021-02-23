#include "communication.h"

#include "../backendDelegate.h"

#include <thread>
#include <chrono>

void communication::startThread() {
    isRunningThread = true;

    if (!connect("224.0.0.0", 28650)) {
        isRunningThread = false;
        logs::crit("COULD NOT CONNECT WITH SOCKET");
        return;
    }

    auto startT = std::chrono::high_resolution_clock::now();
	long c = 0;

    while (isRunningThread) {
        //logs::stat("running");
        
        if (isSocketConnected) {
            socketbuffer s_buffer;
            while (socket->recv(s_buffer)) {

                backendDelegate::updateDataBuffer(string(s_buffer.buffer, s_buffer.buffer.size()));

                c++;
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startT).count();
                if (duration >= 1000000) { // 1 sec
                    logs::stat(to_string(c) + " packets in 1 second");
                    startT = std::chrono::high_resolution_clock::now();
                    c = 0;
                }


            }
        }



        this_thread::sleep_for(chrono::microseconds(1));
    }
}

void communication::stopThread() {
    isRunningThread = false;
}
