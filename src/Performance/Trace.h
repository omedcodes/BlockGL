#pragma once

#include <utility>

#include "../glBlocks.h"

class Trace {
private:
    static Trace* instancePtr;

    std::ofstream traceFile;
    uint64_t eventCount = 0;

    Trace(const std::string& traceFile);
    ~Trace();

public:
    static void start(const std::string& traceFile);
    static void end();
    void writeEvent(std::string eventName, uint64_t start, uint64_t end);

    class TraceTimer {
        using TimeUnit = std::chrono::microseconds;
        using Clock = std::chrono::high_resolution_clock;

        bool startNewTrace;
        uint64_t startTime;
        const std::string name;

        [[nodiscard]] uint64_t getTimestamp() const;

    public:
        explicit TraceTimer(const std::string& name);
        ~TraceTimer();
    };
};