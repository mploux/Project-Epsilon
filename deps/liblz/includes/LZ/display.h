#ifndef DISPLAY_H
# define DISPLAY_H

# include <iostream>
# define GLEW_STATIC
# include <GL/glew.h>
# include <GLFW/glfw3.h>

namespace lz
{
	class Display
	{
	private:
	    GLFWwindow *m_window;

	    std::string m_title;

	    int m_width;
	    int m_height;

	    int m_last_width;
	    int m_last_height;

	    bool m_resized;
	    bool m_closed;

	    void create(const char *title, int width, int height);

	public:
	    Display(const char *title, int width, int height);
	    ~Display();

	    void update();

	    void setTitle(const char* title);
	    const char *getTitle();

	    inline GLFWwindow *getWindow() { return m_window; };

	    inline int getWidth() { return m_width; };
	    inline int getHeight() { return m_height; };

	    inline bool wasResized() { return m_resized; };
	    inline bool isClosed() { return m_closed; };
	};
}
#endif
