#pragma once

class View;

#include <memory>
#include <vector>

#include "Controller.h"

class View {
private:
    std::vector<Controller*> controllers;

protected:
    virtual void updateControllers() const {
        for (auto& c: controllers)
            c->viewChanged();
    }
public:
    virtual void addController(Controller* c){
        this->controllers.push_back(c);
    }
    virtual void modelChanged() = 0;
    virtual void show() = 0;
    virtual ~View() = default;
};