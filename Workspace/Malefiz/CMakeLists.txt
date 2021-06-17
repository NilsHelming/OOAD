cmake_minimum_required(VERSION 3.17)
project(Malefiz)

set(CMAKE_CXX_STANDARD 14)

add_executable(Malefiz main.cpp MfController.cpp Würfel.h WürfelView.h Spieler.h Spielfeld.h SpielfeldView.h)