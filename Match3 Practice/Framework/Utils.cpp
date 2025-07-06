#include "stdafx.h"
#include "Utils.h"

std::random_device Utils::rd;
std::mt19937 Utils::gen;

void Utils::Init()
{
    gen.seed(rd());
}

float Utils::RandomValue()
{
    std::uniform_real_distribution<float> dist(0.f, 1.f);
    return dist(gen);
}

int Utils::RandomRange(int min, int maxExclude)
{
    std::uniform_int_distribution<int> dist(min, maxExclude - 1);
	return dist(gen);
}

float Utils::RandomRange(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

sf::Vector2f Utils::SetOrigin(sf::Transformable& obj, Origins preset, const sf::FloatRect rect)
{
    sf::Vector2f newOrigin(rect.width, rect.height);
    newOrigin.x *= ((int)preset % 3) * 0.5f;
    newOrigin.y *= ((int)preset / 3) * 0.5f;
    obj.setOrigin(newOrigin);
    return newOrigin;
}

sf::Vector2f Utils::SetOrigin(sf::Shape& obj, Origins preset)
{
    return SetOrigin(obj, preset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Text& obj, Origins preset)
{
    return SetOrigin(obj, preset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Sprite& obj, Origins preset)
{
    return SetOrigin(obj, preset, obj.getLocalBounds());
}

void Utils::SetSpriteSize(sf::Sprite& obj, float width, float height)
{
    sf::Vector2u size = obj.getTexture()->getSize();
    obj.setScale({ width / static_cast<float>(size.x), height / static_cast<float>(size.y) });
}

float Utils::Clamp(float value, float min, float max)
{
    if (value < min)
        return min;
    else if (value > max)
        return max;
    return value;
}

float Utils::Clamp01(float value)
{
    return Clamp(value, 0.f, 1.f);
}

float Utils::Magnitude(const sf::Vector2f& vec)
{
    return std::sqrtf(SqrMagnitude(vec));
}

float Utils::SqrMagnitude(const sf::Vector2f& vec)
{
    return vec.x * vec.x + vec.y * vec.y;
}

sf::Vector2f Utils::GetNormal(const sf::Vector2f& vec)
{
    float mag = Magnitude(vec);
    if (mag < std::numeric_limits<float>::epsilon())
    {
        return { 0.f,0.f };
    }
    return vec / mag;
}

void Utils::Normalize(sf::Vector2f& vec)
{
    float mag = Magnitude(vec);
    if (mag > std::numeric_limits<float>::epsilon())
    {
        vec /= mag;
    }
}

float Utils::Distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
    return Magnitude(p1 - p2);
}

float Utils::Lerp(float min, float max, float t, bool clamp)
{
    if (clamp)
    {
        t = Clamp01(t);
    }

    return min + (max - min) * t;
}

sf::Vector2f Utils::Lerp(const sf::Vector2f& min, const sf::Vector2f& max, float t, bool clamp)
{
    if (clamp)
    {
        t = Clamp01(t);
    }

    return min + (max - min) * t;
}

sf::Color Utils::Lerp(const sf::Color& min, const sf::Color& max, float t, bool clamp)
{
    if (clamp)
    {
        t = Clamp01(t);
    }

    return sf::Color{
        (sf::Uint8)Lerp(min.r, max.r, t),
        (sf::Uint8)Lerp(min.g, max.g, t),
        (sf::Uint8)Lerp(min.b, max.b, t),
        (sf::Uint8)Lerp(min.a, max.a, t)
    };
}