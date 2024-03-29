#include "PauseControllerInput.h"
#include "PauseState.h"


PauseControllerInput::PauseControllerInput(PauseState* h)
{
	if (m_bJoysticksInitialised)
		active_ = true;

	state_ = h;
}


PauseControllerInput::~PauseControllerInput()
{
}

void PauseControllerInput::handleInput(Entity * o, Uint32 time, const SDL_Event & event)
{

	if (event.type == SDL_JOYDEVICEREMOVED) {
		active_ = false;
		clean();
	}
	else if (event.type == SDL_JOYDEVICEADDED) {
		initialiseJoysticks();
		active_ = true;
	}

	if (m_bJoysticksInitialised && active_) {
		if (event.type == SDL_JOYAXISMOTION) // check the type value
		{
			// left stick move left or right
			if (event.jaxis.axis == 0)
			{
				if (event.jaxis.value > m_joystickDeadZone)		//This value goes from -33000 until 33000
				{
					m_joystickValues[0].first->setX(1);		//joystick izquierdo - derecha
				}
				else if (event.jaxis.value < -m_joystickDeadZone)
				{
					m_joystickValues[0].first->setX(-1);		//joystick izquierdo - izquierda

				}
				else
				{
					m_joystickValues[0].first->setX(0);
				}
			}
			// left stick move up or down
			if (event.jaxis.axis == 1)
			{
				if (event.jaxis.value > m_joystickDeadZone)			//joystick izquierdo - abajo
				{
					m_joystickValues[0].first->setY(1);
				}
				else if (event.jaxis.value < -m_joystickDeadZone)	//joystick izquierdo - arriba
				{
					m_joystickValues[0].first->setY(-1);
				}
				else
				{
					m_joystickValues[0].first->setY(0);
				}
			}
		}

		int a;	//vertical

		a = SDL_JoystickGetAxis(m_joysticks[0], 1);	//EJE VERTICAL

		//izquierdo derecha
		if (a > m_joystickDeadZone && !joystickMoved)
		{
			joystickMoved = true;
			state_->moveButton(0);
		}
		//izquierdo izquierda
		else if (a < -m_joystickDeadZone && !joystickMoved)
		{
			joystickMoved = true;
			state_->moveButton(1);
		}
		else if ((a > -m_joystickDeadZone && a < m_joystickDeadZone) && (a > -m_joystickDeadZone && a < m_joystickDeadZone))
		{
			joystickMoved = false;
		}

		if (event.type == SDL_JOYBUTTONDOWN)
		{
			m_buttonStates[0][event.jbutton.button] = true;
		}

		if (event.type == SDL_JOYBUTTONUP)
		{
			m_buttonStates[0][event.jbutton.button] = false;
		}

		if (((!controllerType && m_buttonStates[0][Cross]) || (controllerType && m_buttonStates[0][A])) && !buttonPressed) {

			state_->pressButton();
			buttonPressed = true;
		}
		else if (((!controllerType && !m_buttonStates[0][Cross]) || (controllerType && !m_buttonStates[0][A])) && buttonPressed) {
			buttonPressed = false;
		}
	}
}