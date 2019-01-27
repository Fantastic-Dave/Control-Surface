#pragma once

#include "Selectable.hpp"
#include <Helpers/Debug.hpp>
#include <Helpers/Updatable.hpp>
#include <Def/Def.hpp>

enum class Wrap : bool {
    NoWrap = false,
    Wrap = true,
};

template <setting_t N>
class Selector : public Updatable<> {
  protected:
    Selector(); // Not used, only for virtual inheritance
    Selector(Selectable<N> &selectable) : selectable(selectable) {}

  public:
    virtual void beginInput() = 0;
    virtual void beginOutput() = 0;

    void begin() final override {
        beginOutput();
        reset();
        beginInput();
    }

    virtual void reset() { set(selectable.getInitialSelection()); }

    setting_t get() const { return setting; }

    void set(setting_t newSetting) {
        newSetting = Selectable<N>::validateSetting(newSetting);
        selectable.select(newSetting);
        updateOutput(get(), newSetting);
        setting = newSetting;
    }

    void increment(Wrap wrap) {
        setting_t setting = this->get();
        setting++;
        if (setting == N) {
            if (wrap == Wrap::Wrap) {
                setting = 0;
            } else {
                return;
            }
        }
        this->set(setting);
    }

    void decrement(Wrap wrap) {
        setting_t setting = this->get();
        if (setting == 0) {
            if (wrap == Wrap::Wrap) {
                setting = N;
            } else {
                return;
            }
        }
        setting--;
        this->set(setting);
    }

  private:
    virtual void updateOutput(setting_t oldSetting, setting_t newSetting) = 0;

    Selectable<N> &selectable;
    setting_t setting = 0;
};