#ifndef HC2IMG_BAR
#define HC2IMG_BAR

#include <cstdint>
#include <vector>

#include <harmony-core/harmony-core.hpp>

namespace hc2img {
    /*!
     * \brief Предствляет Нотный такт.
     * Является базовым кирпичем интерфейса.
     * Содержит следующую информацию:
     * - о размере такта (определяется с помощью двух чисел - числителя и знаменателя размера).
     * - о ключе (определяется с помощью класса harmony_core::Clef).
     * - о ключевых знаках (определяется с помолью класса harmony_core::Key).
     * Также в такт можно добавить ноты и интервалы (клсcы harmony_core::Note и harmony_core::Interval).
     * Интервал хранится как две ноты в одинаковых индексах.
     * Возможность добавления определяется размером такта, размером ноты и суммой размеров нот в такте.
     */
    struct Bar final {
    public:
        /*!
         * \brief Добавляет ноту, если она помещается в такт.
         * Пустые места в такте отображаются как паузы.
         * \param [in] harmony_core::Note добавляемая нота.
         * \param [in] uint8_t Индекс ноты.
         */
        void add(harmony_core::Note &, uint8_t) noexcept;

        /*!
         * \brief Убирает ноту(ы) по индексу.
         * На месте удаленного объекта образуется пустота, отображаемая паузой при отрисовке такта.
         * \param [in] uint8_t Индекс ноты для удаления.
         */
        void remove(uint8_t) noexcept;

        /*!
         * Возвращает ноту, расположенную по индексу.
         * \param [in] uint8_t Индекс ноты.
         * \return Нота по индексу.
         */
        harmony_core::Note get(uint8_t) const noexcept;

        /*!
         * \brief Задает или переписывает размер такта.
         * \param [in] uint8_t Числитель размера
         * \param [in] uint8_t Знаменатель размера
         */
        void set_time_signature(uint8_t, uint8_t) noexcept;

        /*!
         * Возвращает текущий размер такта.
         * \return размер такта.
         */
        std::pair<uint8_t, uint8_t> get_time_signature() const noexcept;

        /*!
         * Задает или переписывает ключевые знаки (тональность) такта.
         * \param [in] harmony_core::Key Тональность для замены/установки значения.
         */
        void set_key(harmony_core::Key) noexcept;

        /*!
         * Возвращает тональность такта
         * \return Тональность такта.
         */
        harmony_core::Key get_key() const noexcept;

    private:
        /*!
         * \brief Хранит числитель размера такта
         */
        uint8_t numerator = 0;

        /*!
         * \brief Хранит знаменатель размера такта
         */
        uint8_t denominator = 0;

        /*!
         * \brief Хранит ссылку на ключ ракта
         */
        harmony_core::Clef *bar_clef = nullptr;

        /*!
         * \brief Хранит ссылку на тональность такта.
         */
        harmony_core::Key *bar_key = nullptr;

        /*!
         * хранит информацию о нотах в такте
         */
        std::vector<std::pair<uint8_t, harmony_core::Note *>> bar_notes;
    };
} // namespace hc2img

#endif // HC2IMG_BAR
