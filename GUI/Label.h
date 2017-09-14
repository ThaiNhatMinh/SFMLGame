#pragma once
#include "pch.h"

namespace GUI
{
	class Label :public Component
	{
	public:
		typedef std::shared_ptr<Label> Ptr;
	public:
		Label(const std::string& text, const FontHandles& fonts,int size = 16);
		
		virtual bool IsSelectable()const override;
		virtual void HandleEvent(const sf::Event& ev);
		void SetText(const std::string& text);

	private:
		virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs)const;
	private:
		sf::Text m_Text;
	};
}