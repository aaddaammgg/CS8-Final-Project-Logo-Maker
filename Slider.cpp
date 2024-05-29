//
// Created by Adam G.
//

#include "Slider.h"

Slider::Slider() : Slider("", 0) {

}

Slider::Slider(std::string str, float initialValue) {
    label = str;

    box.setFillColor(sf::Color::Transparent);
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(2);


    knob.setFillColor(sf::Color::White);
    knob.setOutlineColor(sf::Color::White);
    knob.setOutlineThickness(2);


//    dot.setFillColor(sf::Color::Transparent);
//    dot.setOutlineColor(sf::Color::White);
//    dot.setOutlineThickness(2);
//    dot.setRadius(20);
//    dot.setOrigin({20, 20 / 2});

    progressBox.setFillColor(sf::Color::Green);

    setValue(initialValue);

    disableState(HIDDEN);
    disableState(DISABLED);
    disableState(SELECTED);
    disableState(CLICKED);
}

void Slider::updatePos() {
    sf::FloatRect labelSize = label.getSize();

    float padding = 15 + labelSize.width;

    box.setSize({getSize().x - padding, getSize().y});
}

sf::Vector2f Slider::getMinMax() const {
    return {min, max};
}

float Slider::getMin() const {
    return min;
}

float Slider::getMax() const {
    return max;
}

void Slider::setMinMax(sf::Vector2f minMax) {
    setMin(minMax.x);
    setMax(minMax.y);
}

void Slider::setMin(float x) {
    min = x;
    setValue(value);
}

void Slider::setMax(float x) {
    max = x;
    setValue(value);
}

void Slider::setLabel(std::string str) {
    label = str;
    updatePos();
}

int Slider::getPrecision() const {
    return precision;
}

void Slider::setPrecision(int x) {
    precision = x;
}

float Slider::getValue() const {
    return value;
}

void Slider::setValue(float val) {
    value = val;

    if (value < min) {
        value = min;
    } else if (value > max) {
        value = max;
    }

    float width = box.getSize().x;
    float x = (value - min) * width / (max - min);

    knob.setPosition(x, 0);

    progressBox.setSize({x, getSize().y});

    std::stringstream stream;
    stream << std::fixed << std::setprecision(getPrecision()) << value;

    if (callBack != nullptr) {
        callBack(value);
    }

    labelValue = stream.str();

//    labelValue--;
//    labelValue += std::to_string(value);
}

float Slider::getStep() const {
    return step;
}

void Slider::setStep(float x) {
    step = x;
}

void Slider::setCallBack(std::function<void(const float &)> cb) {
    callBack = std::move(cb);
}

void Slider::setSize(sf::Vector2f size) {
    GUIComponent::setSize(size);

    label.setCharacterSize(size.y * 1.5);
    label.setPosition({-15, -3});
    label.setAlignment(MultiText::RIGHT);

//    std::cout << origPos.x << " " << label.getSize().width << std::endl;

    setPosition({origPos.x + label.getSize().width + 15, origPos.y});

    updatePos();

    labelValue.setCharacterSize(size.y * 1.5);
    labelValue.setPosition({box.getSize().x + 15, -3});

    knob.setSize({size.y / 2,static_cast<float>(size.y * 1)});
    knob.setOrigin({(size.y / 2) / 2, 0});

    setValue(getValue());
}

void Slider::setPosition(sf::Vector2f pos) {
    GUIComponent::setPosition(pos);

    origPos = pos;
}

void Slider::onMouseMoved(sf::Vector2f pos) {
    if (!isEnabled(CLICKED)) {
        return;
    }

    sf::Vector2f point = getTransform().getInverse().transformPoint(pos);

    float ratio = (point.x) / (box.getSize().x);

    setValue((max - min) * ratio + min);
}

void Slider::onMouseWheelScrolled(sf::Mouse::Wheel wheel, float delta, sf::Vector2f pos) {
    if (!isEnabled(SELECTED) || delta == 0) {
        return;
    }

    float amt = (delta > 0) ? step : -step;
    setValue(value + amt);
}

void Slider::onMousePressed(sf::Mouse::Button button, sf::Vector2f pos) {
    sf::FloatRect dotBounds = knob.getGlobalBounds();
    sf::FloatRect dotPosTransform = getTransform().transformRect(dotBounds);

    sf::FloatRect boxBounds = box.getGlobalBounds();
    sf::FloatRect boxPosTransform = getTransform().transformRect(boxBounds);

    if (button == sf::Mouse::Left && !isEnabled(CLICKED) && (dotPosTransform.contains(pos) || boxPosTransform.contains(pos))) {
        enableState(CLICKED);
        enableState(SELECTED);
        focusedComponent = this;
    }
}

void Slider::onMouseReleased(sf::Mouse::Button button, sf::Vector2f pos) {
    sf::FloatRect boxBounds = box.getGlobalBounds();
    sf::FloatRect boxPosTransform = getTransform().transformRect(boxBounds);

    if (!boxPosTransform.contains(pos) && !isEnabled(CLICKED)) {
        disableState(SELECTED);
        focusedComponent = nullptr;
    }

    disableState(CLICKED);
}

void Slider::onKeyPressed(const sf::Event::KeyEvent &key) {
    if (!isEnabled(SELECTED)) {
        return;
    }

    switch (key.code) {
        case sf::Keyboard::Left:
            setValue(value - (step * 2));
            break;
        case sf::Keyboard::Right:
            setValue(value + (step * 2));
            break;
        default:
            break;
    }
}

void Slider::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    if (isEnabled(HIDDEN)) {
        return;
    }
    states.transform *= getTransform();
    window.draw(box, states);
    window.draw(progressBox, states);
    window.draw(label, states);
    window.draw(labelValue, states);
    window.draw(knob, states);
}

void Slider::addEventHandler(sf::RenderWindow &window, sf::Event event) {
    if (isEnabled(HIDDEN) || isEnabled(DISABLED)) {
        return;
    }
    GUIComponentAdapter::addEventHandler(window, event);
}

void Slider::update() {

}
