/*
 * Copyright (c) 2020, Emanuele Torre <torreemanuele6@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <AK/Function.h>
#include <AK/HashMap.h>
#include <AK/Noncopyable.h>
#include <LibJS/Forward.h>

namespace JS {

enum class ConsoleMessageKind {
    Clear,
    Count,
    Debug,
    Error,
    Info,
    Log,
    Trace,
    Warn,
};

struct ConsoleMessage {
    ConsoleMessageKind kind;
    String text;
};

class Console {
    AK_MAKE_NONCOPYABLE(Console);
    AK_MAKE_NONMOVABLE(Console);

public:
    Console(Interpreter&);

    Interpreter& interpreter() { return m_interpreter; }

    HashMap<String, unsigned>& counters() { return m_counters; }

    void debug(String text);
    void error(String text);
    void info(String text);
    void log(String text);
    void warn(String text);

    void clear();

    void trace(String title);

    unsigned count(String label = "default");
    bool count_reset(String label = "default");

    void add_message(ConsoleMessageKind, String text);

    AK::Function<void(ConsoleMessage&)> on_new_message;

private:
    Interpreter& m_interpreter;

    Vector<ConsoleMessage> m_messages;
    HashMap<String, unsigned> m_counters;
};

}
