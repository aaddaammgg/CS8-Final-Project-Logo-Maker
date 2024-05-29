//
// Created by Adam G.
//

#ifndef CS008_SFML_TYPING_TEXTINPUT_H
#define CS008_SFML_TYPING_TEXTINPUT_H

#include <SFML/Graphics.hpp>
#include <functional>
#include "GUIComponentAdapter.h"
#include "Typing.h"
#include "CursorBlink.h"
#include "Label.h"

class TextInput : public GUIComponentAdapter {
private:
    sf::RectangleShape box;
    CursorBlink cursorBlink;
    Typing typing;
    Label label;

    void updatePos();
    void updateCursor();
public:
    TextInput();

    void setSize(sf::Vector2f size);

    void setLabel(const std::string& str);
    void setLabelSize(const int& size);
    void setLabelColor(const sf::Color& color);

    std::function<void(const std::string&, const bool&)> callBack;
    void setCallBack(std::function<void(const std::string&, const bool&)> cb);

    std::string getString();
    void setString(const std::string& str);

    virtual Snapshot getSnapshot();
    virtual void applySnapshot(const Snapshot& snapshot);

    virtual void onMouseReleased(sf::Mouse::Button button, sf::Vector2f pos);
    virtual void onKeyPressed(const sf::Event::KeyEvent& key);
    virtual void onTextEntered(sf::Uint32 unicode);

    virtual void addEventHandler(sf::RenderWindow& window, sf::Event event) override;
    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    virtual void update();
};


#endif //CS008_SFML_TYPING_TEXTINPUT_H
