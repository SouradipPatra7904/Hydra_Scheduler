Introduction :

★ Hydra_Scheduler :

    Hydra_Scheduler is a modern, GUI-based process scheduler simulator built using Qt6 and C++17. It allows users to experiment with various CPU scheduling algorithms like FCFS, SJF, Round Robin, and more, providing a real-time, interactive Gantt chart view of process execution. The application supports light and dark themes, fully dynamic tables, and customizable process inputs.

★ Tools & Technologies Used :

    1. C++17 – Core language for logic and scheduling algorithms.
    2. Qt6 (Core, Widgets, GUI) – For building the cross-platform graphical interface.
    3. CMake – For project build system and dependency management.
    4. Debian Packaging Tools – To create .deb packages for Ubuntu/Debian-based systems.
    5. Git – Version control.

★ Purpose :

    Hydra_Scheduler is designed for students, educators, and enthusiasts learning CPU scheduling concepts. 
    It provides:
        1. Visual understanding of process scheduling algorithms.
        2. Dynamic table-based input for processes with adjustable arrival and burst times.
        3. Real-time simulation of preemptive and non-preemptive scheduling.
        4. Theme-aware GUI for light and dark preferences.
        5. Fully self-contained deployment for Linux users.
        6. Upto 4 Algorithms, 32 CPU-Cores, Time Quantum 1000 (max) and upto 200 processes supported with unique Arrival & Burst Times and      Priorities.

---------------------------------------------------------------------------------------------------------------------------------------------------
★ Installation :
    A. Using .deb Package (Ubuntu/Debian):
        1. Download the latest hydra-scheduler_1.0.0-1_amd64.deb from the Releases page.
        2. Open a terminal in the download directory.
        3. Install the package:
            $ sudo dpkg -i hydra-scheduler_1.0.0-1_amd64.deb
            $ sudo apt-get install -f   # fix any missing dependencies
    Notes:
        The .deb package is self-contained.
        No additional setup is required beyond installing dependencies (Qt6 libraries are included).

    B. For advanced users, you can also build from source using CMake:

        Prerequisites :
            1. C++17 compiler:
            2. Linux: g++ (build-essential) or clang
            3. Windows: Visual Studio 2022 (with C++ workload)
            4. macOS: Xcode or GCC/Clang via Homebrew
            5. Qt6 (Core, Gui, Widgets modules)
            6. CMake (≥ 3.16)
            7. Git (for cloning repository)

        Linux/macOS (Terminal) :
            $ git clone https://github.com/SouradipPatra7904/Hydra_Scheduler.git
            $ cd Hydra_Scheduler
            $ mkdir build && cd build
            $ cmake .. && make
            $ ./Hydra_Scheduler

        Windows (PowerShell) :
            $ git clone https://github.com/SouradipPatra7904/Hydra_Scheduler.git
            $ cd Hydra_Scheduler
            $ mkdir build && cd build
            $ cmake .. -G "Visual Studio 17 2022" -A x64
            $ cmake --build . --config Release
            $   # Then Run Hydra_Scheduler.exe from the Release folder.
    Notes :
        Ensure Qt6 is properly installed and accessible by CMake :
            For Linux/macOS, install dev packages if needed:
                $ sudo apt install build-essential qt6-base-dev qt6-tools-dev qt6-tools-dev-tools cmake git

            On Windows, set CMAKE_PREFIX_PATH to the Qt installation path if CMake cannot find it:
                cmake .. -DCMAKE_PREFIX_PATH="C:/Qt/6.6.0/msvc2019_64/lib/cmake"

---------------------------------------------------------------------------------------------------------------------------------------------------
Hydra_Scheduler provides a clean, interactive experience to experiment with CPU scheduling algorithms, making learning easier and more visual.