#ifndef INPUT_H
# define INPUT_H

# include "display.h"
# include <GLFW/glfw3.h>

namespace lz
{
	class Input
	{
	private:
		double m_x;
		double m_y;
		double m_last_x;
		double m_last_y;
		double m_dx;
		double m_dy;
		bool m_focused;
		GLFWwindow *m_window;

	public:
		Input(GLFWwindow *window);
		~Input();

		void update(Display *display);
		void updateMouseMovement(Display *display);

		bool getKey(int key);
		bool getButton(int button);

		inline double getX() { return (m_x); }
		inline double getY() { return (m_y); }
		inline double getDX() { return (m_dx); }
		inline double getDY() { return (m_dy); }
		inline bool isFocused() { return (m_focused); }
		inline void setFocused(bool focused) { m_focused = focused; }
	};
}

#endif
