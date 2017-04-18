#include "input.h"

using namespace lz;

Input::Input(GLFWwindow *window)
{
	m_window = window;
	m_x = 0;
	m_y = 0;
	m_last_x = 0;
	m_last_y = 0;
	m_dx = 0;
	m_dy = 0;
	m_focused = false;
}

Input::~Input()
{
}

void Input::update(Display *display)
{
	(void) display;
}

void Input::updateMouseMovement(Display *display)
{
	if (glfwGetMouseButton(m_window, 0) && !m_focused)
	{
		m_focused = true;
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwGetCursorPos(display->getWindow(), &m_last_x, &m_last_y);
	}
	else if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) && m_focused)
	{
		m_focused = false;
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwSetCursorPos(display->getWindow(), display->getWidth() / 2.0, display->getHeight() / 2.0);
	}
	if (m_focused)
	{
		glfwGetCursorPos(display->getWindow(), &m_x, &m_y);
		m_dx = m_x - m_last_x;
		m_dy = m_y - m_last_y;
		m_last_x = m_x;
		m_last_y = m_y;
	}
	else
		m_dx = m_dy = 0;
}

bool Input::getKey(int key)
{
	return (glfwGetKey(m_window, key));
}

bool Input::getButton(int button)
{
	return (glfwGetMouseButton(m_window, button));
}
