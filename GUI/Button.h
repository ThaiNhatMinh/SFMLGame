#pragma once
#include "pch.h"

#include <vector>
#include <string>
#include <memory>
#include <functional>
namespace GUI
{
	class Button : public Component
	{
	public: 
		typedef std::shared_ptr<Button>		Ptr;
		typedef std::function<void()>		Callback;
	public:
		Button(const TextureHandles& textures, const FontHandles& fonts);

		virtual bool IsSelectable()const override;
		virtual void Select() override;
		virtual void DeSelect()override;
		virtual void Active() override;
		virtual void DeActive()override;
		virtual void HandleEvent(const sf::Event& ev)override;

		void SetCallback(Callback callback);
		void SetText(const std::string& text);
		void SetToggle(bool flag);

	private:
		virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs)const override;
	private:
		Callback m_Callback;
		sf::Sprite m_Sprite;
		const sf::Texture& m_SelectTex;
		const sf::Texture& m_NormalTex;
		const sf::Texture& m_PressTex;
		sf::Text m_Text;
		bool m_IsToggle;
	};
}