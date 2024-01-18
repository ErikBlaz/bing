#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <irrklang/irrKlang.h>
#include <dlfcn.h>
#include <filesystem>

void sound(int status) {
    std::string executablePath = std::getenv("_");
    std::filesystem::path executableDir = std::filesystem::path(executablePath).parent_path();
    std::string filename = executableDir.string() + std::string("/../sounds/microwave.mp3");
    irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice(irrklang::ESOD_AUTO_DETECT , irrklang::ESEO_MULTI_THREADED | irrklang::ESEO_LOAD_PLUGINS | irrklang::ESEO_USE_3D_BUFFERS);
    chdir((executableDir.string() + std::string("/../lib/")).c_str());
    engine->loadPlugins("");
    chdir((executableDir.string() + std::string("/../bin/")).c_str());
    irrklang::ISound* src = engine->play2D(filename.c_str(), true, false, true);
    sleep(2);
}

int main(int argc, char** argv) {
    int pid = fork();
    if (pid == 0) {
        execvp(argv[1], &argv[1]);
    } else if (pid == -1) {
        exit(-1);
    }
    int status;
    waitpid(pid, NULL, 0);
    sound(status);
}