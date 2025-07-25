#ifndef EDITOR_WIN_HPP
#define EDITOR_WIN_HPP

#include "../../status_bar/status_bar.hpp"
#include "../../../common/styles/style.hpp"
#include <string>

typedef enum class EDITOR_MODE
{
    NORMAL,
    INSERT,
    VISUAL,
    COMMAND
} EDITOR_MODE;

typedef enum class EDITOR_FILE_STATUS
{
    NEW_FILE,
    EXISTING_FILE,
} EDITOR_FILE_STATUS;

typedef enum class EDITOR_OPEN_MODE
{
    NEW_FILE,
    OPEN_FILE,
    OPEN_FOLDER
} EDITOR_OPEN_MODE;

class EditorWin : public StatusBar
{
private:
    WINDOW *editor_win; //TODO: Here we need a naming convention for windows objects
    
protected:
    EDITOR_FILE_STATUS file_status;
    EDITOR_MODE mode = EDITOR_MODE::NORMAL;

public:
    EditorWin();
    ~EditorWin();

    std::string current_file_path;

    void open(EDITOR_OPEN_MODE mode, const std::string &path = "");
};

#endif // EDITOR_WIN_HPP
