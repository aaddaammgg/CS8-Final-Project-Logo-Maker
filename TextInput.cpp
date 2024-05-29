//
// Created by Adam G.
//

#include "TextInput.h"

TextInput::TextInput() {
    box.setSize(getSize());
    box.setFillColor(sf::Color::Black);
    box.setOutlineColor(sf::Color::Red);
    box.setOutlineThickness(5);

    cursorBlink.setPosition(1, 1);
    label.setPosition(1, -2);
    typing.setPosition(0, -2);
}

void TextInput::setSize(sf::Vector2f size) {
    GUIComponent::setSize(size);
//    box.setSize(boxSize);
    cursorBlink.setSize({2, size.y - 2});
//    typing.setSize(boxSize);
    updatePos();
}

void TextInput::updatePos() {
    sf::FloatRect labelGB = label.getGlobalBounds();

    float padding = 10 + labelGB.width + labelGB.left;

    cursorBlink.setPosition(1 + padding, 1);
    typing.setPosition(0 + padding, -2);
    box.setPosition(padding, 0);

    box.setSize({getSize().x - padding, getSize().y});
    typing.setSize({getSize().x - padding, getSize().y});
}

void TextInput::setLabel(const std::string &str) {
    label.setLabel(str);
    updatePos();
}

void TextInput::setLabelSize(const int &size) {
    label.setLabelSize(size);
    updatePos();
}

void TextInput::setLabelColor(const sf::Color &color) {
    label.setLabelColor(color);
}

Snapshot TextInput::getSnapshot() {
    Snapshot s;
    s.setData(typing.getMultiText());
    return s;
}

void TextInput::applySnapshot(const Snapshot &snapshot) {
    typing.getMultiText() = snapshot.getData();
}

void TextInput::onMouseReleased(sf::Mouse::Button button, sf::Vector2f pos) {
    if (button != sf::Mouse::Left) return;

    sf::FloatRect boxPos = getTransform().transformRect(box.getGlobalBounds());

    if (boxPos.contains(pos)) {
        box.setOutlineColor(sf::Color::Green);
        enableState(SELECTED);
        cursorBlink.enableState(SELECTED);
    } else {
        box.setOutlineColor(sf::Color::Red);
        disableState(SELECTED);
        cursorBlink.disableState(SELECTED);
    }
}

void TextInput::onKeyPressed(const sf::Event::KeyEvent &key) {
    if (!isEnabled(SELECTED)) return;

    if (KBShortcuts::isUndo()) {
        std::cout << "Control + Z" << std::endl;

        if (getUndoSize() == 0 || typing.getMultiText().getCharCount() == 0) {
            return;
        }

        if (getUndoTop().snapshot.getData().getString() == typing.getMultiText().getString()) {
            undoPop();
        }

        applySnapshot(getUndoTop().snapshot);
        undoPop();
    }

    if (KBShortcuts::isRedo()) {
        std::cout << "Control + Y" << std::endl;

        if (getRedoSize() == 0) {
            return;
        }

        if (getRedoTop().snapshot.getData().getString() == typing.getMultiText().getString()) {
            redoPop();
        }

        applySnapshot(getRedoTop().snapshot);
        redoPop();
    }
}

void TextInput::updateCursor() {
    sf::FloatRect labelGB = label.getGlobalBounds();
    float padding = (label.getLabelString().empty()) ? 0 : 10;

    switch (typing.getMultiText().getAlignment()) { // I really do not like having this in updateCursor()
        case MultiText::ALIGN::LEFT: {
            typing.getMultiText().setPosition({0, 0});
            break;
        }
        case MultiText::ALIGN::CENTER: {
            typing.getMultiText().setPosition({getSize().x / 2, 0});
            break;
        }
        case MultiText::ALIGN::RIGHT: {
            typing.getMultiText().setPosition({getSize().x - 4, 0});
            break;
        }
    }

    sf::Vector2f curPos = typing.getMultiText().getTransform().transformPoint(0, 0);

    curPos += {3, 1};
    curPos += {typing.getMultiText().getSize().width, 0};
    curPos += {labelGB.width + labelGB.left + padding, 0};

    cursorBlink.setPosition(curPos);
}

std::string TextInput::getString() {
    return typing.getMultiText().getString();
}

void TextInput::setString(const std::string& str) {
    typing.getMultiText() = "";
    for (const auto& s : str) {
        typing.getMultiText().addChar(s);
    }

    updateCursor();
}

void TextInput::setCallBack(std::function<void(const std::string&, const bool&)> cb) {
    callBack = std::move(cb);
}

void TextInput::onTextEntered(sf::Uint32 unicode) {
    if (!isEnabled(SELECTED)) return;

    updateCursor();
}

void TextInput::addEventHandler(sf::RenderWindow &window, sf::Event event) {
    if (isEnabled(SELECTED)) {
        if (!getInit()) {
            HistoryNode hn;
            hn.snapshot = getSnapshot();
            hn.component = this;
            undoPush(hn);
            setInit(true);
        }

        typing.addEventHandler(window, event);

        if (event.type == sf::Event::TextEntered && !KBShortcuts::isControl()) {
            HistoryNode hn;
            hn.snapshot = getSnapshot();
            hn.component = this;
            undoPush(hn);

            if (callBack != nullptr) {
                callBack(typing.getMultiText().getString(), event.text.unicode == 8);
            }
        }
    }

    // Moved after typing's event handler due to typing class needing the highest priority
    GUIComponentAdapter::addEventHandler(window, event);

    if (isEnabled(SELECTED) && (KBShortcuts::isUndo() || KBShortcuts::isRedo())) {
        updateCursor();
    }
}

void TextInput::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    states.transform *= getTransform();
    window.draw(box, states);
    window.draw(typing, states);
    window.draw(cursorBlink, states);
    window.draw(label, states);
}

void TextInput::update() {
    typing.update();
    cursorBlink.update();
}
