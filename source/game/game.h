#include <SFML/Graphics.hpp>

namespace ginger {

	class Game
	{
	public:
		/*
		 * �������������� ����, 
		 * ��������� ��, ��� ����������
		 */
		int start();

		/*
		 * ��������� ��, ��������� ����������
		 */
		void stop();

		/*
		 * �������� ����:
		 * ������� �������, ������������ ������, ������ ���������, ��������� ����������, ������
		 */
		void cycle();

	private:
		sf::RenderWindow*	_window = 0;
		wchar_t*			_gameTitle = L"Ginger";
	};

}