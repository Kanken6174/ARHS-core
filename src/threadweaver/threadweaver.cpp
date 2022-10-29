#include "./threadweaver.hpp"

std::vector<std::thread*> Threadweaver::captureThreads;
std::thread* Threadweaver::hardwareWatcherThread;
std::thread* Threadweaver::osUiDrawerThread;
std::thread* Threadweaver::gfxPipelineThread;

void Threadweaver::stick_this_thread_to_core(std::thread* t,int core_id){
    unsigned num_cpus = std::thread::hardware_concurrency();
    if(core_id > num_cpus) return;
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);
    int rc = pthread_setaffinity_np(t->native_handle(),sizeof(cpu_set_t), &cpuset);
    std::cout << "set thread to core " << core_id << " successfully" << std::endl;
}