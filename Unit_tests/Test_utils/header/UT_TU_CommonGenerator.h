#pragma once

#include <vector>
#include <cstddef>

#include <functional>

namespace UTUtils
{

/*
** Describes interfase of any generator of GeneratedObject type objects.
*/
template <typename GeneratedObject>
class CommonGenerator
{
    static_assert(std::is_copy_assignable_v<GeneratedObject> || std::is_move_assignable_v<GeneratedObject>);

  public:

    virtual ~CommonGenerator() noexcept = default;

    virtual void generate(const size_t amount, std::function<void(GeneratedObject&&)> callback) const = 0;
    virtual void generateUnique(const size_t amount, std::function<void(GeneratedObject&&)> callback) const = 0;

    template <template <typename, typename...> class Container>
    Container<GeneratedObject> generateInContainer(const size_t amount) const;

    template <template <typename, typename...> class Container>
    Container<GeneratedObject> generateUniqueInContainer(const size_t amount) const;

    std::vector<GeneratedObject> generateInContainer(const size_t amount) const;
    std::vector<GeneratedObject> generateUniqueInContainer(const size_t amount) const;
};

template <typename GeneratedObject>
std::vector<GeneratedObject> CommonGenerator<GeneratedObject>::generateInContainer(const size_t amount) const
{
    std::vector<GeneratedObject> objects;
    objects.reserve(amount);

    const auto vectorPacker = [&objects](GeneratedObject&& object)
    {
        objects.push_back(std::move(object));
    };

    generate(amount, vectorPacker);

    return objects;
}

template <typename GeneratedObject>
std::vector<GeneratedObject> CommonGenerator<GeneratedObject>::generateUniqueInContainer(const size_t amount) const
{
    std::vector<GeneratedObject> objects;
    objects.reserve(amount);

    const auto vectorPacker = [&objects](GeneratedObject&& object)
    {
        objects.push_back(std::move(object));
    };

    generateUnique(amount, vectorPacker);

    return objects;
}

} // namespace UTUtils
