#include <vector>
#include <mutex>

/// @brief this class manages the UI(s) [windows] used by the application, right now only one should ever be used, especially in opengl mode
class UiManager
{
public:
    static std::vector<std::mutex*> accessLocks;
    static std::vector<Ui *> managedUIs;
    static bool uiShouldRun;
    static void init();
    static void cleanup();
    static void beginDrawRoutineForUi(Ui *u);
};