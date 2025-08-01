#ifndef COMMON_DESIGN_HPP
#define COMMON_DESIGN_HPP

#include <mutex>
#include <string>
#include <vector>

class Style
{
public:
  static Style &instance()
  {
    static Style instance;
    return instance;
  }

  // constants getters
  int status_bar_height() const { return m_status_bar_height; }
  int editor_buffer_vertical_padding() const { return m_editor_buffer_vertical_padding; }
  int padding_l_r() const { return m_padding_l_r; }
  int padding_t_b() const { return m_padding_t_b; }
  int required_term_rows() const { return m_required_term_rows; }
  int required_term_cols() const { return m_required_term_cols; }
  int logo_width() const { return te_cpp_logo_width; }
  int logo_height() const { return te_cpp_logo_height; }
  const std::vector<std::string> logo() const { return te_cpp_logo; }

  // Dynamic getters
  int term_rows() const { return M_TERM_ROWS; }
  int term_cols() const { return M_TERM_COLS; }

  // First is x (COLS), second is y (ROWS)
  void updateFromWindowSize(int COLS, int ROWS)
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    // TODO
    M_TERM_COLS = COLS;
    M_TERM_ROWS = ROWS - m_status_bar_height;
  }

private:
  Style() = default;
  Style(const Style &) = delete;
  Style &operator=(const Style &) = delete;

  // Constants
  const int m_padding_l_r = 2;
  const int m_padding_t_b = 1;
  const int m_required_term_rows = 30;
  const int m_required_term_cols = 80;
  const int m_editor_buffer_vertical_padding = 3;
  const int m_status_bar_height = 1;
  // Editor ekraninda metin ekranin soldan ve sagdan 4. indexinden
  // basliyor

  // App logo and dimensions
  const int te_cpp_logo_width = 50;
  const int te_cpp_logo_height = 6;
  std::vector<std::string> te_cpp_logo = {
      "████████╗███████╗         ██████╗██████╗ ██████╗ ",
      "╚══██╔══╝██╔════╝        ██╔════╝██╔══██╗██╔══██╗",
      "   ██║   █████╗          ██║     ██████╔╝██████╔╝",
      "   ██║   ██╔══╝          ██║     ██╔═══╝ ██╔═══╝ ",
      "   ██║   ███████╗███████╗╚██████╗██║     ██║     ",
      "   ╚═╝   ╚══════╝╚══════╝ ╚═════╝╚═╝     ╚═╝     "};

  // Dynamic values
  int M_TERM_ROWS = 0;
  int M_TERM_COLS = 0;

  std::mutex m_mutex;
};

#endif // COMMON_DESIGN_HPP
