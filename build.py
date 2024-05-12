
#!/usr/bin/env python3

import subprocess
import os

def get_user_input():
    while True:
        try:
            user_input = int(input("Pick from lesson 1 to 20: "))
            if 1 <= user_input <= 20:
                return user_input
            else:
                print("Please enter an integer between 1 and 20.")
        except ValueError:
            print("Please enter a valid integer.")


def lesson_cases(lesson):
    switch_dict = {
        1: "clang++ image_on_screen.cpp -o lesson_one ",
        2: "clang++ events.cpp -o lesson_two ",
        3: "clang++ events.cpp -o lesson_three ",
        4: "clang++ events.cpp -o lesson_four ",
        5: "clang++ events.cpp -o lesson_five ",
        6: "clang++ events.cpp -o lesson_six ",

    }
    result = switch_dict.get(lesson, "Invalid option")
    return result

def executable_cases(lesson):
    switch_dict = {
        1: "./lesson_one",
        2: "./lesson_two"
    }
    result = switch_dict.get(lesson, "Invalid option")
    return result


if __name__ == "__main__":
    selected_lesson = get_user_input()

    compile_file = lesson_cases(selected_lesson)
    compile_tag = ("-I/opt/homebrew/opt/sdl2/include/SDL2 "
                   "-I/opt/homebrew/opt/sdl2_image/include/SDL2 "
                   "-L/opt/homebrew/opt/sdl2/lib "
                   "-L/opt/homebrew/opt/sdl2_image/lib "
                   "-lSDL2 "
                   "-lSDL2_image")

    compile_command = compile_file + " " + compile_tag

    print(compile_command)
    print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
    print("Compiling project . . . . . .")
    print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
    compile_line = os.system(compile_command)

    # Compile flag
    if compile_line == 0:
        print("~~~~~~~~~~~~~~~~~~~~~")
        print("Compiled successfully")
        print("~~~~~~~~~~~~~~~~~~~~~")

    selected_executable = executable_cases(selected_lesson)
    subprocess.run(selected_executable, shell=True)
