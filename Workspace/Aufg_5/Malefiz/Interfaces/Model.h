#pragma once

class Model;

#include <memory>
#include <vector>

#include "View.h"

class Model {
    // using ViewPtr = std::shared_ptr<View>;
private:
    std::vector<View*> views;

protected:
    void updateViews() const {
        for (auto& v: views)
            v->modelChanged();
    }

public:
    virtual ~Model() = default;
    virtual void addView(View* v){
        this->views.push_back(v);
    }
};