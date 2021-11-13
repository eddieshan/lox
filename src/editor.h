#ifndef EDITOR_H
#define EDITOR_H

struct EditorState {
    bool is_started;
};

class Editor {
    private:
        Editor();

        EditorState _state;

    public:
        static Editor& instance();
        void start();

        Editor(Editor const&) = delete;
        void operator =(Editor const&) = delete;
};

#endif